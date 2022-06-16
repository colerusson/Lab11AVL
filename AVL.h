#ifndef AVL_H
#define AVL_H
#include "AVLInterface.h"
#include <string>
using namespace std;

template<typename T>
class AVL : public AVLInterface<T> {
private: 
	struct Node {		//Node struct nested within the BST template class
		struct Node* left_;		//left and right nodes to use in a tree
		struct Node* right_;
		T data_;
		int level_;

		Node(T data, Node* left = NULL, Node* right = NULL) :		//constructor for struct node, passing in data and setting left and right to NULL
			data_(data), left_(left), right_(right), level_(0) {}
		~Node() = default;

		friend ostream& operator<<(ostream& os, const struct Node* node) {		//friend operator to print out data
			os << node->data_;
			return os;
		}
	};
	Node* root;		//head or root node of the tree

	bool insert(Node*& node, const T& data) {		//insert recursive function which is called from the public section of BST class
		if (node == NULL) {
			node = new Node(data);
			return true;
		}
		if (data < node->data_) return insert(node->left_, data);
		if (data > node->data_) return insert(node->right_, data);
		return false;
	}

	bool deleteNode(Node*& node, const T& data) {		//delete item recursive function which is called from the public section of BST class
		if (node == NULL) return false;
		if (data < node->data_) return deleteNode(node->left_, data);
		if (data > node->data_) return deleteNode(node->right_, data);

		Node* oldNode = node;
		if (node->left_ == NULL) node = node->right_;
		else if (node->right_ == NULL) node = node->left_;
		else {
			Node* predecessor = node->left_;
			while (predecessor->right_ != NULL) predecessor = predecessor->right_;
			swap(node->data_, predecessor->data_);
			deleteNode(node->left_, data);
			return true;
		}
		delete oldNode;
		return true;
	}

	bool deleteTree(Node* node) {		//clear tree recursive function which is called from the public section of BST class
		if (node == NULL) return false;
		deleteTree(node->left_);
		deleteTree(node->right_);
		delete node;
		root = NULL;
		return true;
	}

	int size(Node* node) {		//size recursive function which is called from the public section of BST class
		if (node == NULL) {
			return 0;
		}
		else {
			return(size(node->left_) + 1 + size(node->right_));
		}
	}

	bool find(Node* node, const T& value) {		//find recursive function which is called from the public section of BST class
		if (node == NULL) return false;
		if (node->data_ == value) return true;
		if (value < node->data_) return find(node->left_, value);
		return find(node->right_, value);
	}

public:
	AVL() : root(NULL) {}
	~AVL() { clearTree(); }

	virtual bool addNode(const T& data) {
		return insert(root, data);
	}

	virtual bool removeNode(const T& data) {
		deleteNode(root, data);
		return true;
	}

	virtual bool clearTree() {
		return deleteTree(root);
	}

	virtual size_t sizeTree() {
		return size(root);
	}

	bool findValue(const T& value) {		//findValue function which calls a recursive function in the private section
		return find(root, value);
	}

	virtual std::string toString() const {
		stringstream out;
		if (root == NULL) out << " empty";
		else {
			int level = 0;
			do {
				out << endl << "  " << ++level << ":";
			} while (outLevel(root, level, out));
		}
		return out.str();
	}

	bool outLevel(Node* root, int level, stringstream& out) const {		//function which handles level order output of the tree
		if (root == NULL) return false;
		if (level == 1) {
			out << " " << root->data_;
			if ((root->left_ != NULL) || (root->right_ != NULL)) return true;
			return false;
		}
		if ((level == 2) && !root->left_ && root->right_) out << " _";
		bool left = outLevel(root->left_, level - 1, out);
		bool right = outLevel(root->right_, level - 1, out);
		if ((level == 2) && root->left_ && !root->right_) out << " _";
		return left || right;
	}
};
#endif	// AVL_H