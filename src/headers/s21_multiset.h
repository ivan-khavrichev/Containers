#ifndef __S21MultiSet_H__
#define __S21MultiSet_H__

#include "../s21_containers.h"
#include "./iterators/s21_tree_iterators.h"
#include "s21_tree_node.h"
#include "s21_vector.h"

using namespace s21;

namespace s21 {

template <class Key, typename size_type = size_t>
class MultiSet {
 public:
  // MultiSet Member type

  // 	Key the first template parameter (Key)
  using key_type = Key;

  // Key-value pair
  using value_type = Key;

  // tree node -> MultiSet node
  using MultiSetNode = TreeNode<value_type>;

  // tree iter -> MultiSet iterator
  using MultiSetIterator = TreeIterator<value_type>;
  // tree const iter -> MultiSet const iterator
  using MultiSetConstIterator = TreeConstIterator<value_type>;

  // the reference to an element
  using reference = value_type&;

  //  defines the type of the constant reference
  using const_reference = const value_type&;

  // defines the type for iterating through the container
  using iterator = MultiSetIterator;

  // defines the constant type for iterating through the container
  using const_iterator = MultiSetConstIterator;

  // MultiSet Member functions

  // default constructor, creates empty MultiSet
  MultiSet() : root_(nullptr), size_(0){};

  // initializer list constructor,
  // creates the MultiSet initizialized using std::initializer_list
  MultiSet(std::initializer_list<value_type> const& items) : MultiSet() {
    for (auto& itm : items) {
      insert(itm);
    }
  }

  // copy constructor
  MultiSet(const MultiSet& m) : MultiSet() {
    if (this != &m) {
      Clear(this->root_);
      root_ = nullptr;
      for (const_iterator it = m.begin(); it != m.end(); ++it) {
        Insert(*it);
      }
    }
  }

  // move constructor
  MultiSet(MultiSet&& m) : MultiSet() {
    std::swap(root_, m.root_);
    std::swap(size_, m.size_);
  }

  // 	destructor
  ~MultiSet() {
    if (root_ != nullptr) Clear(root_);
  };

  MultiSet& operator=(MultiSet& m) {
    if (this != &m) {
      clear(this->root_);
      root_ = nullptr;
      for (MultiSetIterator it = m.begin(); it != m.end(); ++it) {
        Insert(*it);
      }
    }
    return *this;
  }

  MultiSet& operator=(MultiSet&& m) {
    std::swap(root_, m.root_);
    std::swap(size_, m.size_);
    return *this;
  }

  // access specified element with bounds checking
  value_type& at(const Key& key) {
    iterator res = nullptr;
    Find(key, root_, res);
    if (res == nullptr)
      throw std::out_of_range("Trying to access an element out of range");
    return (*res).second;
  }

  // access or insert specified element
  value_type& operator[](const Key& key) {
    iterator res = nullptr;
    value_type tmp_val(key);
    Find(key, root_, res);
    if (res == nullptr) {
      std::pair<iterator, bool> result = Insert(tmp_val);
      return (*result.first).second;
    };
    return (*res).second;
  }

  // 	checks whether the container is empty
  bool empty() {
    bool out = false;
    if (size_ == 0) out = true;

    return out;
  }

  // returns the number of elements
  size_type size() const { return size_; }

  // returns the maximum possible number of elements
  size_type max_size() {
    return (std::numeric_limits<value_type>::max() * (sizeof(MultiSet) + 1) /
                2 +
            sizeof(MultiSet));
  }

  // MultiSet Iterators

  // returns an iterator to the beginning
  iterator begin() { return begin_node(root_); }

  const_iterator begin() const { return begin_node(root_); }

  // returns an iterator to the end
  iterator end() { return MultiSetIterator(); }

  const_iterator end() const { return MultiSetConstIterator(); }

  // clears the contents
  void clear() {
    Clear(root_);
    root_ = nullptr;
    size_ = 0;
  }

