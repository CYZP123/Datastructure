#pragma once

#ifndef __LIST_H__
#define __LIST_H__

#include <cstddef>
#include <cassert>
#include <string>
#include <iostream>

namespace sub {

template <typename T>
struct ListNode {
  using value_type            = T;
  using const_value_type      = T const;
  
  using pointer_type          = T*;
  using const_pointer_type    = const T*;

  using reference_type        = T&;
  using const_reference_type  = const T&;

  value_type data_;
  ListNode<value_type> *pre_;
  ListNode<value_type> *succ_;

  ListNode() = default;

  ListNode(value_type data, ListNode<value_type> *pre = nullptr,
                            ListNode<value_type> *succ = nullptr)
    : data_(data), pre_(pre), succ_(succ)
  { }

  ListNode<value_type> *InsertAsPre(const_reference_type data) {
    ListNode<value_type> *new_node = new ListNode<T>(data, pre_, this);

    pre_->succ_ = new_node;
    pre_ = new_node;

    return new_node;
  }

  ListNode<value_type> *InsertAsSucc(const_reference_type data) {
    ListNode<value_type> *new_node = new ListNode<value_type>(data, this, succ_);

    succ_->pre_ = new_node;
    succ_ = new_node;

    return new_node;
  }
};

template <typename T>
class List {
  using size_type             = size_t;
  using value_type            = T;
  using const_value_type      = T const;
  
  using pointer_type          = T*;
  using const_pointer_type    = const T*;

  using reference_type        = T&;
  using const_reference_type  = const T&;

 private:
  size_type size_;
  ListNode<value_type> *header_;
  ListNode<value_type> *trailer_;

 protected:
  void Init() {
    header_ = new ListNode<value_type>;
    trailer_ = new ListNode<value_type>;
    header_->succ_ = trailer_;
    header_->pre_ = nullptr;
    trailer_->pre_ = header_;
    trailer_->succ_ = nullptr;
    size_ = 0;    
  }

  int Clear() {
    int old_size = size_;

    while (size_ > 0)
      Remove(header_->succ_);

    return old_size;
  }

  void CopyNode(ListNode<value_type> *pos, size_t n) {
    Init();
    while (n--) {
      InsertAsLast(pos->data_);
      pos = pos->succ_;
    }
  }

 public:
  List() { Init(); }

  List(List<value_type> const &list) {
    CopyNode(list.First(), list.size_);
  }

  List(List<value_type> const &list, size_t pos, size_t n) {
    CopyNode(list[pos], n);
  }

  List(ListNode<value_type> *pos, size_t n) {
    CopyNode(pos, n);
  }

  ~List() {
    Clear();
    delete header_;
    delete trailer_;
  }

  size_type Size() const noexcept { return size_; }

  ListNode<value_type> *First() const { return header_->succ_; }

  ListNode<value_type> *Last() const { return trailer_->pre_; }

  int Rank(ListNode<value_type> *pos) const {
    ListNode<value_type> node = header_;
    for (int r = 0; node->succ_ != trailer_; r++, node = node->succ_)
      if (node->succ_ == pos)
        return r;

    return -1;
  }

  bool Empty() const
    { return size_ <= 0; }

  value_type &operator[](int r) const {
    ListNode<value_type> *node = First();
    while (0 < r--)
      node = node->succ_;

    return node->data_;
  }

  bool Vaild(ListNode<value_type> *node) {
    return node && (trailer_ != node) && (header_ != node);
  }

  int DisOrdered() const {
    int n = 0;
    ListNode<value_type> *node = First();

    for (size_t i = 0; i < size_ - 1; node = node->succ_, ++i)
      if (node->data_ > node->succ_->data_)
        ++n;

    return n;
  }

  ListNode<value_type> *Find(const_reference_type ele, size_t n,
                             ListNode<value_type> *node) const {
    while (n-- > 0) {
      if (ele == (node = node->pre_)->data_)
        return node;
    }
    return nullptr;
  }

