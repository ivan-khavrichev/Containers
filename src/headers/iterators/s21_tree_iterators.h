#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_S21_TREE_ITERATORS_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_S21_TREE_ITERATORS_H_

#include "../s21_tree_node.h"

namespace s21 {
// ITERATOR CLASS

template <class T>
class TreeIterator {
 public:
  using value_type = T;
  using reference = value_type&;
  using TreeNodeIt = TreeNode<T>;

  TreeIterator() : it_ptr_(nullptr) {}

  TreeIterator(TreeNodeIt* ptr) : it_ptr_(ptr) {}

  TreeIterator(const TreeIterator& it) { it_ptr_ = it.it_ptr_; }

  TreeIterator& operator=(const TreeIterator& it) {
    it_ptr_ = it.it_ptr_;
    return *this;
  }

  bool operator==(const TreeIterator& it) const {
    return it_ptr_ == it.it_ptr_;
  }

  bool operator!=(const TreeIterator& it) const {
    return it_ptr_ != it.it_ptr_;
  }

  // pre-increment
  TreeIterator& operator++() {
    if (it_ptr_->right_) {
      it_ptr_ = it_ptr_->right_;
      while (it_ptr_->left_) {
        it_ptr_ = it_ptr_->left_;
      }
    } else {
      TreeNodeIt* prev = it_ptr_;
      it_ptr_ = it_ptr_->parent_;
      while (it_ptr_ && prev == it_ptr_->right_) {
        prev = it_ptr_;
        it_ptr_ = it_ptr_->parent_;
      }
    }
    return *this;
  }

  // post-increment
  TreeIterator operator++(int) {
    TreeIterator old(*this);
    ++(*this);
    return old;
  }

  // pre-decrement
  TreeIterator& operator--() {
    if (it_ptr_->left_) {
      it_ptr_ = it_ptr_->left_;
      while (it_ptr_->right_) {
        it_ptr_ = it_ptr_->right_;
      }
    } else {
      TreeNodeIt* prev = it_ptr_;
      it_ptr_ = it_ptr_->parent_;
      while (it_ptr_ && prev == it_ptr_->left_) {
        prev = it_ptr_;
        it_ptr_ = it_ptr_->parent_;
      }
    }
    return *this;
  }

  // post-decrement
  TreeIterator operator--(int) {
    TreeIterator old(*this);
    --(*this);
    return old;
  }

  reference operator*() const { return it_ptr_->data_; }

  value_type* operator->() const { return &(it_ptr_->data_); }

  TreeNodeIt* it_ptr_;
};

// CONST ITERATOR CLASS
template <class T>
class TreeConstIterator {
 public:
  using value_type = T;
  using const_reference = const value_type&;
  using TreeNodeCIt = TreeNode<T>;

  TreeConstIterator() : it_ptr_(nullptr) {}

  TreeConstIterator(const TreeNodeCIt* ptr) : it_ptr_(ptr) {}

  TreeConstIterator(const TreeConstIterator& it) { it_ptr_ = it.it_ptr_; }

  TreeConstIterator& operator=(const TreeConstIterator& it) {
    it_ptr_ = it.it_ptr_;
    return *this;
  }

  bool operator==(const TreeConstIterator& it) const {
    return it_ptr_ == it.it_ptr_;
  }

  bool operator!=(const TreeConstIterator& it) const {
    return it_ptr_ != it.it_ptr_;
  }

  // pre-increment
  TreeConstIterator& operator++() {
    if (it_ptr_->right_) {
      it_ptr_ = it_ptr_->right_;
      while (it_ptr_->left_) {
        it_ptr_ = it_ptr_->left_;
      }
    } else {
      const TreeNodeCIt* prev = it_ptr_;
      it_ptr_ = it_ptr_->parent_;
      while (it_ptr_ && prev == it_ptr_->right_) {
        prev = it_ptr_;
        it_ptr_ = it_ptr_->parent_;
      }
    }
    return *this;
  }

  // post-increment
  TreeConstIterator operator++(int) {
    TreeConstIterator old(*this);
    ++(*this);
    return old;
  }

  // pre-decrement
  TreeConstIterator& operator--() {
    if (it_ptr_->left_) {
      it_ptr_ = it_ptr_->left_;
      while (it_ptr_->right_) {
        it_ptr_ = it_ptr_->right_;
      }
    } else {
      const TreeNodeCIt* prev = it_ptr_;
      it_ptr_ = it_ptr_->parent_;
      while (it_ptr_ && prev == it_ptr_->left_) {
        prev = it_ptr_;
        it_ptr_ = it_ptr_->parent_;
      }
    }
    return *this;
  }

  // post-decrement
  TreeConstIterator operator--(int) {
    TreeConstIterator old(*this);
    --(*this);
    return old;
  }

  //заменить на reference
  const_reference operator*() const { return it_ptr_->data_; }

  const value_type* operator->() const { return &(it_ptr_->data_); }

  const TreeNodeCIt* it_ptr_;
};

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_S21_TREE_ITERATORS_H_