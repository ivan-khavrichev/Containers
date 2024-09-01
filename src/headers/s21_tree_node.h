#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_TREE_NODE_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_TREE_NODE_H_

namespace s21 {

// NODE STRUCT
template <class T>
struct TreeNode {
  using value_type = T;
  using const_reference = const value_type&;
  value_type data_;
  // указатель на левое поддерево
  TreeNode* left_ = nullptr;
  // указатель на правое поддерево
  TreeNode* right_ = nullptr;
  // указатель на передыдущий узел
  TreeNode* parent_ = nullptr;
  // баланс = выстота правого поддерева - левое поддерево
  int balance_;

  explicit TreeNode(const_reference data_input, TreeNode* left = nullptr,
                    TreeNode* right = nullptr, TreeNode* parent = nullptr)
      : data_(data_input), left_(left), right_(right), parent_(parent) {}
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_TREE_NODE_H_