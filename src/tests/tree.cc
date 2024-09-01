#include <iostream>
#include <map>
#include <string>
#include <iostream>

template<class Key, class T, typename size_type = size_t> 
class Map{
public:

class MapIterator;
class MapConstIterator;

// Map Member type

// 	Key the first template parameter (Key)
using key_type = Key;

// T the second template parameter (T)
using mapped_type = T;

// Key-value pair
using value_type = std::pair<key_type, mapped_type>;

// the reference to an element
using reference = value_type&;

//  defines the type of the constant reference
using const_reference = const value_type&;

// defines the type for iterating through the container
using iterator = MapIterator;

// defines the constant type for iterating through the container
using const_iterator = MapConstIterator;

struct Node{
	value_type data_;
	// указатель на левое поддерево
	Node *left_;
	// указатель на правое поддерево
	Node *right_;
	// указатель на передыдущий узел
	Node *parent_; 
	// баланс = выстота правого поддерева - левое поддерево
	int balance_;
};

// ITERATOR CLASS
    class MapIterator {

    public:

	MapIterator() : it_ptr_(nullptr) {}

	MapIterator(Node* ptr) : it_ptr_(ptr) {}

	MapIterator(const MapIterator& it) {
	    it_ptr_ = it.it_ptr_;
	}

	MapIterator& operator=(const MapIterator& it) {
	    it_ptr_ = it.it_ptr_;
	    return *this;
	}

	bool operator==(const MapIterator& it) const {
	    return it_ptr_ == it.it_ptr_;
	}

	bool operator!=(const MapIterator& it) const {
	    return it_ptr_ != it.it_ptr_;
	}

	// pre-increment
	MapIterator& operator++() {
	    if (it_ptr_->right_) {
		it_ptr_ = it_ptr_->right_;
		while (it_ptr_->left_) {
		    it_ptr_ = it_ptr_->left_;
		}
	    } else {
		// Node* before = nullptr;
		// do {
		//     before = it_ptr_;
		//     it_ptr_ = it_ptr_->parent_;
		// } while (it_ptr_ && before == it_ptr_->right_);
	    // }
		Node* prev = it_ptr_;
		it_ptr_ = it_ptr_->parent_;
		while (it_ptr_ && prev == it_ptr_->right_) {
		    prev = it_ptr_;
		    it_ptr_ = it_ptr_->parent_;
		}
	    }
	    return *this;
	}

	// post-increment
	MapIterator operator++(int) {
	    MapIterator old(*this);
	    ++(*this);
	    return old;
	}

	// pre-decrement
	MapIterator& operator--() {
	    if (it_ptr_->left_) {
		it_ptr_ = it_ptr_->left_;
		while (it_ptr_->right_) {
		    it_ptr_ = it_ptr_->right_;
		}
	    } else {
		// Node* before;
		// do {
		//     before = it_ptr_;
		//     it_ptr_ = it_ptr_->parent_;
		// } while (it_ptr_ && before == it_ptr_->left_);
		Node* prev = it_ptr_;
		it_ptr_ = it_ptr_->parent_;
		while (it_ptr_ && prev == it_ptr_->left_) {
		    prev = it_ptr_;
		    it_ptr_ = it_ptr_->parent_;
		}		
	    }
	    return *this;
	}

	// post-decrement
	MapIterator operator--(int) {
	    MapIterator old(*this);
	    --(*this);
	    return old;
	}

	reference operator*() const {
	    return it_ptr_->data_;
	}

	value_type* operator->() const {
	    return &(it_ptr_->data_);
	}

	Node *it_ptr_;
    };

// CONST ITERATOR CLASS
    class MapConstIterator {

    public:

	MapConstIterator() : it_ptr_(nullptr) {}

	MapConstIterator(Node* ptr) : it_ptr_(ptr) {}

	MapConstIterator(const MapConstIterator& it) {
	    it_ptr_ = it.it_ptr_;
	}

	MapConstIterator& operator=(const MapConstIterator& it) {
	    it_ptr_ = it.it_ptr_;
	    return *this;
	}

	bool operator==(const MapConstIterator& it) const {
	    return it_ptr_ == it.it_ptr_;
	}

	bool operator!=(const MapConstIterator& it) const {
	    return it_ptr_ != it.it_ptr_;
	}

	// pre-increment
	MapConstIterator& operator++() {
	    if (it_ptr_->right_) {
		it_ptr_ = it_ptr_->right_;
		while (it_ptr_->left_) {
		    it_ptr_ = it_ptr_->left_;
		}
	    } else {
		// Node* before = nullptr;
		// do {
		//     before = it_ptr_;
		//     it_ptr_ = it_ptr_->parent_;
		// } while (it_ptr_ && before == it_ptr_->right_);
	    // }
		Node* prev = it_ptr_;
		it_ptr_ = it_ptr_->parent_;
		while (it_ptr_ && prev == it_ptr_->right_) {
		    prev = it_ptr_;
		    it_ptr_ = it_ptr_->parent_;
		}
	    }
	    return *this;
	}

