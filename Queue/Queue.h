#pragma once

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "../List/List.h"

namespace sub {

template <typename T>
class Queue : public List<T> {
  using value_type            = T;
  using const_value_type      = T const;
  
  using pointer_type          = T*;
  using const_pointer_type    = const T*;

  using reference_type        = T&;
  using const_reference_type  = const T&;

 public:
  void Enqueue(const_reference_type data) { this->InsertAsLast(data); }

  value_type Dequeue() { return this->Remove(this->First()); }

  reference_type Front() { return this->First()->data_; }

  bool Empty() const noexcept { return this->Size() == 0; }
};

} // namespace sub
#endif