  ListNode<value_type> *Find(const_reference_type ele) const {
    return Find(ele, size_, trailer_);
  }

  ListNode<value_type> *Search(const_reference_type ele, size_t n,
                               ListNode<value_type> *node) const {
    while (n-- >= 0) {
      if ((node = node->pre_)->data_ <= ele)
        break;
    }
    return node;
  }

  ListNode<value_type> *Search(const_reference_type ele) const {
    return Search(ele, size_, trailer_);
  }

  ListNode<value_type> *SelectMax(ListNode<value_type> *start, size_t n) {
    ListNode<value_type> *max = start;
    for (ListNode<value_type> *cur_node = start; n > 1; n--)
      if((cur_node = cur_node->succ_)->data_ >= max->data_)
        max = cur_node;

    return max;
  }

  ListNode<value_type> *SelectMax() {
    return SelectMax(header_->succ_, size_);
  }

  ListNode<value_type> *InsertAsFirst(const_reference_type ele) {
    ++size_;
    return header_->InsertAsSucc(ele);
  }

  ListNode<value_type> *InsertAsLast(const_reference_type ele) {
    ++size_;
    return trailer_->InsertAsPre(ele);
  }

  ListNode<value_type> *InsertAfter(ListNode<value_type> *node,
                                   const_reference_type ele) {
    ++size_;
    return node->InsertAsSucc(ele);
  }

  ListNode<value_type> *InsertBefore(ListNode<value_type> *node,
                                     const_reference_type ele) {
    ++size_;
    return node->InsertAsPre(ele);
  }

  value_type Remove(ListNode<value_type> *node) {
    value_type data = node->data_; // will delete data of node
    node->pre_->succ_ = node->succ_;
    node->succ_->pre_ = node->pre_;

    delete node;
    --size_;

    return data;
  }

  
  int DeDuplicate() {
    if (size_ <= 1) return 0; // only have one or zero data in list need do nothing

    int old_size = size_;
    ListNode<value_type> *node = header_;
    int r = 0;

    while ((node = node->succ_) != trailer_) {
      ListNode<value_type> *tmp = Find(tmp->data_, r, node);
      if (tmp)
        Remove(tmp);
      else
        ++r;
    }
    return old_size - size_;
  }

  int Uniquify() {
    if (size_ <= 1) return 0;

    int old_size = size_;

    ListNode<value_type> *p = First();
    ListNode<value_type> *q = nullptr;

    while ((q = p->succ_) != trailer_) {
      if (p->data_ != q->data_)
        p = q;
      else
        Remove(q);
    }
    return old_size - size_;
  }

  void Reverse() {
    ListNode<value_type> *start = header_;
    ListNode<value_type> *end = trailer_;

    // assert(size_ % 2 == 0);

    for (int i = 0; i < size_; i += 2) {
      std::swap((start = start->succ_)->data_, (end = end->pre_)->data_);
    }
  }

