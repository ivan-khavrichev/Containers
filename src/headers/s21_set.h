#ifndef __S21SET_H__
#define __S21SET_H__

#include "../s21_containers.h"
#include "./iterators/s21_tree_iterators.h"
#include "s21_tree_node.h"
#include "s21_vector.h"

using namespace s21;

namespace s21 {

template <class Key, typename size_type = size_t>
class Set {
 public:
  // Set Member type

  // 	Key the first template parameter (Key)
  using key_type = Key;

  // Key-value pair
  using value_type = Key;

  // tree node -> Set node
  using SetNode = TreeNode<value_type>;

  // tree iter -> Set iterator
  using SetIterator = TreeIterator<value_type>;
  // tree const iter -> Set const iterator
  using SetConstIterator = TreeConstIterator<value_type>;

  // the reference to an element
  using reference = value_type&;

  //  defines the type of the constant reference
  using const_reference = const value_type&;

  // defines the type for iterating through the container
  using iterator = SetIterator;

  // defines the constant type for iterating through the container
  using const_iterator = SetConstIterator;

  // Set Member functions

  // default constructor, creates empty Set
  Set() : root_(nullptr), size_(0){};

  // initializer list constructor,
  // creates the Set initizialized using std::initializer_list
  Set(std::initializer_list<value_type> const& items) : Set() {
    for (auto& itm : items) {
      insert(itm);
    }
  }

  // copy constructor
  Set(const Set& m) : Set() {
    if (this != &m) {
      Clear(this->root_);
      root_ = nullptr;
      for (const_iterator it = m.begin(); it != m.end(); ++it) {
        Insert(*it);
      }
    }
  }

  // move constructor
  Set(Set&& m) : Set() {
    std::swap(root_, m.root_);
    std::swap(size_, m.size_);
  }

  // 	destructor
  ~Set() {
    if (root_ != nullptr) Clear(root_);
  };

  Set& operator=(Set& m) {
    if (this != &m) {
      clear(this->root_);
      root_ = nullptr;
      for (SetIterator it = m.begin(); it != m.end(); ++it) {
        Insert(*it);
      }
    }
    return *this;
  }

  Set& operator=(Set&& m) {
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
    return (std::numeric_limits<value_type>::max() * (sizeof(Set) + 1) / 2 +
            sizeof(Set));
  }

  // Set Iterators

  // returns an iterator to the beginning
  iterator begin() { return begin_node(root_); }

  const_iterator begin() const { return begin_node(root_); }

  // returns an iterator to the end
  iterator end() { return SetIterator(); }

  const_iterator end() const { return SetConstIterator(); }

  // clears the contents
  void clear() {
    Clear(root_);
    root_ = nullptr;
    size_ = 0;
  }

  // inserts node and returns iterator to where the element is in the container
  // and bool denoting whether the insertion took place
  std::pair<iterator, bool> insert(const value_type& value) {
    return Insert(value);
  }

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
  void swap(Set& other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }

