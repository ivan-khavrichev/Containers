#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_QUEUE_H_

#include <cstddef>
#include <cstdio>
#include <iostream>
#include <list>

#include "s21_list.h"

namespace s21 {

template <class T>
class Queue {
 public:
  // Queue Member type
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  // Queue Member functions

  // default constructor, creates empty queue
  Queue() { queue_.clear(); }

  // initializer list constructor, creates queue initizialized using
  // std::initializer_list
  Queue(std::initializer_list<value_type> const &items) {
    queue_.clear();
    for (const auto &i : items) {
      push(i);
    }
  }

  // copy constructor
  Queue(const Queue &q) { operator=(q); }

  // move constructor
  Queue(Queue &&q) { operator=(std::move(q)); }

  // destructor
  ~Queue() { queue_.clear(); }

  // assignment operator overload for moving object
  Queue &operator=(Queue &&q) {
    this->queue_ = std::move(q.queue_);
    return *this;
  }

  // assignment operator overload for copying object
  Queue &operator=(const Queue &q) {
    this->queue_ = q.queue_;
    return *this;
  }

  // Queue Element access

  // access the first element
  const_reference front() { return queue_.front(); }

  // access the last element
  const_reference back() { return queue_.back(); }

  // Queue Capacity

  // checks whether the container is empty
  bool empty() { return queue_.empty(); }

  // returns the number of elements
  size_type size() { return queue_.size(); }

  // Queue Modifiers

  // inserts element at the end
  void push(const_reference value) { queue_.push_back(value); }

  // removes the first element
  void pop() { queue_.pop_front(); }

  // swaps the contents
  void swap(Queue &other) { queue_.swap(other.queue_); }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    s21::Vector<value_type> new_vector = {args...};
    for (auto it = new_vector.begin(); it != new_vector.end(); ++it) {
      push(*it);
    }
  }

 private:
  s21::list<value_type> queue_;
};

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_QUEUE_H_