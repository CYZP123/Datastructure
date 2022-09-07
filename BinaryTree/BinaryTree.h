#pragma once

#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <cstring>
#include "../Stack/Stack.h"
#include "../Queue/Queue.h"

namespace sub {

template <typename T>
struct Cleaner {
  static void clean(T x) {
#ifdef _DEBUG
    static int n = 0;
    if (7 > std::strlen(typeid(T).name())) { //复杂类型一概忽略，只输出基本类型
       printf ("\t<%s>[%d]=", typeid(T).name(), ++n);
       print (x);
       printf (" purged\n");
    }
#endif
  }
};

template <typename T>
struct Cleaner<T*> {
  static void clean(T* x) {
    if (x) { delete x; } //如果其中包含指针，递归释放
#ifdef _DEBUG
    static int n = 0;
    printf ("\t<%s>[%d] released\n", typeid(T*).name(), ++n);
#endif
  }
};

template <typename T>
void release(T x) { Cleaner<T>::clean (x); }

template <typename T>
T Max(T left, T right) {
  if (left > right)
    return left;
  // left >= right
  else
    return right;
}

enum class RBColor {
  RED,
  BLACK
};


template <typename T>
class BinNode;

template <typename T>
inline int Stature(BinNode<T> *p) {
  return p ? p->height_ : -1;
}

template <typename T>
inline bool IsRoot(const BinNode<T> &x) {
  return !x.parent_;
}

template <typename T>
inline bool IsLChild(const BinNode<T> &x) {
  return !IsRoot(x) && (&x == x.parent_->lchild_);
}

template<typename T>
inline bool IsRChild(const BinNode<T> &x) {
  return !IsRoot(x) && (&x == x.parent_->rchild_);
}

template<typename T>
inline bool HasParent(const BinNode<T> &x) {
  return !IsRoot(x);
}

template<typename T>
inline BinNode<T> *HasLChild(const BinNode<T> &x) {
  return x.lchild_;
}

template<typename T>
inline BinNode<T> *HasRChild(const BinNode<T> &x) {
  return x.rchild_;
}

template<typename T>
inline bool HasChild(const BinNode<T> &x) {
  return HasLChild(x) || HasRChild(x);
}

template<typename T>
inline bool HasBothChild(const BinNode<T> &x) {
  return HasLChild(x) && HasRChild(x);
}

template<typename T>
inline bool IsLeaf(const BinNode<T> &x) {
  return !HasChild(x);
}

//AVL
template<typename T>
inline bool Balanced(const BinNode<T> &x) {
    return Stature(x.lchild_) == Stature(x.rchild_);
}

template<typename T>
inline int BalFac(const BinNode<T> &x) {
    return Stature(x.lchild_) - Stature(x.rchild_);
}

template<typename T>
inline bool AvlBalanced(const BinNode<T> &x) {
    return -2 < BalFac(x) && BalFac(x) < 2;
}

//rebalance
// template<typename T>
// inline BinNode<T>* TallerChild(const BinNode<T> *x) {
//     return Stature(x->lchild_) > Stature(x->rchild_) ? x->lchild_ : Stature(x->lchild_) < Stature(x->rchild_) ? x->rchild_ : IsLChild(*x) ? x->lchild_ : x->rchild_;
// }

template <typename T>
inline BinNode<T> *TallerChild(const BinNode<T> *x) {
  if (Stature(x->lchild_) > Stature(x->rchild_)) {
    return x->lchild_;
  } else if (Stature(x->lchild_) < Stature(x->rchild_)) {
    return x->rchild_;
  } else if (IsLChild(*x)) {
    return x->lchild_;
  } else {
    return x->rchild_;
  }
}

//Operations
template<typename T>
inline BinNode<T>* Sibling(const BinNode<T> *&x){
    return IsLChild(*x) ? (x->parent_->rchild_) : (x->parent_->lchild_);
}

template<typename T>
inline BinNode<T>* Uncle(BinNode<T> *x){
    return IsLChild(*(x->parent_)) ? (x->parent_->parent_->rchild_) : (x->parent_->parent_->lchild_);
}

template <typename T>
struct BinNode {
  using size_type             = size_t;
  using value_type            = T;
  using const_value_type      = T const;
  
  using pointer_type          = T*;
  using const_pointer_type    = const T*;

  using reference_type        = T&;
  using const_reference_type  = const T&;

  value_type data_;
  BinNode<value_type> *parent_;
  BinNode<value_type> *lchild_;
  BinNode<value_type> *rchild_;
  size_type height_;
  int npl_;
  RBColor color_;

  BinNode()
    : parent_(nullptr),
      lchild_(nullptr),
      rchild_(nullptr),
      height_(0),
      npl_(1),
      color_(RBColor::RED)
    { }

  BinNode(value_type data, BinNode<value_type> *parent = nullptr,
          BinNode<value_type> *lchild = nullptr, BinNode<value_type> *rchild = nullptr,
          size_type height = 0, int npl = 1, RBColor color = RBColor::RED)
    : data_(data),
      parent_(parent),
      lchild_(lchild),
      rchild_(rchild),
      height_(height),
      npl_(npl),
      color_(color)
    { }

