
#ifndef __S21VECTOR_H__
#define __S21VECTOR_H__

#include <cstring>
#include <exception>
#include <iostream>
#include <limits>

#include "../s21_containers.h"

namespace s21 {

template <class T, typename size_type = size_t>
class Vector {
 public:
  // Vector Member type

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  // Vector Member functions

  // default constructor, creates empty vector
  Vector() {
    size_ = 0;
    capacity_ = 0;
    vector_ = nullptr;
  };

  // parameterized constructor, creates the vector of size n
  Vector(size_type n) : size_(n), capacity_(n) {
    if (size_ <= 0 || capacity_ <= 0)
      throw std::out_of_range("Vector size can't be 0 or lower");
    vector_ = MemAlloc(size_);
  }
  // initializer list constructor, creates vector initizialized using
  // std::initializer_list
  Vector(std::initializer_list<value_type> const &items) {
    size_ = (size_type)items.size();
    capacity_ = (size_type)items.size();
    vector_ = MemAlloc(size_);
    int i = 0;
    for (const auto &it : items) {
      vector_[i] = it;
      i++;
    }
  }

  // copy constructor
  Vector(const Vector &v) : Vector(v.size()) { VectorCopy(*this, v, 0, size_); }

  // move constructor
  Vector(Vector &&v) { VectorMove(v); }

  // destructor
  ~Vector() {
    if (vector_ != nullptr) {
      FreeVector(begin());
    }
  }

  Vector &operator=(const Vector &v) {
    if (this != &v) {
      FreeVector(begin());
      size_ = v.size_;
      capacity_ = v.capacity_;
      vector_ = MemAlloc(size_);
      VectorCopy(*this, v, 0, size_);
    }
    return *this;
  }

  // assignment operator overload for moving object
  Vector &operator=(Vector &&v) {
    if (this != &v) {
      VectorMove(v);
    }
    return *this;
  }

  // Vector Element access

  // access specified element with bounds checking
  reference at(size_type pos) {
    if (pos >= size_ || pos < 0)
      throw std::out_of_range(
          "Trying to access an element out of vector's range");
    return vector_[pos];
  }

  // access specified element
  reference operator[](size_type pos) { return vector_[pos]; }

  // access the first element
  const_reference front() { return *vector_; }
  // access the last element
  const_reference back() { return vector_[size_ - 1]; }

  // direct access to the underlying array
  T *data() { return vector_; }

  // returns an iterator to the beginning
  iterator begin() { return vector_; }

  // returns an iterator to the end
  iterator end() { return (vector_ + size_); }

  // returns an iterator to the pos element
  iterator itpos(size_type pos) {
    if (pos > size_ + 1 || pos < 0)
      throw std::out_of_range(
          "Trying to access an iterator out of vector's range");
    return (begin() + pos);
  }

  // returns an const_iterator to the beginning
  const_iterator cbegin() const { return const_iterator(vector_); }

  // returns an const_iterator to the end
  const_iterator cend() const { return const_iterator(vector_ + size_); }

  // returns an const_iterator to the pos element
  const_iterator citpos(size_type pos) const {
    if (pos > size_ + 1 || pos < 0)
      throw std::out_of_range(
          "Trying to access an iterator out of vector's range");
    return const_iterator(cbegin() + pos);
  }

  // checks whether the container is empty
  bool empty() {
    bool out = false;
    if (size_ == 0) out = true;
    return out;
  }

  // returns the number of elements
  size_type size() const { return size_; };

  // returns the maximum possible number of elements - НЕ СДЕЛАНО
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / (2 * sizeof(value_type));
  }

  // allocate storage of size elements and copies current array
  // elements to a newely allocated array
  void reserve(size_type size) {
    if (size > capacity_) {
      Vector<T> new_vector(size_);
      VectorCopy(new_vector, *this, 0, size_);
      capacity_ = size;
    }
  }

  // returns the number of elements
  // that can be held in currently allocated storage
  size_type capacity() const { return capacity_; }

  // reduces memory usage by freeing unused memory
  void shrink_to_fit() {
    if (size_ < capacity_) {
      Vector<T> new_vector(size_);
      VectorCopy(new_vector, *this, 0, size_);
      capacity_ = size_;
    }
  }

  // clears the contents
  void clear() {
    FreeVector(begin());
    vector_ = MemAlloc(size_);
    size_ = 0;
  }

