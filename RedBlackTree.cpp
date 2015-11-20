#include "RedBlackTree.h"
#include <string>
#include <iostream>
#include <iomanip>// - for setw>
#include <fstream>
#include <cstdlib>
#include <stdexcept>

using namespace std;
/*
This is RedBlackTree.cpp which is separated from 
the header file (RedBlackTree.h)

It contains:

default constructor
copy constructor
assignment operator
destructor 
load
insert
remove
search
deleteAll()
dump

size
hight
b_height

and other helper functions
*/


//#define MAX_ARRAY_SIZE 1000

namespace RBTree{

	/*
	//RedBlackTree's default constructor - create an empty tree
	root set to NULL
	PRE:
	PARAM:
	POST:
	*/
	template <class T>
	RedBlackTree<T>::RedBlackTree(): root(NULL){
	}

	/*
	Copy constructor, creates a deep copy of the parameter by calling copy_helper function
	to make the deep copy of root's parameter easier
	PRE:
	PARAM:old- the pointer of old tree
	POST: 
	*/
	template<class T>
	RedBlackTree<T>::RedBlackTree(const RedBlackTree& old) {
		if (old.root == NULL) {
			return;
		}
		root = new Node<T>(old.root->data);
		root->isBlack = old.root->isBlack;
		root->color = old.root->color;
		copy_helper(root, old.root);
	}

