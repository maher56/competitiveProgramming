#include<bits/stdc++.h>
using namespace std;
// data structure that represents a node in the tree
struct Node {
	int data; // holds the key
	Node *parent; // pointer to the parent
	Node *left; // pointer to left child
	Node *right; // pointer to right child
};

typedef Node *node;

// class SplayTree implements the operations in Splay tree
class SplayTree {
private:
	node root;

	void preOrder(node cur) {
		if (cur != nullptr) {
			cout<<cur->data<<" ";
			preOrder(cur->left);
			preOrder(cur->right);
		}
	}

	void inOrder(node cur) {
		if (cur != nullptr) {
			inOrder(cur->left);
			cout<<cur->data<<" ";
			inOrder(cur->right);
		}
	}

	void postOrder(node cur) {
		if (cur != nullptr) {
			postOrder(cur->left);
			postOrder(cur->right);
			cout<<cur->data<<" ";
		}
	}

	node searchTree(node cur, int key) {
		if (cur == nullptr || key == cur->data) {
			return cur;
		}

		if (key < cur->data) {
			return searchTree(cur->left, key);
		}
		return searchTree(cur->right, key);
	}

	bool deleteNode(node cur, int key) {
		node x = nullptr;
		node t, s;
		while (cur != nullptr){
			if (cur->data == key) {
				x = cur;
			}

			if (cur->data <= key) {
				cur = cur->right;
			} else {
				cur = cur->left;
			}
		}

		if (x == nullptr) {
			return 0;
		}
		split(x, s, t); // split the tree
		if (s->left){ // remove x
			s->left->parent = nullptr;
		}
		root = join(s->left, t);
		s = nullptr;
		return 1;
	}

	void print(node root, string indent, bool last) {
		// print the tree structure on the screen
	   	if (root != nullptr) {
		   cout<<indent;
		   if (last) {
		      cout<<"----";
		      indent += "     ";
		   } else {
		      cout<<"|----";
		      indent += "|    ";
		   }

		   cout<<root->data<<endl;

		   print(root->left, indent, false);
		   print(root->right, indent, true);
		}
	}

	// rotate left at node x
	void leftRotate(node x) {
		node y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	// rotate right at node x
	void rightRotate(node x) {
		node y = x->left;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	// splaying
	void splay(node x) {
		while (x->parent) {
			if (!x->parent->parent) {
				if (x == x->parent->left) {
					// zig rotation
					rightRotate(x->parent);
				} else {
					// zag rotation
					leftRotate(x->parent);
				}
			} else if (x == x->parent->left && x->parent == x->parent->parent->left) {
				// zig-zig rotation
				rightRotate(x->parent->parent);
				rightRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->right) {
				// zag-zag rotation
				leftRotate(x->parent->parent);
				leftRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->left) {
				// zig-zag rotation
				leftRotate(x->parent);
				rightRotate(x->parent);
			} else {
				// zag-zig rotation
				rightRotate(x->parent);
				leftRotate(x->parent);
			}
		}
	}

	// joins two trees s and t
	node join(node s, node t){
		if (!s) {
			return t;
		}

		if (!t) {
			return s;
		}
		node x = maximum(s);
		splay(x);
		x->right = t;
		t->parent = x;
		return x;
	}

	// splits the tree into s and t
	void split(node &x, node &s, node &t) {
		splay(x);
		if (x->right) {
			t = x->right;
			t->parent = nullptr;
		} else {
			t = nullptr;
		}
		s = x;
		s->right = nullptr;
		x = nullptr;
	}

public:
	SplayTree() {root = nullptr;}

	// Node->Left Subtree->Right Subtree
	void preorder() {preOrder(this->root);}
	// Left Subtree -> Node -> Right Subtree
	void inorder() {inOrder(this->root);}
	// Left Subtree -> Right Subtree -> Node
	void postorder() {postOrder(this->root);}

	// search the tree for the key k
	// and return the corresponding node
	node searchTree(int k) {
		node x = searchTree(this->root, k);
		if (x) {
			splay(x);
		}
		return x;
	}

	// find the node with the minimum key
	node minimum(node node) {
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	// find the node with the maximum key
	node maximum(node node) {
		while (node->right != nullptr) {
			node = node->right;
		}
		return node;
	}
	// insert the key to the tree in its appropriate position
	void insert(int key) {
		// normal BST insert
		node cur = new Node;
		cur->parent = nullptr;
		cur->left = nullptr;
		cur->right = nullptr;
		cur->data = key;
		node y = nullptr;
		node x = this->root;

		while (x != nullptr) {
			y = x;
			if (cur->data < x->data) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		// y is parent of x
		cur->parent = y;
		if (y == nullptr) {
			root = cur;
		} else if (cur->data < y->data) {
			y->left = cur;
		} else {
			y->right = cur;
		}

		// splay the node
		splay(cur);
	}

	node getRoot(){
		return this->root;
	}

	// delete the node from the tree
	void deleteNode(int data) {
		deleteNode(this->root, data);
	}

	// print the tree structure on the screen
	void prettyPrint() {
		print(this->root, "", true);
	}

};

int32_t main() {
    SplayTree bst;
	bst.insert(33);
	bst.insert(44);
	bst.insert(67);
	bst.insert(5);
	bst.insert(89);
	bst.insert(41);
	bst.insert(98);
	bst.insert(1);
	bst.prettyPrint();
	bst.searchTree(33);
	bst.searchTree(44);
	bst.prettyPrint();
	bst.deleteNode(89);
	bst.deleteNode(67);
	bst.deleteNode(41);
	bst.deleteNode(5);
	bst.prettyPrint();
	bst.deleteNode(98);
	bst.deleteNode(1);
	bst.deleteNode(44);
	bst.deleteNode(33);
	bst.prettyPrint();
}