  // splices nodes from another container
  void merge(Set& other) {
    Set<value_type> saved_other;
    for (auto it = other.begin(); it != other.end(); ++it) {
      auto insert_result = insert(*it);
      if (insert_result.second == false) {
        saved_other.insert(*it);
      }
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

  // Set Lookup
  bool contains(const Key& key) { return !KeyIsUnique(key); }

  void print() {
    output_sim(root_);
    std::cout << std::endl;
  }

 private:
  // корень дерева
  SetNode* root_;
  // размер дерева
  size_type size_;

  iterator begin_node(SetNode* node) {
    iterator out(node);
    SetNode* out_node = out.it_ptr_;
    if (node != nullptr) {
      while (out_node->left_ != nullptr) {
        out_node = out_node->left_;
      }
      out.it_ptr_ = out_node;
    }

    return out;
  }

  const_iterator begin_node(SetNode* node) const {
    const_iterator out(node);
    const SetNode* out_node = out.it_ptr_;
    if (node != nullptr) {
      while (out_node->left_ != nullptr) {
        out_node = out_node->left_;
      }
      out.it_ptr_ = out_node;
    }

    return out;
  }

  // поиск узла с минимальным ключом в дереве
  SetNode* FindMin(SetNode* node) {
    SetNode* out = nullptr;
    if (node->left_) {
      out = FindMin(node->left_);
    } else {
      out = node;
    }

    return out;
  }

  void EraseFrSubTree(SetIterator pos) {
    SetNode* LeftSubTree = pos.it_ptr_->left_;
    SetNode* RightSubTree = pos.it_ptr_->right_;
    SetNode* ParentNode = pos.it_ptr_->parent_;

    if (LeftSubTree == nullptr && RightSubTree == nullptr) {
      BothSubTreeCase(ParentNode, pos);
    } else {
      if (RightSubTree != nullptr) {
        RightSubTreeCase(LeftSubTree, RightSubTree, ParentNode, pos);
      } else if (LeftSubTree != nullptr) {
        LeftSubTreeCase(LeftSubTree, RightSubTree, ParentNode, pos);
      }
    }
    SetBalance(root_);
    delete pos.it_ptr_;
  }

  void BothSubTreeCase(SetNode* parent_node, iterator& pos) {
    if (pos.it_ptr_->data_ > parent_node->data_) {
      parent_node->right_ = nullptr;
    } else if (pos.it_ptr_->data_ < parent_node->data_) {
      parent_node->left_ = nullptr;
    }
  }

  void LeftSubTreeCase(SetNode* left_tree, SetNode* right_tree,
                       SetNode* parent_node, iterator& pos) {
    SetNode* min = FindMin(left_tree);
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
    SetBalance(min);
  }

  void RightSubTreeCase(SetNode* left_tree, SetNode* right_tree,
                        SetNode* parent_node, iterator& pos) {
    SetNode* min = FindMin(right_tree);
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
    SetBalance(min);
  }

  // удаление узла с минимальным ключом из дерева
  SetNode* RemoveMin(SetNode* node) {
    if (node->left_ == nullptr) return node->right_;
    node->left_ = RemoveMin(node->left_);
    return node;
  }

  int Height(SetNode* node) {
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
  void SetBalance(SetNode*(&node)) {
    if (node != nullptr)
      node->balance_ = Height(node->right_) - Height(node->left_);
  }

  void Clear(SetNode* p) {
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
  void TurnLeft(SetNode*(&node)) {
    SetNode* oldest_parent = node->parent_;
    SetNode* RightSubTree = nullptr;
    SetNode* RightSubTreeLeftSubTree = nullptr;

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

    SetBalance(node->left_);
    SetBalance(node);
  }

  /*
  //       X                         A
  //     /   \                      /  \
  //    A     \        ---->       /    X
  //  /   \    \                  /   /   \
  // T1   T2   T3                T1  T2    T3
  */

  // правый поворот авл-дерева
  void TurnRight(SetNode*(&node)) {
    SetNode* oldest_parent = node->parent_;
    SetNode* LeftSubTree = nullptr;
    SetNode* LeftSubTreeRightSubTree = nullptr;

    LeftSubTree = node->left_;
    LeftSubTree->parent_ = node;
    LeftSubTreeRightSubTree = LeftSubTree->right_;
    if (LeftSubTreeRightSubTree) LeftSubTreeRightSubTree->parent_ = LeftSubTree;

    LeftSubTree->right_ = node;
    LeftSubTree->parent_ = oldest_parent;
    node->left_ = LeftSubTreeRightSubTree;
    node->parent_ = LeftSubTree;
    node = LeftSubTree;

    SetBalance(node->right_);
    SetBalance(node);
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
  std::pair<iterator, bool> Insert(const_reference value) {
    std::pair<iterator, bool> out = std::pair(nullptr, false);
    if (KeyIsUnique(value)) {
      InsertToSubTree(root_, value, root_);
      out.second = true;
      size_++;
    } else {
      out.second = false;
    }
    Find(value, root_, out.first);

    return out;
  }

  // поиск по ключу
  void Find(const key_type key, SetNode* node, iterator& res) {
    value_type node_data = node->data_;
    if (key > node_data) {
      if (node->right_ != nullptr) Find(key, node->right_, res);
    } else if (key < node_data) {
      if (node->left_ != nullptr) Find(key, node->left_, res);
    } else if (key == node_data) {
      res.it_ptr_ = node;
    }
  }

  void Find(const key_type key, SetNode* node, const_iterator& res) const {
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
  void InsertToSubTree(SetNode*(&node), const_reference value,
                       SetNode* parent_node) {
    if (node == nullptr) {
      // создаем узел
      node = new SetNode(value);
      node->left_ = nullptr;
      node->right_ = nullptr;
      node->balance_ = 0;
      if (parent_node != nullptr) node->parent_ = parent_node;
    } else {
      parent_node = node;
      if (value > node->data_) {
        InsertToSubTree(node->right_, value, parent_node);
        SetBalance(node);
        if (node->balance_ > 1) {
          SetBalance(node->right_);
          if (node->right_->balance_ < 0) {
            TurnRight(node->right_);
          }
          TurnLeft(node);
        }
      } else if (value < node->data_) {
        InsertToSubTree(node->left_, value, parent_node);
        SetBalance(node);
        if (node->balance_ < -1) {
          SetBalance(node->left_);
          if (node->left_->balance_ > 0) {
            TurnLeft(node->left_);
          }
          TurnRight(node);
        }
      }
    }
  }

  void output_sim(SetNode* p) {
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