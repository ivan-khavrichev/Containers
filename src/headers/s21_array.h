#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERSPLUS_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERSPLUS_ARRAY_S21_ARRAY_H_

namespace s21 {

template <typename T, std::size_t Size = 0>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() {}
  array(std::initializer_list<value_type> const &items) {
    std::copy(items.begin(), items.end(), elems);
  }

  array(const array &a) {
    for (size_t i = 0; i < Size; i++) {
      elems[i] = a.elems[i];
    }
  }

  array(array &&a) {
    for (size_t i = 0; i < Size; i++) {
      elems[i] = std::move(a.elems[i]);
    }
  }

  ~array() = default;

  iterator begin() { return elems; }

  iterator end() { return elems + capacity; }
  iterator data() { return begin(); }

  reference at(size_type pos) { return (*this)[pos]; }
  const_reference front() {
    const_reference ref = elems[0];
    return ref;
  }

  const_reference back() {
    const_reference ref = elems[Size - 1];
    return ref;
  }

  bool empty() { return !capacity; }
  size_type size() { return capacity; }

  size_type max_size() { return capacity; }

  void swap(array &other) {
    T temp;
    for (size_t i = 0; i < capacity; ++i) {
      temp = elems[i];
      elems[i] = other.elems[i];
      other.elems[i] = temp;
    }
  }
  void fill(const_reference value) {
    for (size_t i = 0; i < capacity; ++i) {
      elems[i] = value;
    }
  }

  array &operator=(const array &other) {
    for (size_t i = 0; i < capacity; ++i) {
      elems[i] = other.elems[i];
    }

    return *this;
  }

  array &operator=(array &&other) {
    for (size_t i = 0; i < capacity; ++i) {
      elems[i] = std::move(other.elems[i]);
    }

    return *this;
  }
  reference operator[](size_type pos) {
    if (pos >= Size)
      throw std::out_of_range("s21:array operator[] - Index out of range");
    return elems[pos];
  }

  const_reference operator[](size_type pos) const {
    if (pos >= Size)
      throw std::out_of_range("s21:array operator[] - Index out of range");
    return elems[pos];
  }

 private:
  value_type elems[Size] = {};
  size_type capacity = Size;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERSPLUS_ARRAY_S21_ARRAY_H_
