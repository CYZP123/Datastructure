#pragma once

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <bits/move.h>
#include <random>
#include <iostream>

#define DEFAULT_CAPACITY 3

namespace sub {

template <typename T>
class Vector {
  using value_type            = T;
  using const_value_type      = T const;
  
  using pointer_type          = T*;
  using const_pointer_type    = const T*;

  using reference_type        = T&;
  using const_reference_type  = const T&;

 protected:
  int size_;
  int capacity_;
  pointer_type elem_;

  void CopyForm(const_pointer_type from, int lo, int hi) {
    int new_size = 2 * (hi - lo);
    capacity_ = new_size;
    elem_ = new value_type[capacity_];
    size_ = 0;

    while (lo < hi)
      elem_[size_++] = from[lo++];
  }

  void Expand() {
    // If remain have space in array return.
    if (size_ < capacity_) return;

    // If size_ >= capacity_ but capacity_ too small set capacity_ to normal.
    if (capacity_ < DEFAULT_CAPACITY)
      capacity_ = DEFAULT_CAPACITY;

    // Reallocate a array and copy from origial array to new array
    // update capacity_ and delete old array.
    pointer_type old_elem = elem_;
    elem_ = new value_type[capacity_ *= 2];

    for (int i = 0; i < size_; ++i) {
      elem_[i] = old_elem[i];
    }
    delete[] old_elem;
  }

  void Shrink() {
    // if capacity_ small than 6 return.
    if (capacity_ < DEFAULT_CAPACITY * 2) return;

    if (size_ * 4 > capacity_) return;

    pointer_type old_elem = elem_;
    elem_ = new value_type[capacity_ /= 2];

    for (int i = 0; i < size_; ++i)
      elem_[i] = old_elem[i];

    delete[] old_elem;
  }

  int Max(int lo, int hi) {
    int max = hi;
    while (lo < hi--) {
      if (elem_[hi] > elem_[max])
        max = hi;
    }
    return max;
  }

 public:
  Vector(int scale = 0, value_type val = 0, int capacity = DEFAULT_CAPACITY) {
    elem_ = new value_type[capacity_ = capacity];
    for (size_ = 0; size_ < scale; size_++)
      elem_[size_] = val;
  }

  Vector(const_pointer_type from, int lo, int hi) {
    CopyForm(from, lo, hi);
  }

  Vector(const_pointer_type from, int n) {
    CopyForm(from, 0, n);
  }

  Vector(Vector<value_type> const &v, int lo, int hi) {
    CopyForm(v.elem_, lo, hi);
  }

  Vector(Vector<value_type> const &v) {
    CopyForm(v.elem_, 0, v.size_);
  }

  ~Vector() {
    delete[] elem_;
    elem_ = nullptr;
  }

  int Size() const { return size_; }

  bool Empty() const { return !size_; }

  int DisOrdered() const {
    int n = 0;
    for (int i = 1; i < size_; ++i)
      if (elem_[i - 1] > elem_[i])
        ++n;

    return n;
  }

  int Partition(int lo, int hi) {
    int i = lo, j = hi + 1;
    const_value_type val = elem_[lo];

    while (true) {

      while (elem_[++i] < val)
        if (i == hi) break;

      while (elem_[--j] > val)
        if (j == lo) break;;

      if (i >= j) break;

      std::swap(elem_[i], elem_[j]);
    }

    std::swap(elem_[lo], elem_[j]);

    return j; // return pivot
  }

  void QuickSort(int lo, int hi) {
    if (lo >= hi) return;
    int pivot = Partition(lo, hi);
    QuickSort(lo, pivot - 1);
    QuickSort(pivot + 1, hi);
  }

  void QuickSort() { QuickSort(0, size_ - 1); }
  // [WARNING]
  // use this func must ensure element in elem_ are ordered.
  int BinarySearch(const_pointer_type ar, const_value_type key, int lo, int hi) {
    while (lo < hi) {
      int mid = (lo + hi) / 2;
      if (key < ar[mid]) hi = mid - 1;
      else if (key > ar[mid]) lo = mid + 1;
      else return mid;
    }
    return -1;
  }

  int Search(const_reference_type e, int lo, int hi) {
    QuickSort();
    return BinarySearch(elem_, e, lo, hi);
  }
  
  int Search(const_reference_type e) {
    return (size_ <= 0) ? -1 : Search(e, 0, size_ - 1);
  }

  int Find(const_reference_type e, int lo, int hi) {
    while (lo < hi-- && e != elem_[hi]);
    return hi;
  }

  int Find(const_reference_type e) {
    return Find(e, 0, size_);
  }

  reference_type operator[](int r) const {
    return elem_[r];
  }

  Vector<T> &operator=(Vector<T> const &rhs) {
    if (elem_)
      delete[] elem_;
    
    CopyForm(rhs.elem_, 0, rhs.Size());

    return *this;
  }

  size_t Remove(int lo, int hi) {
    if (lo == hi) return 0;

    while (hi < size_)
      elem_[lo++] = elem_[hi++];
    size_ = lo;

    Shrink();

    return hi - lo;
  }

  value_type Remove(int r) {
    value_type e = elem_[r];
    Remove(r, r + 1);
    return e;
  }

  int Deduplicate() {
    int old_size = size_;
    int i = 1;
    while (i < size_) {
      find(elem_[i], 0, i) < 0 ? i++ : Remove(i);
    }

    return old_size - size_;
  }

  int Insert(int pos, const_reference_type e) {
    Expand();

    for (int i = size_; i > pos; i--)
      elem_[i] = elem_[i - 1];

    elem_[pos] = e;
    size_++;

    return pos;
  }

  int Insert(const_reference_type e) { return Insert(size_, e); }

  void Put(int pos, const_reference_type e) {
    elem_[pos] = e;
  }

  value_type Get(int pos) { return elem_[pos]; }

  void Unsort(int lo, int hi) {
    pointer_type v = elem_ + lo;
    for (int i = hi - lo; i > 0; i--)
      std::swap(v[i - 1], v[rand() % i]);
  }

  void Unsort() {
    Unsort(0, size_);
  }

  int Uniquify() {
    int i = 0, j = 0;

    while (++j < size_) {
      if (elem_[i] != elem_[j])
        elem_[++i] = elem_[j];
    }
    // Currently i indexed the last element in array, so need plus + 1 to show array size
    size_ = ++i;
    Shrink();

    return j - i; // return number of deleted element
  }

  void Traverse(void (*visit)(reference_type)) {
    for (int i = 0; i < size_; ++i)
      visit(elem_[i]);
  }

  template <typename VST>
  void Traverse(VST &visit) {
    for (int i = 0; i < size_; ++i) {
      visit(elem_[i]);
    }
  }

  void Report(std::string title) {
    std::cout << "Vector(" << title << "): ";
    for (int i = 0 ; i < size_; ++i) {
      std::cout << elem_[i] << ' ';
    }
    std::cout << std::endl;
  }
};

} // namespace sub

#endif // __VECTOR_H__