  size_type Size() const {
    int s = 1;
    if (lchild_)
      s += lchild_->Size();
    if (rchild_)
      s += rchild_->Size();
    return s;
  }

  BinNode<value_type> *InsertAsLChild(const_reference_type data) {
    if (lchild_) {
      release(lchild_->data_);
      release(lchild_);
    }
    return lchild_ = new BinNode(data, this);
  }

  BinNode<value_type> *InsertAsRChild(const_reference_type data) {
    if (rchild_) {
      release(rchild_->data_);
      release(rchild_);
    }
    return rchild_ = new BinNode(data, this);
  }

  BinNode<value_type> *Succ() {
    BinNode<value_type> *s = this;
    if (rchild_) {
      s = rchild_;
      while (HasLChild(*s))
        s = s->lchild_;
    } else {
      while (IsRChild(*s))
        s = s->parent_;
    }

    return s;
  }

  template <typename VST>
  static void VisitAlongLeftBranch(BinNode<T> *x, VST &visit, sub::Stack<BinNode<T>*>& S){
    while(x){
      visit(x->data_);
      S.Push(x->rchild_);
      x = x->lchild_;
    }
  }

  static void GoAlongLeftBranch(BinNode<T> *x, sub::Stack<BinNode<T>*> &S){
    while (x) {  
      S.Push(x); 
      x = x->lchild_; 
    }
  }

  static void GotoHLVFL(Stack<BinNode<T>*> &S){
    while(BinNode<T>* x = S.Top())
      if(HasLChild(*x)) {

        if(HasRChild(*x)) 
          S.Push(x->rchild_);

        S.Push(x->lchild_);
      } else {
        S.Push(x->rchild_);
      }

    S.Pop();
  }

  template <typename VST>
  void TravLevel(BinNode<T> *x, VST& visit) {
    sub::Queue<BinNode<T>*> Q;
      Q.Enqueue(x);
      while(!Q.Empty()){
        BinNode<T>* x = Q.Dequeue();
        visit(x->data_);
        if(HasLChild(*x)) Q.Enqueue(x->lchild_);
        if(HasRChild(*x)) Q.Enqueue(x->rchild_);
    }
  }
  template <typename VST>
  void TravLevel(VST& visit) { TravLevel(this, visit); };

  template <typename VST> 
  void TravPre(BinNode<T>* x, VST& visit) {
    sub::Stack<BinNode<T>*> S;
    while(true){
      VisitAlongLeftBranch(x, visit, S);
      if(S.Empty()) break;
      x = S.Pop();
    }
  }
  template <typename VST>
  void TravPre(VST& visit) { TravPre(this, visit); }
  
  template <typename VST>
  void TravIn(BinNode<T> *x, VST &visit) {
    sub::Stack<BinNode*> S;
    while (true){
      GoAlongLeftBranch(x, S);
      if (S.Empty()) break;
      x = S.Pop();
      visit(x->data_);
      x = x->rchild_;
    }
  }
  template <typename VST>
  void TravIn(VST& visit) { TravIn(this, visit); }
  
  template <typename VST>
  void TravPost(BinNode<T>* x, VST &visit) {
    sub::Stack<BinNode*> S;

    if (x)
      S.Push(x);

    while (!S.Empty()) {
      if (S.Top() != x->parent_)
        GotoHLVFL(S);
      x = S.Pop();
      visit(x->data_);
    }
  }

  template <typename VST>
  void TravPost(VST& visit) { TravPost(this, visit); }


  bool operator < (BinNode const &bn)  { return data_ < bn.data_; }
  bool operator > (BinNode const &bn)  { return data_ > bn.data_; }
  bool operator == (BinNode const &bn) { return data_ == bn.data_; }
  bool operator != (BinNode const &bn) { return data_ != bn.data_; }

}; // class BinNode<T>

template <typename T>
class BinTree {
  using size_type             = size_t;
  using value_type            = T;
  using const_value_type      = T const;
  
  using pointer_type          = T*;
  using const_pointer_type    = const T*;

  using reference_type        = T&;
  using const_reference_type  = const T&;

 protected:
  size_type size_{0};
  BinNode<value_type> *root_{nullptr};

  virtual int UpdateHeight(BinNode<value_type> *x) {
    return x->height_ = 1 + Max(Stature(x->lchild_), Stature(x->rchild_));
  }

  void UpdateHeightAbove(BinNode<value_type> *x) {
    while (x) {
      UpdateHeight(x);
      x = x->parent_;
    }
  }

  BinNode<value_type> *&FromParentTo(const BinNode<value_type> &node) {
    if (IsRoot(node))
      return this->root_;
    else if (IsLChild(node))
      return node.parent_->lchild_;
    else
      return node.parent_->rchild_;
  }

 public:
  BinTree() { }

  ~BinTree() {
    Destruct(root_);
  }