  ///!      pre        succ  succ  succ
  ///! null <-- header --> 0 --> 1 --> trailer --> null  ---------------------- Before
  ///!                 <--   <--   <--
  ///!                 pre   pre   pre
  ///!
  ///!                  succ  succ  succ
  ///! null <-- trailer <-- 0 <-- 1 <-- header --> null  ----------------------- After
  ///!      succ        -->   -->   -->        pre
  ///!                  pre   pre   pre
  ///!
  ///! OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
  ///! OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
  ///!
  ///! Loop 1 start:
  ///!
  ///!      pre        succ  succ  succ
  ///! null <-- header --> 0 --> 1 --> trailer --> null  ----------------------  (1)
  ///!                 <--   <--   <--
  ///!                 pre   pre   pre
  ///!
  ///!
  ///! first      second
  ///!   |    succ  | succ   succ         succ
  ///! header --->  0 ---> 1 ---> trailer ---> null      ----------------------  (2)
  ///!        <--     <---   <---
  ///!        pre     pre    pre
  ///!        -->
  ///!        pre
  ///!
  ///!           first  second
  ///!        succ | succ | succ         succ
  ///! header ---> 0 ---> 1 ---> trailer ---> null      ----------------------  (3)
  ///!        --->   --->   <---
  ///!        pre    pre    pre
  ///!               <---
  ///!               pre
  ///!
  ///! 
  ///!                  first   second
  ///!        succ   succ |       |      succ
  ///! header ---> 0 ---> 1 ---> trailer ---> null      ----------------------  (4)
  ///!        --->   --->   ---> 
  ///!        pre    pre    pre
  ///!                      <---
  ///!                      pre
  ///!
  ///!                           first       second
  ///!        succ   succ   succ   |     succ  |
  ///! header ---> 0 ---> 1 ---> trailer ---> null      ---------------------- Loop 1 end
  ///!        --->   --->   --->         --->
  ///!        pre    pre    pre          pre
  ///! ------------------------------------------------------------------------------------
  ///! Loop 2 start:
  ///! 
  ///! first     second
  ///!   |    succ |        succ         succ
  ///! header ---> 0 ---> 1 ---> trailer ---> null     -------------------------- (1)
  ///!        <---   pre    --->         --->
  ///!        succ          pre          pre
  ///!        --->
  ///!        pre
  ///!  
  ///!           first  second
  ///!        succ | succ |              succ
  ///! header ---> 0 <--- 1 ---> trailer ---> null     --------------------------  (2)
  ///!        <---   --->   pre          --->
  ///!        succ   pre                 pre
  ///!        --->
  ///!        pre
  ///!
  ///!                   first     second
  ///!         succ   succ | succ    |
  ///!  header ---> 0 <--- 1 <--- trailer ---> null    --------------------------  (3)  Loop 2 end
  ///!         <---   --->   --->         pre
  ///!         succ   pre    pre
  ///!         --->
  ///!         pre
  ///!          
  ///!                                       first       second
  ///!                   succ    succ   succ   |           |
  ///!  null <--- header <---  0 <--- 1 <--- trailer ---> null
  ///!       succ        --->    --->   --->         pre
  ///!                   pre     pre    pre
  ///!
  ///!
  ///!                   succ  succ  succ
  ///!  null <-- trailer <-- 0 <-- 1 <-- header --> null
  ///!       succ        -->   -->   -->        pre
  ///!                   pre   pre   pre
  ///!
  void Reverse2() { 
    if (size_ <= 1) return;

    ListNode<value_type> *first = nullptr;
    ListNode<value_type> *second = nullptr;

    for (first = header_, second = first->succ_;
          first != trailer_;
            first = second, second = second->succ_) {
      first->pre_ = second;
    }

    for (first = header_, second = first->pre_;
          first != trailer_;
            first = second, second = second->pre_) {
      second->succ_ = first;
    }

    trailer_->pre_ = nullptr;
    header_->succ_ = nullptr;

    std::swap(header_, trailer_);
  }

  void Reverse3() {
    if (size_ <= 1) return;

    for (ListNode<value_type> *p = header_; p; p = p->pre_)
      std::swap(p->pre_, p->succ_);

    std::swap(header_, trailer_);
  }

  void Traverse(void (*visit)(reference_type)) {
    for (ListNode<value_type> *p = header_->succ_; p != trailer_; p = p->succ_) {
      visit(p->data_);
    }
  }

  template <typename VST>
  void Traverse(VST &visit) {
    for (ListNode<value_type> *p = header_->succ_; p != trailer_; p = p->succ_)
      visit(p->data_);
  }

  void Report(std::string title) {
    std::cout << "List(" << title << "): ";
    ListNode<value_type> *p = First();
    while (Vaild(p)) {
      std::cout << p->data_ << ", ";
      p = p->succ_;
    }
    std::cout << std::endl;
  }

  void Show(ListNode<value_type> *p, size_t n) {
    for (size_t i = 0; i < n; ++i, p = p->succ_)
      std::cout << p->data_ << ", ";
    std::cout << std::endl;
  }

}; // class

} // namespace sub

#endif