	// post-increment
	MapConstIterator operator++(int) {
	    MapConstIterator old(*this);
	    ++(*this);
	    return old;
	}

	// pre-decrement
	MapConstIterator& operator--() {
	    if (it_ptr_->left_) {
		it_ptr_ = it_ptr_->left_;
		while (it_ptr_->right_) {
		    it_ptr_ = it_ptr_->right_;
		}
	    } else {
		// Node* before;
		// do {
		//     before = it_ptr_;
		//     it_ptr_ = it_ptr_->parent_;
		// } while (it_ptr_ && before == it_ptr_->left_);
		Node* prev = it_ptr_;
		it_ptr_ = it_ptr_->parent_;
		while (it_ptr_ && prev == it_ptr_->left_) {
		    prev = it_ptr_;
		    it_ptr_ = it_ptr_->parent_;
		}
	    }
	    return *this;
	}

	// post-decrement
	MapConstIterator operator--(int) {
	    MapConstIterator old(*this);
	    --(*this);
	    return old;
	}

//заменить на reference
	reference operator*() const {
	    return it_ptr_->data_;
	}

	value_type* operator->() const {
	    return &(it_ptr_->data_);
	}

	const Node *it_ptr_;
    };

// Map Member functions

// default constructor, creates empty map
Map() : root_(nullptr), size_(0) {};

// initializer list constructor, 
// creates the map initizialized using std::initializer_list
Map(std::initializer_list<value_type> const &items) : Map() {
    for (auto& itm : items) {
      Insert(itm);
    }
}

// copy constructor
Map(const Map &m) : Map() {
	if (this != &m) {
      clear(this->root_);
	  root_ = nullptr;
      for (MapIterator it = m.begin(); it != m.end(); ++it) {
        Insert(*it);
      }
    }
}

// move constructor
Map(Map &&m) : Map() {
    std::swap(root_, m.root_);
    std::swap(size_, m.size_);
}

// 	destructor
~Map() {
	clear(root_);
};

// подружить с const
  Map& operator=(Map& m) {
    if (this != &m) {
      clear(this->root_);
	  root_ = nullptr;
      for (MapIterator it = m.begin(); it != m.end(); ++it) {
        Insert(*it);
      }
    }
    return *this;
  }

  Map& operator=(Map&& m) {
    std::swap(root_, m.root_);
    std::swap(size_, m.size_);
    return *this;
  }

T& at(const Key& key) {
	for (auto it = begin(); it != end(); ++it) {
		if ((*it).first == key) return (*it).second;
	}
    throw std::out_of_range("Trying to access an element out of vector's range");
}

size_t size() {return size_;}

MapIterator begin() {return begin_node (root_);}
MapIterator end() {return MapIterator();}

MapIterator begin_node(Node *node) {
	MapIterator out(node);
	Node *out_node = out.it_ptr_;
	while (out_node->left_ != nullptr) {
		out_node = out_node->left_;
	}
	out.it_ptr_ = out_node;
	return out;
}

// добавление узла в дерево поиска
void Insert (const_reference value) {
	InsertToSubTree(root_, value, root_);
	size_++;
}

// поиск узла с минимальным ключом в дереве 
Node* FindMin(Node* node) {
	Node *out;
	if (node->left_) {
		out = FindMin(node->left_);
	} else {
		out = node;
	}
	
	return out;
}

// удаление узла с минимальным ключом из дерева
Node* RemoveMin(Node* node) {
	if(node->left_ == 0) return node->right_;
	node->left_ = RemoveMin(node->left_);
	return node;
}
void Erase (MapIterator pos) {
	EraseFrSubTree(pos, root_);
	size_--;
}

void EraseFrSubTree (MapIterator pos, Node * node) {
// сохранили указатели удаленного узла
	Node * LeftSubTree = pos.it_ptr_->left_;	
	Node * RightSubTree = pos.it_ptr_->right_;
	Node * ParentNode = pos.it_ptr_->parent_;
	 
	// 
	if (LeftSubTree == nullptr && RightSubTree == nullptr) {
		if (pos.it_ptr_->data_ > ParentNode->data_) {
			ParentNode->right_ = nullptr;
		} else if (pos.it_ptr_->data_ < ParentNode->data_) {
			ParentNode->left_ = nullptr;
		}
	} else {
		if (RightSubTree != nullptr) {
		Node* min = FindMin(RightSubTree);
		min->right_ = RemoveMin(RightSubTree);
		min->left_ = LeftSubTree;
		min->parent_ = ParentNode;
		if (LeftSubTree != nullptr) {
			LeftSubTree->parent_ = min;
		}
		if (ParentNode != nullptr) {
			if (pos.it_ptr_->data_ > ParentNode->data_) {
				ParentNode->right_ = min;
			} else if (pos.it_ptr_->data_ < ParentNode->data_) {
				ParentNode->left_ = min;
			}
		} else {
			RightSubTree->parent_ = min;
			root_ = min;
		}
		

		SetBalance(min);
		} else if (LeftSubTree != nullptr) {
		Node* min = FindMin(LeftSubTree);
		min->right_ = RemoveMin(LeftSubTree);
		min->left_ = RightSubTree;
		min->parent_ = ParentNode;
		if (RightSubTree != nullptr) {
			RightSubTree->parent_ = min;
		}
		if (ParentNode != nullptr) {
			if (pos.it_ptr_->data_ > ParentNode->data_) {
				ParentNode->right_ = min;
			} else if (pos.it_ptr_->data_ < ParentNode->data_) {
				ParentNode->left_ = min;
			}
		} else {
			RightSubTree->parent_ = min;
			root_ = min;
		}
		SetBalance(min);
		}
	}
	
	SetBalance(root_);
}

void Swap(Map& other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
}

void output() {
	output_sim(root_);
}

void print() {
	int h = Height(root_);
	int prob = 3;
	if (root_) {
		for (int i = 0; i <= h; i++) {
			print_n(root_, i, 0, prob*(h - i));
			std::cout << std::endl;
		}
	}
}

private:

// корень дерева
	Node *root_;
	size_type size_; 