  void Destruct(BinNode<value_type> *x) {
    if (x != nullptr) {
      BinNode<value_type> *lchild = x->lchild_;
      BinNode<value_type> *rchild = x->rchild_;
      release(x->data_);
      release(x);

      Destruct(lchild);
      Destruct(rchild);
    }
  }

  size_type Size() const { return size_; }

  bool Empty() const { return !root_; }
  
  BinNode<value_type> *Root() const { return root_; }

  BinNode<value_type> *InsertAsRoot(const_reference_type data) {
    size_ = 1;
    return root_ = new BinNode<value_type>(data);
  }
    
  BinNode<value_type> *InsertAsLChild(BinNode<value_type> *x, const_reference_type data) {
    size_++;
    x->InsertAsLChild(data);
    UpdateHeightAbove(x);
    return x->lchild_;
  }

  BinNode<value_type> *InsertAsRChild(BinNode<value_type> *x, const_reference_type data) {
    size_++;
    x->InsertAsRChild(data);
    UpdateHeightAbove(x);
    return x->rchild_;
  }

  BinNode<value_type> *AttachAsLChild(BinNode<value_type> *x, BinTree<value_type> *&S) {
    BinTree<value_type> *tmp = Secede(x->rchild_);

    if ((x->lchild_ = S->root_)) {
      x->lchild_->parent_ = x;
    }

    if (tmp)
      release(tmp);

    size_ += S->size_;
    UpdateHeightAbove(x);
    S->root_ = nullptr;
    S->size_ = 0;
    release(S);
    S = nullptr;

    return x;
  }

  BinNode<value_type> *AttachAsRChild(BinNode<value_type> *x, BinTree<value_type> *&S) {
    BinTree<value_type> *tmp = Secede(x->rchild_);

    if ((x->rchild_ = S->root_))
      x->rchild_->parent_ = x;

    if (tmp)
      release(tmp);

    size_ += S->size_;
    UpdateHeightAbove(x);
    S->root_ = nullptr;
    S->size_ = 0;
    release(S);
    S = nullptr;

    return S;
  }

  static int RemoveAt(BinNode<value_type> *x) {
    if (!x) return 0;

    int n = 1 + RemoveAt(x->lchild_) + RemoveAt(x->rchild_);
    release(x->data_);
    release(x);

    return n;
  }

  int Remove(BinNode<value_type> *x) {
    this->FromParentTo(*x) = nullptr;

    UpdateHeightAbove(x->parent_);
    int n = RemoveAt(x);
    size_ -= n;

    return n;
  }

  BinTree<value_type> *Secede(BinNode<value_type> *x) {
    if (x == nullptr)
      return nullptr;

    this->FromParentTo(*x) = nullptr;
    UpdateHeightAbove(x->parent_);

    BinTree<value_type> *S = new BinTree<value_type>();
    S->root_ = x;

    x->parent_ = nullptr;
    S->size_ = x->Size();

    size_ -= S->Size();

    return S;
  }

  template <typename VST>
  void TravLevel(VST &&visit) {
    if (root_)
      root_->TravLevel(visit);
  }

  template <typename VST>
  void TravPre(VST &&visit) {
    if (root_)
      root_->TravPre(visit);
  }

  template <typename VST>
  void TravIn(VST &&visit) {
    if (root_)
      root_->TravIn(visit);
  }

  template <typename VST>
  void TravPost(VST &&visit) {
    if (root_)
      root_->TravPost(visit);
  }

  template <typename VST>
  void TravPre_R(BinNode<value_type> *x, VST &visit) {
    if (!x) return;
    visit(x->data_);
    TravPre_R(x->lchild_, visit);
    TravPre_R(x->rchild_, visit);
  }

  template <typename VST>
  void TravPre_R(VST &visit) { TravPre_R(root_, visit); }

  template <typename VST>
  void TravPost_R(BinNode<value_type> *x, VST &visit) {
    if (!x) return;
    TravPost_R(x->lchild_, visit);
    TravPost_R(x->rchild_, visit);
    visit(x->data_);
  }

  template <typename VST>
  void TravPost_R(VST &visit) { TravPost_R(root_, visit); }

  template <typename VST>
  void TravIn_R(BinNode<value_type> *x, VST &visit) {
    if (!x) return;
    TravIn_R(x->lchild_, visit);
    visit(x->data_);
    TravIn_R(x->rchild_, visit);
  }

  template <typename VST>
  void TravIn_R(VST &visit) { TravIn_R(root_, visit); }

  bool operator < (const BinNode<value_type> &rhs)
    { return root_ && rhs.root_ && (*root_) < (*rhs.root_); }

  bool operator > (const BinTree<value_type> &rhs)
    { return root_ && rhs.root_ && (*root_) > (*rhs.root_); }

  bool operator == (const BinTree<value_type> &rhs)
    { return root_ && rhs.root_ && (root_ == rhs.root_); }

  bool operator != (const BinTree<value_type> &rhs)
    { return !(*this == rhs); }

}; // class BinTree<T>


} // namespace sub
#endif