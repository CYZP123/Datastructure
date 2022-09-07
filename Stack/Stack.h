#pragma once

#ifndef __STACK_H__
#define __STACK_H__

#include "../Vector/Vector.h"

namespace sub {

template <typename T>
class Stack : public Vector<T> {
  using value_type            = T;
  using const_value_type      = T const;
  
  using pointer_type          = T*;
  using const_pointer_type    = const T*;

  using reference_type        = T&;
  using const_reference_type  = const T&;

 public:
  void Push(const_reference_type data) { this->Insert(this->Size(), data); }

  value_type Pop() { return this->Remove(this->Size() - 1); }

  reference_type Top() { return (*this)[this->Size() - 1]; }

  bool Empty() { return this->Size() == 0; }
};

} // namespace sub

#endif