/*
Gavin Stark
gestark
pa7
*/
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

#define RED 1
#define BLACK 0

using namespace std;

// Helper Functions (Optional) ---------------------------------------------



// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
	if(R != N){
		setValue(R->key, R->val);
		preOrderCopy(R->left, N);
		preOrderCopy(R->left, N);
	}
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
	if(R == nil){
		return R;
	} else if (R->key == k){
		return R;
	} else if (R->key > k) {
		return search(R->left, k);
	} else {
		return search(R->right, k);
	}
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
	if(R->left != nil){
		postOrderDelete(R->left);
	}
	if(R->right != nil){
		postOrderDelete(R->right);
	}
	delete(R);
	R = nil;
	num_pairs--;
	
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
	while(R->left != nil){
		return findMin(R->left);
	}
	return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
	while(R->right != nil){
		return findMin(R->right);
	}
	return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
	Node* R = N;
	if(R->right != nil){
		return findMin(N->right);
	}
	Node* y = R->parent;
	while(y != nil && R == y->right){
		R = y;
		y = y->parent;
	}
	return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
	Node* R = N;
	if(R->left != nil){
		return findMax(N->left);
	}
	Node* y = R->parent;
	while(y != nil && R == y->left){
		R = y;
		y = y->parent;
	}
	return y;
}