	int Height(Node *root_) {
	int out = 0;
	if (root_ == nullptr) return 0;
	// вычисляем высоту правого и левого дерева
	int hLeft = Height(root_->left_);
	int hRight = Height(root_->right_);
	if (hLeft > hRight) {
		out = hLeft + 1;
	} else {
		out = hRight + 1;
	}
	
	return out;
}

//нахождение баланса текущего узла
	void SetBalance(Node *(&node)) {
		if (node != nullptr)
		node->balance_ = Height(node->right_) - Height(node->left_);	
	}

	void clear (Node *p) {
	if (p != nullptr) {
		clear(p->left_);
		clear(p->right_);

		delete p;
		p = nullptr;
	}
    }

//      X                          B
//    /   \                      /   \ 
//   /      B        ---->      X     \ 
//  /     /   \                /  \    \ 
// T1   T2     T3            T1    T2   T3

// левый поворот авл-дерева
void TurnLeft(Node *(&node)) {
	Node *oldest_parent = node->parent_;
	Node *RightSubTree = nullptr;
	Node *RightSubTreeLeftSubTree = nullptr;

	RightSubTree = node->right_;
	RightSubTree->parent_ = node;
	RightSubTreeLeftSubTree = RightSubTree->left_;
	if (RightSubTreeLeftSubTree)	
	RightSubTreeLeftSubTree->parent_ = RightSubTree;


	RightSubTree->left_ = node; //ок
	RightSubTree->parent_ = oldest_parent; //ok
	node->right_ = RightSubTreeLeftSubTree; // ok
	node->parent_ = RightSubTree;
	node = RightSubTree;

	SetBalance(node->left_);
	SetBalance(node);
}

//       X                         A
//     /   \                      /  \ 
//    A     \        ---->       /    X
//  /   \    \                  /   /   \ 
// T1   T2   T3                T1  T2    T3

// правый поворот авл-дерева
void TurnRight(Node *(&node)) {
	Node *oldest_parent = node->parent_;
	Node *LeftSubTree = nullptr;
	Node *LeftSubTreeRightSubTree = nullptr;

	LeftSubTree = node->left_;
	LeftSubTree->parent_ = node;
	LeftSubTreeRightSubTree = LeftSubTree->right_;
	if (LeftSubTreeRightSubTree)
	LeftSubTreeRightSubTree->parent_ = LeftSubTree;

	LeftSubTree->right_ = node;
	LeftSubTree->parent_ = oldest_parent;
	node->left_ = LeftSubTreeRightSubTree;
	node->parent_ = LeftSubTree;
	node = LeftSubTree;

	SetBalance(node->right_);
	SetBalance(node);
}

// добавление узла в дерево поиска
void InsertToSubTree (Node *(&root), value_type value, Node *parent_node) {
if (root == nullptr) {
	// создаем узел
	root = new Node;
	if (parent_node != nullptr) root->parent_ = parent_node;
	root->left_ = nullptr;
	root->right_ = nullptr;
	root->balance_ = 0;
	root->data_ = value;
} else {
	parent_node = root;
	if (value.first > root->data_.first) {
		InsertToSubTree(root->right_, value, parent_node);
		if (Height(root->right_) - Height(root->left_) > 1) {
			if (Height(root->right_->right_) < Height(root->right_->left_)) {
				TurnRight(root->right_);
			}
			TurnLeft(root);
		}
	} else if (value.first < root->data_.first) {
		InsertToSubTree(root->left_, value, parent_node);
		if (Height(root->left_) - Height(root->right_) > 1) {
			if (Height(root->left_->left_) < Height(root->left_->right_)) {
				TurnLeft(root->left_);
			}
			TurnRight(root);
		}
	}
	SetBalance(root);
}
}

void output_sim(Node *p) {
	if (p != nullptr) {
		output_sim(p->left_);
		std::cout << p->data_.first << " ";
		output_sim(p->right_);
	}
}

void print_n(const Node *p, int n, int level, int prob) {
	if (p) {
		if (level == n) {
			for (int i = 1; i <= prob; i++) std::cout << " ";
			std::cout << p->data_.first;
		} else {
			print_n(p->left_, n, level + 1, prob);
			print_n(p->right_, n, level + 1, prob);
		}
	}
}

};