  // inserts elements into concrete pos and
  // returns the iterator that points to the new element
  iterator insert(iterator pos, const_reference value) {
    size_type new_size = size_ + 1;
    size_type el_pos = pos - vector_;
    iterator new_vector = MemAlloc(new_size);
    for (auto it = begin(), it_new = new_vector; it != pos; ++it, ++it_new) {
      *it_new = *it;
    }
    *(new_vector + el_pos) = value;
    for (auto it = citpos(el_pos + 1), it_new = new_vector + el_pos + 1;
         it_new != new_vector + new_size; ++it, ++it_new) {
      *it_new = *(it - 1);
    }
    FreeVector(begin());
    vector_ = new_vector;
    size_ = new_size;
    capacity_++;
    pos = vector_ + el_pos;

    return pos;
  }

  // erases element at pos
  void erase(iterator pos) {
    size_type el_pos = pos - vector_;
    size_type new_size = size_ - 1;
    iterator new_vector = MemAlloc(new_size);
    for (auto it = begin(), it_new = new_vector; it != pos; ++it, ++it_new) {
      *it_new = *it;
    }
    for (auto it = citpos(el_pos), it_new = new_vector + el_pos;
         it_new != new_vector + new_size; ++it, ++it_new) {
      *it_new = *(it + 1);
    }
    FreeVector(begin());
    vector_ = new_vector;
    size_ = new_size;
  }

  // iterator new_vector = MemAlloc(new_size);
  void push_back(const_reference value) { insert(end(), value); }

  // removes the last element
  void pop_back() { erase(end() - 1); }

  // swaps the contents
  void swap(Vector &other) {
    Vector<T> tmp_vec1(size_);
    VectorCopy(tmp_vec1, *this, 0, size_);

    size_type tmp_size1 = size_;
    size_type tmp_cap1 = capacity_;
    Vector<T> tmp_vec2(other.size_);
    VectorCopy(tmp_vec2, other, 0, other.size_);

    size_type tmp_size2 = other.size_;
    size_type tmp_cap2 = other.capacity_;
    size_ = tmp_size2;
    capacity_ = tmp_cap2;
    *this = tmp_vec2;
    other.size_ = tmp_size1;
    other.capacity_ = tmp_cap1;
    other = tmp_vec1;
  }

  // equality check
  bool EqVector(std::vector<T> &lib_vector) {
    bool out = true;
    if (size() != lib_vector.size()) return false;
    for (auto it = begin(), l_it = lib_vector.begin(); it < end();
         ++it, ++l_it) {
      if (*it != *l_it) {
        out = false;
        break;
      }
    }

    return out;
  }

  // inserts new elements into the container directly before pos
  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    Vector<value_type> new_vector = {args...};
    iterator pos_i{const_cast<iterator>(pos)};
    for (auto it = new_vector.begin(); it != new_vector.end(); ++it) {
      pos_i = insert(pos_i, *it);
      ++pos_i;
    }

    return pos_i - 1;
  }

  // appends new elements to the end of the container
  template <class... Args>
  void emplace_back(Args &&...args) {
    Vector<value_type> new_vector = {args...};
    for (auto it = new_vector.begin(); it != new_vector.end(); ++it) {
      push_back(*it);
    }
  }

  void print() {
    for (size_type i = 0; i < size_; ++i) {
      std::cout << vector_[i] << ' ' << std::endl;
    }
    std::cout << std::endl;
  }

  // bubble sort vector
  void sort() {
    for (auto it = begin(); it != end(); ++it) {
      for (auto it1 = begin(); it1 != end() - 1; ++it1) {
        if (*it1 > *(it1 + 1)) {
          value_type tmp_val = *it1;
          *it1 = *(it1 + 1);
          *(it1 + 1) = tmp_val;
        }
      }
    }
  }

  // checks equality of s21 vector to lib vector
  bool operator==(std::vector<T> &lib_vector) { return EqVector(lib_vector); }

 private:
  // move elements of one vector to another
  void VectorMove(Vector &other) {
    this->vector_ = other.begin();
    this->size_ = other.size();
    this->capacity_ = other.capacity();

    other.vector_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  // copy elements of one vector to another
  void VectorCopy(Vector &dest, const Vector &src, size_type from_i,
                  size_type to_size) {
    auto it_src = src.citpos(from_i);
    auto it_dest = dest.itpos(from_i);
    for (; it_dest != dest.itpos(to_size);
         *it_dest = *it_src, ++it_src, ++it_dest) {
      ;
    }
  }

  // allocate memory of definite size with check, returns iter/pointer to
  // allocated memory
  iterator MemAlloc(size_type alloc_size = size()) {
    iterator out = nullptr;
    try {
      out = new value_type[alloc_size];
    } catch (std::bad_alloc const &) {
      std::cerr << "Memory not allocated" << std::endl;
    }

    return out;
  }

  // frees memory
  void FreeVector(iterator it = begin()) { delete[] it; }

  // attributes
  size_type size_;      // size of vector
  size_type capacity_;  // capacity of vector
  T *vector_;           // pointer to a memory area for vector elements
};

}  // namespace s21
#endif