// RB_Transplant
// Replaces value
void Dictionary::RB_Transplant(Node* u, Node* v){
	if(u->parent == nil){
		root = v;
	} else if (u == u->parent->left){
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
	if(R != nil){
		inOrderString(s, R->left);
		s += R->key + " : " + std::to_string(R->val) + "\n";
		inOrderString(s, R->right);
	}
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
	if(R != nil){
		s += R->key + "\n";
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

// LeftRotate()
void Dictionary::LeftRotate(Node* N){
	Node* y = N->right;

	N->right = y->left;
	if(y->left != nil){
		y->left->parent = N;
	}

	y->parent = N->parent;
	if(N->parent == nil){
		root = y;
	} else if (N == N->parent->left){
		N->parent->left = y;
	} else {
		N->parent->right = y;
	}

	y->left = N;
	N->parent = y;

}

// RightRotate()
void Dictionary::RightRotate(Node* N){
	Node* y = N->left;

	N->left = y->right;
	if(y->right != nil){
		y->right->parent = N;
	}

	y->parent = N->parent;
	if(N->parent == nil){
		root = y;
	} else if (N == N->parent->right){
		N->parent->right = y;
	} else {
		N->parent->left = y;
	}

	y->right = N;
	N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
	while(N->parent->color == RED){
		if(N->parent == N->parent->parent->left){
			Node* y = N->parent->parent->right;
			if(y->color == RED){
				N->parent->color = BLACK;
				y->color = BLACK;
				N->parent->parent->color = RED;
				N = N->parent->parent;
			} else {
				if (N == N->parent->right){
					N = N->parent;
					LeftRotate(N);
				}
				N->parent->color = BLACK;
				N->parent->parent->color = RED;
				RightRotate(N->parent->parent);
			}
		} else {
			Node* y = N->parent->parent->left;
			if(y->color == RED){
				N->parent->color = BLACK;
				y->color = BLACK;
				N->parent->parent->color = RED;
				N = N->parent->parent;
			} else {
				if(N == N->parent->left){
					N = N->parent;
					RightRotate(N);
				}
				N->parent->color = BLACK;
				N->parent->parent->color = RED;
				LeftRotate(N->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* x){
	while(x != root && x->color == BLACK){
		if(x == x->parent->left){
			Node* w = x->parent->right;
			if(w->color == RED){
				w->color = BLACK;
				x->parent->color = RED;
				LeftRotate(x->parent);
				w = x->parent->right;
			}
			if(w->left->color == BLACK && w->right->color == BLACK){
				w->color = RED;
				x = x->parent;
			} else {
				if(w->right->color == BLACK){
					w->left->color = BLACK;
					w->color = RED;
					RightRotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotate(x->parent);
				x = root;
			}
		} else {
			Node* w = x->parent->left;
			if(w->color == RED){
				w->color = BLACK;
				x->parent->color = RED;
				RightRotate(x->parent);
				w = x->parent->left;
			}
			if(w->right->color == BLACK && w->left->color == BLACK){
				w->color = RED;
				x = x->parent;
			} else {
				if(w->left->color == BLACK){
					w->right->color	= BLACK;
					w->color = RED;
					LeftRotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* z){
	Node* y = z;
	Node* x;
	int y_original_color = y->color;
	if(z->left == nil){
		x = z->right;
		RB_Transplant(z, z->right);
	} else if (z->right == nil){
		x = z->left;
		RB_Transplant(z, z->left);
	} else {
		y = findMin(z->right);
		y_original_color = y->color;
		x = y->right;
		if(y->parent == z){
			x->parent = y;
		} else {
			RB_Transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		RB_Transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if(y_original_color == BLACK){
		RB_DeleteFixUp(x);
	}
}

// Class Constructors & Destructors ----------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v){
    key = k;
	val = v;
	color = 0;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
	Node* N = new Node("Null", -99);
	nil = N;
	root = nil;
	current = nil;
	num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
	Node* N = new Node("Null", -99);
	nil = N;
	root = nil;
	num_pairs = 0;
	preOrderCopy(D.root, D.nil);
	if(D.hasCurrent()){
		current = search(root, D.currentKey());

	} else {
		current = nil;
	}
}
	

// Destructor
Dictionary::~Dictionary(){
	clear();
	delete(nil);
}



// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
	return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
	Node* c = root;
	if(search(c, k) != nil){
		return true;
	} else {
		return false;
	}

}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
	if(search(root, k) == nil){
		throw std::logic_error("Dictionary: getValue(): not found");
	}
	return search(root, k)->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
	if(current != nil){
		return true;
	} else {
		return false;
	}
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
	if(!hasCurrent()){
		throw std::logic_error("Dictionary: currentKey(): not found");
	}
	return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
	if(!hasCurrent()){
		throw std::logic_error("Dictionary: currentVal(): not found");
	}
	return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
	if(root != nil){
		postOrderDelete(root);
	}
	root = nil;
	current = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
	Node* y = nil;
    Node* x = root;
    while (x != nil){
        y = x;
        if (k < x->key){
            x = x->left;
        }else if (k > x->key){ 
            x = x->right;
        } else {
			x->val = v;
			return;
		}
    }
	
    Node* z = new Node(k,v);
    z->parent = y;
	if(y == nil){
		root = z;
	} else if(k < y->key){
		y->left = z;
	} else {
		y->right = z;
	}
    z->left = nil;
    z->right = nil;
	z->color = RED;
	RB_InsertFixUp(z);
    num_pairs++;
}


// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
	if(search(root, k) == nil){
		throw std::logic_error("Dictionary: remove(): not found");
	}
	Node* N = search(root, k);
	if(N == current){
		current = nil;
	}
	/*if(current == N){
		current = nil;
	}
	if(N->left == nil){
		RB_Transplant(N, N->right);
	} else if (N->right == nil){
		RB_Transplant(N, N->left);
	} else {
		Node* y = findMin(N->right);
		if (y->parent != N){
			RB_Transplant(y, y->right);
			y->right = N->right;
			y->right->parent = y;
		}
		RB_Transplant(N, y);
		y->left = N->left;
		y->left->parent = y;
	}*/
	RB_Delete(N);
	num_pairs--;

}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
	if(num_pairs > 0){
		current = root;
		while(current->left != nil){
			current = current->left;
		}
	}
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
	if(num_pairs > 0){
		current = root;
		while(current->right != nil){
			current = current->right;
		}
	}
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
	if(current == NULL){
		throw std::length_error("Dictionary: cursor(): cursor undefined");
	}
	current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
	if(current == NULL){
		throw std::length_error("Dictionary: cursor(): cursor undefined");
	}
	current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
	
	std::string s = "";
	if(num_pairs == 0){
		return s;
	}
	inOrderString(s, root);
	return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
	std::string s = "";
	preOrderString(s, root);
	return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
	if(num_pairs != D.num_pairs){
		return false;
	}
	std::string s = "";
	std::string f = "";
	inOrderString(s, root);
	D.inOrderString(f, D.root);
	if(s == f){
		return true;
	} else {
		return false;
	}
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
	return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
	return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
	if (this != &D){
		Dictionary temp = D;
		std::swap(root, temp.root);
		std::swap(current, temp.current);
		std::swap(nil, temp.nil);
		std::swap(num_pairs, temp.num_pairs);
	}
	return *this;
}