	/*
	overloads the assignment operator for RedBlackTree, 
	(deep) copies the parameter into the calling object 
	and returns a reference to the calling object, 
	if the calling object is the same as the parameter 
	the operator do not copy it; 
	also de-allocates any dynamic memory associated with 
	the original contents of the calling object
	PRE:
	PARAM:old- the pointer of old tree
	POST: return the pointer to the object 
	*/
	template<class T>
	RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree& old) {

		//	deleteAll();
		if (this == &old) {
			return *this;
		}

		deleteAll();
		root = new Node<T>(old.root->data);
		copy_helper(root, old.root);
		return *this;
	}

	/*
	//RedBlackTree's destructor - call the deleteAll() function to 
	deletes dynamic memory allocated by the tree. 
	And deleteAll() function call the delete_all(Node<T> node) to do 
	the jobs as Assignment required
	PRE:
	PARAM:
	POST:
	*/
	template <class T>
	RedBlackTree<T>::~RedBlackTree(){
		deleteAll();
	}

	/*
	Insertion - insert the value which is not contain in the tree,
	which means - no repeated values. 
	PRE:
	PARAM: value - the value to be insert
	POST: return true iff the value is inserted
	*/
	template<class T>
	bool RedBlackTree<T>::insert(T value) {

		Node<T>* t = new Node<T>;
		Node<T>* parent;
		t->data = value;
		t->left = NULL;
		t->right = NULL;
		parent = NULL;
		Node<T>* duplicate;

		bool repeat = true;


		if(duplicate=searchNode(root, value)){
			return false;
		}

		if (isEmpty()) {
			root = t;
			t->color = 'B';
			return true;
		} else {
			Node<T>* curr = root;

			while (curr) {
				parent = curr;
				if (t->data > curr->data) {
					curr = curr->right;
				} else {
					curr = curr->left;
				}
			}
			t->parent = parent;

			if (t->data < parent->data) {
				parent->left = t;
			} else {
				parent->right = t;
			}

		}
		t->color = 'R';
		insertfixup(t);
		return true;

	}

	/*
	Remove is a bool function to call deletNode pointer to 
	delete the value in is ask to be removed 
	PRE:
	PARAM: value - to be delete in the tree
	POST: - ture iff node the value is ask to be deleted
	- return false iff the value is ask to be deleted is 
	not in the tree
	*/
	template<class T>
	bool RedBlackTree<T>::remove(T value){

		Node<T>* node = searchNode(root, value);
		Node<T>* y=NULL;

		if(node!=NULL){
			y=deleteNode(node);
			return true;
		}else{
			return false;
		}
	}

	/*
	Load array of number into the Red black tree, by using Red Black Tree insertion
	PRE:
	PARAM: otherArr - array
	size - total number of items to be insert
	POST:
	*/
	template<class T>
	void RedBlackTree<T>::load(T* otherArr, int size) {

		deleteAll(); //deletes the contents of the tree;

		for (int i = 0; i < size; i++) {
			insert(otherArr[i]);
		}
	}

	/*
	Call the sizeRecursive function to count the size of the tree
	PRE:
	PARAM:
	POST: return the result(total number of red and black nodes)
	*/
	template<class T>
	int RedBlackTree<T>::size() const {
		return sizeRecursive(root);
	}

	/*
	Recursive function post-order tranversal of the tree to 
	PRE:
	PARAM: node - new node 
	POST:return the number of red and black nodes(values) in the tree
	*/
	template<class T>
	int sizeRecursive(Node<T>* node) {
		if (node == NULL) {
			return 0;
		}
		int leftCount = sizeRecursive(node->left);
		int rightCount = sizeRecursive(node->right);
		return leftCount + rightCount + 1;
	}

	/*
	dump the contents of the array are in ascending order
	by calling helper function dumpp
	PRE:
	PARAM: n - the number of items in the returned array
	POST:returns a pointer to an array in dynamic memory that contains all
	the values in the tree
	*/
	template<class T>
	T* RedBlackTree<T>::dump(int& n) const{

		T* result = new T[n];

		if(root!=NULL){
			cout<<endl;
			dump_help(root, n);
		}
		return result;
	}

	/*
	Call the highRecursive function to count the size of the tree
	PRE:
	PARAM:
	POST: return the hight of the tree
	*/
	template<class T>
	int RedBlackTree<T>::height() const {
		return heightRecursive(root);
	}

	/*
	Compare the both size of tree, and the largest one + 1 is 
	tree's height
	PRE:
	PARAM: node - new node 
	POST: return the largest one +1 is the hight of the tree
	*/
	template<class T>
	int heightRecursive(Node<T>* node) {
		if (node == NULL) {
			return 0;
		}
		int leftHeight = heightRecursive(node->left);
		int rightRight = heightRecursive(node->right);
		if (leftHeight > rightRight) {
			return leftHeight + 1;
		} else {
			return rightRight + 1;
		}
	}

	/*
	Call b_height_Recursive to find out the black hight of the tree
	PRE:
	PARAM: 
	POST:
	*/
	template<class T>
	int RedBlackTree<T>::b_height() const {
		return b_height_Recursive(root);
	}

	/*
	IF the root is Black, the larger black heigh number should +1 
	PRE:
	PARAM: node - new node 
	POST:return the reslut of black height of the tree
	*/
	template<class T>
	int b_height_Recursive(Node<T>* node) {
		if (node == NULL) {
			return 0;
		}
		int myHeight;
		if (node->color == 'B') {
			myHeight = 1;
		} else {
			myHeight = 0;
		}
		int leftHeight = b_height_Recursive(node->left);
		int rightRight = b_height_Recursive(node->right);
		int bh;
		if (leftHeight > rightRight) {
			bh = leftHeight + myHeight;
		} else {
			bh = rightRight + myHeight;
		}
		return bh;
	}

	/*
	Search a value is asking which if in the tree return true 
	- by calling searchNode funtion for the help
	PRE:
	PARAM: value - the value need to be found in the tree
	POST: return the the value iff it is found 
	*/
	template<class T>
	bool RedBlackTree<T>::search(T value) {
		return searchNode(root, value) != NULL;
	}

	/*
	Search function 
	returns a pointer to an array in dynamic memory 
	call the searchfixup to do the search job
	PRE:
	PARAM: valueMin - minimum value
	valueMax - maximum value 
	int - the number of items in the return array
	POST:return the result values in the array
	*/
	template<class T>
	T* RedBlackTree<T>::search(T valueMin, T valueMax, int &n) {

		int sz=100;
		T* result = new T[sz];
		if (root != NULL){
			searchfixup(root, valueMin, valueMax, result, n);
			return result;
		}
		//	delete [] result;
	}

	/*
	Void function that help copy constructor and operator overload to do the deep copy
	from one pointer children to the other pointer's children
	PRE:
	PARAM: copy children node from parameter "from" to parameter "to"
	POST:
	*/
	template<class T>
	void copy_helper(Node<T>* to, Node<T>* from) {
		if (from->left != NULL) {
			Node<T>* left = from->left;
			to->left = new Node<T>(left->data);
			to->left->isBlack = left->isBlack;
			to->left->parent = to;
			to->left->color = left->color;
			copy_helper(to->left, left);
		}
		if (from->right != NULL) {
			Node<T>* right = from->right;
			to->right = new Node<T>(right->data);
			to->right->isBlack = right->isBlack;
			to->right->parent = to;
			to->right->color = right->color;
			copy_helper(to->right, right);
		}
	}

	/*
	Void function help the trees's nodes to left roation
	in order to make the three balance 
	PRE:
	PARAM: node - is the node need to be left rotate
	POST:
	*/
	template <class T>
	void RedBlackTree<T>::LeftRotate(Node<T>* x) {
		Node<T>* Right = x->right;
		x->right = Right->left;

		if (Right->left != NULL){
			Right->left->parent = x;
		}
		if (Right != NULL){
			Right->parent = x->parent;
		}
		if (x->parent != NULL) {
			if (x == x->parent->left){
				x->parent->left = Right;
			}
			else{
				x->parent->right = Right;
			}

		}else{
			root = Right;
		}

		Right->left = x;
		if (x != NULL){
			x->parent = Right;
		}

	}

	/*
	Void function help the trees's nodes to left roation
	in order to make the three balance 
	PRE:
	PARAM: node - is the node need to be right rotate
	POST:
	*/
	template <class T>
	void RedBlackTree<T>::RightRotate(Node<T>* x) {

		Node<T>* Left = x->left;
		x->left = Left->right;

		if (Left->right != NULL) {
			Left->right->parent = x;
		}
		if (Left != NULL){
			Left->parent = x->parent;
		}
		if (x->parent != NULL) {
			if (x == x->parent->right){
				x->parent->right = Left;
			}else{
				x->parent->left = Left;
			}
		} else{
			root = Left;
		}

		Left->right = x;
		if (x != NULL){
			x->parent = Left;
		}

	}

	/*
	Case 1: New node and its uncle are both red
	Case 2: New node's parent is red and uncle is black & node is a left child
	Case 3: New node's parent is red and uncle is black & node is a right child
	Case 2 & 3 are opposite when node is in the right sub-tree
	PRE:
	PARAM: node - new node
	POST:
	*/
	template<class T>
	void RedBlackTree<T>::insertfixup(Node<T> *node) {
		//	cout << "fix up" << endl;
		if (node == root) {
			node->color = 'B';
			return;
		}
		if (node->parent->color == 'B') {
			return;
		}

		Node<T>* uncle;
		if (node->parent == node->parent->parent->left) {
			uncle = node->parent->parent->right;
			//	cout << "uncle = " << uncle << " " << endl;
			if (uncle != NULL && uncle->color == 'R') {
				// case 1
				node->parent->parent->color = 'R';
				node->parent->color = 'B';
				uncle->color = 'B';
				insertfixup(node->parent->parent);
			} else if (node == node->parent->right) {
				// case 2
				LeftRotate(node->parent);
				insertfixup(node->left);
			} else {
				// case 3
				node->parent->parent->color = 'R';
				node->parent->color = 'B';
				RightRotate(node->parent->parent);
			}
		} else {
			uncle = node->parent->parent->left;
			if (uncle != NULL && uncle->color == 'R') {
				// case 1
				node->parent->parent->color = 'R';
				node->parent->color = 'B';
				uncle->color = 'B';
				insertfixup(node->parent->parent);
			} else if (node == node->parent->left) {
				// case 2
				RightRotate(node->parent);
				insertfixup(node->right);
			} else {
				// case 3
				node->parent->parent->color = 'R';
				node->parent->color = 'B';
				LeftRotate(node->parent->parent);
			}
		}
	}

	/*
	Refer to lecture note for the algorithm 
	This is helper function as Note<T> pointer to delete the value which 
	is call from "remove" function
	PRE:
	PARAM: node - new node 
	POST:delete the node which is call to be delete
	*/
	template <class T>
	Node<T>* RedBlackTree<T>::deleteNode(Node<T> *node){

		Node<T>* y=NULL;
		Node<T>* x=NULL;
		if(node->left==NULL||node->right==NULL){
			y=node;
		}else{
			y=TreeSuccessor(node);	
		}

		if(y->left!=NULL){
			x=y->left;
		}else{
			x=y->right;
		}
		if(x!=NULL){
			x->parent=y->parent;
		}

		Node<T>* xParent = y->parent;

		bool yIsLeft=false;
		if(y->parent==NULL){
			root=x;
		}else if(y==y->parent->left){
			y->parent->left=x;
			yIsLeft=true;
		}else{
			y->parent->right=x;
			yIsLeft=false;
		}

		if(y!=node){
			node->data=y->data;
		}

		// disabled the deletefixup to run the test file
		//if(y->color=='B'){
		//	deletefixup(x, xParent, yIsLeft);//contain bugs
		//	
		//}

		return y;
	}

	/* need more debugging
	When deleting a node, if the following cases are meet, need to fix the tree
	for each cases in order to fit the Red Black Tree's critea
	//Case 1: x¡¯s sibling is red
	//Case 2: x¡¯s sibling w is black, and both w¡¯s children are black.
	//Case 3: x's sibling w is black, w's left child is red, and w's right child is black
	//Case 4: x's sibling w is black, and w's right child is red
	PRE:
	PARAM: 
	node - new node 
	nodeParent - the node(which is ask to be deleted)'s parent
	nodeIsLeft - 
	POST:
	*/
	template<class T>
	void RedBlackTree<T>::deletefixup(Node<T>* node,Node<T>* nodeParent,bool nodeIsLeft){

		if (node == root) {
			node->color = 'B';
			return;
		}
		if (nodeParent->color == 'B') {
			return;
		}

		Node<T>* w=NULL;

		//Case 1: x¡¯s sibling is red
		if(nodeIsLeft){
			w=nodeParent->right;
			if(node->color=='R'){//doing
				//w->isBlack=true;
				w->color='B';
				nodeParent->color='R';
				LeftRotate(nodeParent);
				w=nodeParent->right;
				cout<<"Bug3"<<endl;
			}

			//Case 2: x¡¯s sibling w is black, and both w¡¯s children are black.
			w=nodeParent->right;
			if(w->left->color=='B' && w->right->color=='B'){

				w->color='R';
				node=nodeParent;
				nodeParent=node->parent;
				nodeIsLeft=(node==nodeParent->left);

			}else {//Case 3: x's sibling w is black, w's left child is red, and w's right child is black
				//
				if(w->right->color=='B'){
					w->left->color='B';
					w->color='R';
					RightRotate(w);
					w=nodeParent->right;
					cout<<"Bug5"<<endl;
				}
				//Case 4: x's sibling w is black, and w's right child is red
				w->color=nodeParent->color;
				nodeParent->color = 'B';
				w->right->color='B';
				LeftRotate(nodeParent);
				node=root;
				nodeParent=NULL;
			}
		}else{
			//deletefixupRight(w ,node,nodeParent,nodeIsLeft);
			w=nodeParent->left;
			if(w->color=='R'){//doing
				//w->isBlack=true;
				w->color='B';
				nodeParent->color='R';
				RightRotate(nodeParent);
				w=nodeParent->left;
			}
			//	if(w->left->color=='B' && w->right->color=='B'){
			if(w->left->color=='B' && w->right->color=='B'){

			//	if(w->right->color=='B'){
					w->color='R';
					node=nodeParent;
					nodeParent=node->parent;
					nodeIsLeft=(node==nodeParent->left);
			//	}
			}else{
				if(w->left->color=='B'){
					w->right->color='B';
					w->color='R';
					LeftRotate(w);
					w=nodeParent->left;
				}
				w->color=nodeParent->color;
				nodeParent->color = 'B';
				w->left->color='B';
				//if(w->left!=NULL){//check
				//	w->right->isBlack=true;
				//}
				RightRotate(nodeParent);
				node=root;
				nodeParent=NULL;
			}
		}

		node->color='B';
	}

	/*
	Call the function delete_all() to deletes dynamic memory allocated by the tree 
	PRE:
	PARAM:
	POST:
	*/
	template <class T>
	void RedBlackTree<T>::deleteAll() {
		if(root!=NULL){
			delete_all(root);
		}
		root=NULL;
	}

	/*
	in-order traversal
	search and print out values in between two parameter "valueMin" and "valueMax"
	PRE:
	PARAM: node - new node
	valueMin - the very left in ascending order but not in clue the number
	valueMax - the very right in ascending order but excluding the maxium value
	outArray - to store the data value in
	n - the number of items in the between parameter valueMin and valueMax
	POST:
	*/
	template<class T>
	void searchfixup(Node<T> *node, T valueMin, T valueMax, T* outArray, int& n) {
		if (node == NULL) {	
			return;
		} else if (node->data >= valueMax) {
			if (node->left) {
				searchfixup(node->left, valueMin,  valueMax,outArray, n);	
			}
		} else if (node->data <= valueMin) {
			if (node->right) {	
				searchfixup(node->right, valueMin, valueMax,outArray, n);
			}
		} else {

			searchfixup(node->left, valueMin, node->data,outArray, n);
			//	outArray[n]=node->data;
			cout<<setw(3)<<node->data;
			n--;
			searchfixup(node->right, node->data, valueMax, outArray, n);
		}
	}

	/*
	dump_help is helper function to print out the values in the 
	tree in order traversal
	PRE:
	PARAM: 
	node - new node 
	n - the number of items in the tree
	POST:
	*/
	template<class T>
	void RedBlackTree<T>::dump_help(Node<T> *node,int& n) const{

		if(node==NULL){return;}

		if(node->left!=NULL){dump_help(node->left,n);}
		cout<<setw(3)<<node->data;
		n--;
		if(node->right!=NULL){dump_help(node->right,n);}
	}



	/*
	Empty the tree, and deallocates dynamic memory which is allocated by the tree
	Destructor and deletAll() call this helper function to do the job
	PRE:
	PARAM: node - new node 
	POST:
	*/
	template<class T>
	void RedBlackTree<T>::delete_all(Node<T>* node){

		if(node!=0){
			delete_all(node->left);
			delete_all(node->right);
			delete node;
		}
		node =NULL;
	}


	////given////
	// Checks that the rb tree is valid with respect to its red property
	// PRE:
	// PARAM:
	// POST: Returns true iff there are no red nodes with red children
	template <class T>
	bool RedBlackTree<T>::redCheck() const
	{
		bool result = true;
		redProperty(root, result);
		return result;
	}

	// Performs a post-order traversal checking the rb red property
	// PRE:
	// PARAM: nd - the node to be tested
	//        ok - reference parameter that records result
	// POST: Returns true iff there are no red nodes with red children
	template <class T>
	void RedBlackTree<T>::redProperty(Node<T>* nd, bool & ok) const
	{
		if(nd != NULL){
			redProperty(nd->left, ok);
			redProperty(nd->right, ok);
			if(nd != root && (!nd->isBlack && !nd->parent->isBlack)){
				ok = false;
			}
		}
	}


	/*
	TreeSuccessor is the successor of the node,
	which is always larger than the node's value
	PRE:
	PARAM: node - new node 
	POST:return the node's successor in the tree to replace 
	the node to be deleted
	*/
	template <class T>
	Node<T>* RedBlackTree<T>::TreeSuccessor(Node<T>* node) {

		if(node==NULL){
			return NULL;
		}
		Node<T>* result= node->right;
		while(result!=NULL){
			if(result->left!=NULL){
				result=result->right;
			}
			else{break;}
		}

		if(result==NULL){
			Node<T>* index = node->parent;
			result =node;
			while(index!=NULL && result==index->right){
				result=index;
				index=index->parent;
			}
			result=index;
		}
		return result;
	}

	/*
	Search the value in the tree, turn if the value is found
	PRE:
	PARAM: node - new node 
	found - the value is looking for
	POST:return the value if it's found
	else return NULL
	*/
	template<class T>
	Node<T>* searchNode(Node<T> *node, T found) {

		if (node == NULL) {
			return NULL;
		} else if (node->data == found) {
			return node;
		} else if (found > node->data) {
			return searchNode(node->right, found);
		} else {
			return searchNode(node->left, found);
		}
	}

	/*
	Check if the root is empty
	PRE:
	PARAM:
	POST:return NULL if the tree is empty
	*/
	template<class T>
	bool RedBlackTree<T>::isEmpty() const {
		return root == NULL;
	}

}