  // inserts node and returns iterator to where the element is in the container
  // and bool denoting whether the insertion took place
  iterator insert(const value_type& value) { return Insert(value); }

  // Inserts new elements into the container
  template <class... Args>
  Vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<value_type> insert_vector = {args...};
    Vector<std::pair<iterator, bool>> out_vector;
    auto ins_it = insert_vector.begin();
    for (; ins_it != insert_vector.end(); ++ins_it) {
      auto push_pair = insert(*ins_it);
      out_vector.push_back(push_pair);
    }

    return out_vector;
  }

  // erases element at pos
  void erase(iterator pos) {
    EraseFrSubTree(pos);
    size_--;
  }

  // swaps the contents
  void swap(MultiSet& other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }

  // splices nodes from another container
  void merge(MultiSet& other) {
    MultiSet<value_type> saved_other;
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(*it);
    }

    other = std::move(saved_other);
  }

  // finds element with specific key
  iterator find(const Key& key) {
    iterator out;
    Find(key, root_, out);

    return out;
  }

  const_iterator find(const Key& key) const {
    const_iterator out;
    Find(key, root_, out);

    return out;
  }

  // returns the number of elements matching specific key
  size_type count(const Key& key) {
    size_type out = 0;
    for (auto it = begin(); it != end(); ++it) {
      if (key == (*it)) {
        out++;
      }
    }

    return out;
  }

  // MultiSet Lookup

  // checks if the container contains element with specific key
  bool contains(const Key& key) { return !KeyIsUnique(key); }

  // returns range of elements matching a specific key
  std::pair<iterator, iterator> equal_range(const Key& key) {
    std::pair<iterator, iterator> out = std::make_pair(nullptr, nullptr);
    bool found_first = false;
    bool found_last = false;
    count(key);
    for (auto it = begin(); it != end(); ++it) {
      if (key == (*it) && found_first == false && found_last == false) {
        out.first = it;
        break;
      }
    }
    auto itt = out.first;
    while (itt != end()) {
      if (*(itt) == key) {
        itt++;
      } else {
        break;
      }
    }
    if (itt != nullptr) {
      out.second = itt;
    }

    return out;
  }

  // returns an iterator to the first element not less than the given key
  iterator lower_bound(const Key& key) { return equal_range(key).first; }

  // returns an iterator to the first element greater than the given key
  iterator upper_bound(const Key& key) { return equal_range(key).second; }

  void print() {
    output_sim(root_);
    std::cout << std::endl;
  }

 private:
  // корень дерева
  MultiSetNode* root_;
  // размер дерева
  size_type size_;

  iterator begin_node(MultiSetNode* node) {
    iterator out(node);
    MultiSetNode* out_node = out.it_ptr_;
    if (node != nullptr) {
      while (out_node->left_ != nullptr) {
        out_node = out_node->left_;
      }
      out.it_ptr_ = out_node;
    }

    return out;
  }

  const_iterator begin_node(MultiSetNode* node) const {
    const_iterator out(node);
    const MultiSetNode* out_node = out.it_ptr_;
    if (node != nullptr) {
      while (out_node->left_ != nullptr) {
        out_node = out_node->left_;
      }
      out.it_ptr_ = out_node;
    }

    return out;
  }

  // поиск узла с минимальным ключом в дереве
  MultiSetNode* FindMin(MultiSetNode* node) {
    MultiSetNode* out = nullptr;
    if (node->left_) {
      out = FindMin(node->left_);
    } else {
      out = node;
    }

    return out;
  }

  void EraseFrSubTree(MultiSetIterator pos) {
    MultiSetNode* LeftSubTree = pos.it_ptr_->left_;
    MultiSetNode* RightSubTree = pos.it_ptr_->right_;
    MultiSetNode* ParentNode = pos.it_ptr_->parent_;

    if (LeftSubTree == nullptr && RightSubTree == nullptr) {
      BothSubTreeCase(ParentNode, pos);
    } else {
      if (RightSubTree != nullptr) {
        RightSubTreeCase(LeftSubTree, RightSubTree, ParentNode, pos);
      } else if (LeftSubTree != nullptr) {
        LeftSubTreeCase(LeftSubTree, RightSubTree, ParentNode, pos);
      }
    }
    MultiSetBalance(root_);
    delete pos.it_ptr_;
  }

  void BothSubTreeCase(MultiSetNode* parent_node, iterator& pos) {
    if (pos.it_ptr_->data_ > parent_node->data_) {
      parent_node->right_ = nullptr;
    } else if (pos.it_ptr_->data_ < parent_node->data_) {
      parent_node->left_ = nullptr;
    }
  }

  void LeftSubTreeCase(MultiSetNode* left_tree, MultiSetNode* right_tree,
                       MultiSetNode* parent_node, iterator& pos) {
    MultiSetNode* min = FindMin(left_tree);
    min->right_ = RemoveMin(left_tree);
    min->left_ = right_tree;
    min->parent_ = parent_node;
    if (right_tree != nullptr) {
      right_tree->parent_ = min;
    }
    if (parent_node != nullptr) {
      if (pos.it_ptr_->data_ > parent_node->data_) {
        parent_node->right_ = min;
      } else if (pos.it_ptr_->data_ < parent_node->data_) {
        parent_node->left_ = min;
      }
    } else {
      right_tree->parent_ = min;
      root_ = min;
    }
    MultiSetBalance(min);
  }

  void RightSubTreeCase(MultiSetNode* left_tree, MultiSetNode* right_tree,
                        MultiSetNode* parent_node, iterator& pos) {
    MultiSetNode* min = FindMin(right_tree);
    min->right_ = RemoveMin(right_tree);
    min->left_ = left_tree;
    min->parent_ = parent_node;
    if (left_tree != nullptr) {
      left_tree->parent_ = min;
    }
    if (parent_node == nullptr) {
      right_tree->parent_ = min;
      root_ = min;
    } else {
      if (pos.it_ptr_->data_ > parent_node->data_) {
        parent_node->right_ = min;
      } else if (pos.it_ptr_->data_ < parent_node->data_) {
        parent_node->left_ = min;
      }
    }
    MultiSetBalance(min);
  }

  // удаление узла с минимальным ключом из дерева
  MultiSetNode* RemoveMin(MultiSetNode* node) {
    if (node->left_ == nullptr) return node->right_;
    node->left_ = RemoveMin(node->left_);
    return node;
  }

  int Height(MultiSetNode* node) {
    int out = 0;
    if (node == nullptr) return 0;
    // вычисляем высоту правого и левого дерева
    int hLeft = Height(node->left_);
    int hRight = Height(node->right_);
    if (hLeft > hRight) {
      out = hLeft + 1;
    } else {
      out = hRight + 1;
    }

    return out;
  }

  //нахождение баланса текущего узла
  void MultiSetBalance(MultiSetNode*(&node)) {
    if (node != nullptr)
      node->balance_ = Height(node->right_) - Height(node->left_);
  }

  void Clear(MultiSetNode* p) {
    if (p != nullptr) {
      if (p->left_ != nullptr) Clear(p->left_);
      if (p->right_ != nullptr) Clear(p->right_);
      if (p != nullptr) delete p;
      p = nullptr;
    }
  }

  /*
  //      X                          B
  //    /   \                      /   \
  //   /      B        ---->      X     \
  //  /     /   \                /  \    \
  // T1   T2     T3            T1    T2   T3
  */

  // левый поворот авл-дерева
  void TurnLeft(MultiSetNode*(&node)) {
    MultiSetNode* oldest_parent = node->parent_;
    MultiSetNode* RightSubTree = nullptr;
    MultiSetNode* RightSubTreeLeftSubTree = nullptr;

    RightSubTree = node->right_;
    RightSubTree->parent_ = node;
    RightSubTreeLeftSubTree = RightSubTree->left_;
    if (RightSubTreeLeftSubTree)
      RightSubTreeLeftSubTree->parent_ = RightSubTree;

    RightSubTree->left_ = node;              //ок
    RightSubTree->parent_ = oldest_parent;   // ok
    node->right_ = RightSubTreeLeftSubTree;  // ok
    node->parent_ = RightSubTree;
    node = RightSubTree;

    MultiSetBalance(node->left_);
    MultiSetBalance(node);
  }

  /*
  //       X                         A
  //     /   \                      /  \
  //    A     \        ---->       /    X
  //  /   \    \                  /   /   \
  // T1   T2   T3                T1  T2    T3
  */

  // правый поворот авл-дерева
  void TurnRight(MultiSetNode*(&node)) {
    MultiSetNode* oldest_parent = node->parent_;
    MultiSetNode* LeftSubTree = nullptr;
    MultiSetNode* LeftSubTreeRightSubTree = nullptr;

    LeftSubTree = node->left_;
    LeftSubTree->parent_ = node;
    LeftSubTreeRightSubTree = LeftSubTree->right_;
    if (LeftSubTreeRightSubTree) LeftSubTreeRightSubTree->parent_ = LeftSubTree;

    LeftSubTree->right_ = node;
    LeftSubTree->parent_ = oldest_parent;
    node->left_ = LeftSubTreeRightSubTree;
    node->parent_ = LeftSubTree;
    node = LeftSubTree;

    MultiSetBalance(node->right_);
    MultiSetBalance(node);
  }

  bool KeyIsUnique(key_type key) {
    bool out = true;
    for (auto it = begin(); it != end(); ++it) {
      if (key == (*it)) {
        out = false;
        break;
      }
    }

    return out;
  }

  // добавление узла в дерево поиска
  iterator Insert(const_reference value) {
    iterator out;
    InsertToSubTree(root_, value, root_);
    size_++;
    Find(value, root_, out);

    return out;
  }

  // поиск по ключу
  void Find(const key_type key, MultiSetNode* node, iterator& res) {
    value_type node_data = node->data_;
    if (key > node_data) {
      if (node->right_ != nullptr) Find(key, node->right_, res);
    } else if (key < node_data) {
      if (node->left_ != nullptr) Find(key, node->left_, res);
    } else if (key == node_data) {
      res.it_ptr_ = node;
    }
  }

  void Find(const key_type key, MultiSetNode* node, const_iterator& res) const {
    const value_type node_data = node->data_;
    if (key > node_data) {
      if (node->right_ != nullptr) Find(key, node->right_, res);
    } else if (key < node_data) {
      if (node->left_ != nullptr) Find(key, node->left_, res);
    } else if (key == node_data) {
      res.it_ptr_ = node;
    }
  }

  // добавление узла в дерево поиска
  void InsertToSubTree(MultiSetNode*(&node), const_reference value,
                       MultiSetNode* parent_node) {
    if (node == nullptr) {
      // создаем узел
      node = new MultiSetNode(value);
      node->left_ = nullptr;
      node->right_ = nullptr;
      node->balance_ = 0;
      if (parent_node != nullptr) node->parent_ = parent_node;
    } else {
      parent_node = node;
      if (value >= node->data_) {
        InsertToSubTree(node->right_, value, parent_node);
        MultiSetBalance(node);
        if (node->balance_ > 1) {
          MultiSetBalance(node->right_);
          if (node->right_->balance_ < 0) {
            TurnRight(node->right_);
          }
          TurnLeft(node);
        }
      } else if (value < node->data_) {
        InsertToSubTree(node->left_, value, parent_node);
        MultiSetBalance(node);
        if (node->balance_ < -1) {
          MultiSetBalance(node->left_);
          if (node->left_->balance_ > 0) {
            TurnLeft(node->left_);
          }
          TurnRight(node);
        }
      }
    }
  }

  void output_sim(MultiSetNode* p) {
    if (p != nullptr) {
      output_sim(p->left_);
      std::cout << "(" << p->data_ << ")"
                << " ";
      output_sim(p->right_);
    }
  }
};

}  // namespace s21

#endif