// #include <iostream>
// #include <utility>

// struct Node1 {
//     using value_type = std::pair<int, int>;
//     value_type data_;
// };

int main()
{
//     Node1 node;
//     std::pair<int, int> pair = std::make_pair(5, 1);
//     node.data_ = pair;

//     std::cout << "Data: " << node.data_.first << ", " << node.data_.second << std::endl;

//     return 0;
// }
	Map<int, int> tree;
	Map<int, int> tree1 = {std::pair(5, 1), std::pair(-1, 2), std::pair(3, 3), std::pair(2, 5)};
	std::pair<int, int> aaa = std::pair(5, 1); 
	tree.Insert(aaa);
	tree.Insert(std::pair(-1, 2));
	tree.Insert(std::pair(3, 3));
	tree.Insert(std::pair(7, 4));
	tree.Insert(std::pair(2, 5));
	tree.Insert(std::pair(1, 6));
	tree.Insert(std::pair(-4, 7));	
	tree.Insert(std::pair(4, 8));
	tree.Insert(std::pair(10, 9));
	std::cout << "печать элемента:"<< tree.at(7) << std::endl;
	;	
	std::cout << "симметричная печать дерева:" << std::endl;
	tree.output();
		std::cout << "симметричная печать дерева1:" << std::endl;

	tree1 = tree;	
	tree1.output();
	std::cout << std::endl;
	std::cout << "печать дерева:" << std::endl;
	tree.print();
	std::cout << "печать дерева по итераторам:" << std::endl;
	for (auto it = tree.begin(); it != tree.end(); it++)
	{
		std::cout << (*it).first << ", " << (*it).second << "	";
	}
	std::cout << std::endl;
	// std::cout << "число элементов:" << std::endl;
	// std::cout << tree.size() << std::endl;
	// auto itt = tree.begin();
	// itt++; // -1
	// itt++; // 1
	// itt++; // 2
	// itt++; // 3
	// itt++; // 4
	// itt++; // 5
	// itt++; // 7
	// itt++; // 10
	// tree.Erase(itt);
	// std::cout << "печать дерева по итераторам:" << std::endl;
	// for (auto it = tree.begin(); it != tree.end(); it++)
	// {
	// 	std::cout << *it.first << " ";
	// }
	// std::cout << std::endl;
	// std::cout << "печать дерева:" << std::endl;
	// tree.print();
	// itt++;
	// itt++;
	// 	tree.Erase(itt);
	// std::cout << "печать дерева по итераторам:" << std::endl;
	// for (auto it = tree.begin(); it != tree.end(); it++)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;
	// std::cout << "печать дерева:" << std::endl;
	// tree.print();
	// std::cout << "число элементов:" << std::endl;
	// std::cout << tree.size() << std::endl;

	// AVL_Tree<int> tree1;
	// tree1.Insert(12);
	// tree1.Insert(10);
	// tree1.Insert(15);

	// tree.Swap(tree1);
	// std::cout << "печать дерева:" << std::endl;
	// tree.print();
	// std::cout << "печать дерева:" << std::endl;
	// tree1.print();

	// std::map<int, std::string> Testing_Map;
	// Testing_Map.insert(std::pair(5, "a"));
	// Testing_Map.insert(std::pair(-1, "b"));
	// Testing_Map.insert(std::pair(3, "b"));
	// Testing_Map.insert(std::pair(7, "b"));
	// Testing_Map.insert(std::pair(2, "b"));
	// Testing_Map.insert(std::pair(1,"b"));
	// Testing_Map.insert(std::pair(-4,"b"));
	// Testing_Map.insert(std::pair(4,"2"));
	// Testing_Map.insert(std::pair(10,"2"));

	// std::map<int, std::string>::iterator itt = Testing_Map.end();
	// itt--;
    // std::cout << itt->first << std::endl;

}
