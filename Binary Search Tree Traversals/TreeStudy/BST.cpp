#include "BST.h"
#include <stack>

//add complexity to each function below.

/*BST default constructor.
**Complexity: 1
**param: none
**return: none
**desc: creates an empty BST.
*/
BST::BST()
{
	root = nullptr;
}

/*BST parameterized constructor.
**Complexity: n
**param: initializer_list<int>
**return: none
**desc: creates a BST with the desired content in the param list.
*/
BST::BST(std::initializer_list<int> lst) {
	for (auto i : lst)
		Insert(i);
}

/*BST destructor.
**Complexity: 1
**param: none
**return: none
**desc: destructs the BST.
*/
BST::~BST()
{
	Clear(root);
}

/*BST copy constructor.
**Complexity: 1
**param: BST
**return: none
**desc: creates a copy of a BST.
*/
BST::BST(const BST& T)
{
	if (T.root == nullptr)
	{
		root = nullptr;
	}
	else
	{
		copyTree(root, T.root);
	}
}

/*BST = operator overload
**Complexity: n
**param: BST
**return: none
**desc: sets one BST to be another.
*/
BST& BST::operator=(const BST& T)
{
	if (this->root != T.root)
	{
		this->Clear(root);
		copyTree(root, T.root);
	}
	return (*this);
}

/*BST default constructor.
**Complexity: 1
**param: none
**return: none
**desc: creates an empty BST.
*/
BST::BST(BST&& r)
{
	root = r.root;
	r.root = nullptr;
}

/*BST = operator overload
**Complexity: n
**param: BST
**return: none
**desc: sets one BST to be another.
*/
BST& BST::operator=(BST&& r) {
	if (this != &r)
	{
		swap(root, r.root);
		return *this;
	}
}

/*public insert method
**Complexity: 1
**param: int
**return: none
**desc: adds a value into the bst.
*/
void BST::Insert(int v)
{
	InsertAux(root, v);
}

/*private insert method
**Complexity: log(n)
**param: node*&, int
**return: none
**desc: adds a value into the bst.
*/
void BST::InsertAux(Node*& r, int v)
{
	if (r == nullptr)
	{	
		r = new Node(v);
		r->left = nullptr;
		r->right = nullptr;
		r->val = v;
		r->size = 0;
	}

	else {
		if (v < r->val)
		{
			r->size++;
			InsertAux(r->left, v);
		}
		else
		{
			r->size++;
			InsertAux(r->right, v);
		}
	}
}

/*private insert method
**Complexity: log(n)
**param: node*&, int
**return: none
**desc: adds a value into the bst.
*/
void BST::InorderPrint(std::ostream& os)
{
	InorderPrintAux(root, os);//start from origin
		os << endl;
}

//print in numerical order everything
void BST::InorderPrintAux(Node* r, ostream& os)
{
	if (r != nullptr)
	{
		InorderPrintAux(r->left, os);//print left subtree
		os << r->val << " ";
		InorderPrintAux(r->right, os);//print right subtree
	}
}

//the copy tree function. i snuck it in.
void BST::copyTree(Node*& r, Node *sr)
{
	if (sr == nullptr)
		r = nullptr;
	else
	{
		r = new Node(sr->val);
		copyTree(r->left, sr->left);
		copyTree(r->right, sr->right);
	}
}

//clears a node
void BST::Clear(Node*& r)
{
	if (r != nullptr)
	{
		Clear(r->left);
		Clear(r->right);
		delete r;
		r = nullptr;
	}
}

//non recursive sum as example
//uses a STL Stack
int BST::SumNR()
{
	stack<Node*> s;
	Node *curr = root;
	int result = 0;
	while (curr != nullptr || s.empty() == false)
	{
		//reach the left most node of the current node
		while (curr!=nullptr)
		{
			s.push(curr);
			curr = curr->left;
		}
		curr = s.top();
		s.pop();
		result += curr->val;
		//we have visited the node and its left subtree. now its right subtree's turn
		curr = curr->right;
	}
	return result;
}

void BST::Flatten() {}


//public sum method
int BST::Sum()
{
	return SumAux(root);
}

//private sum method
int BST::SumAux(Node * r)
{
	if (r == nullptr)
	{
		return 0;
	}
	else
		return r->val + SumAux(r->left) + SumAux(r->right);
}

void BST::Remove(int v)
{
	RemoveAux(root, v);
}

//prog verif line

//another case where & is really important
int BST::RemoveAux(Node*& r, int v)
{
	if (r == nullptr)
	{
		return -1;
	}
	if (v < r->val)
	{
		if (RemoveAux(r->left, v) != -1)
		{
			r->size--;
		}
	}
	else if (v > r->val)
	{
		if (RemoveAux(r->right, v) != -1)
		{
			r->size--;
		}
	}
	//r now points to the thing we need to delete
	else if (r->left != nullptr&&r->right != nullptr)
	{
		
		Node* tptr = r->right;
		Node* bptr = r->right;
		while (tptr->left!=nullptr) 
		{
			bptr = tptr;
			tptr = tptr->left;
		}
		//tptr now points to successor
		//copy succ value to node pointed to by r
		r->val = tptr->val;
		//if we did not go left at all just splice tptr node out
		if (r->right == tptr)
		{
			r->right = tptr->right;
			delete tptr;
		}
		else
		{
			bptr->left = tptr->right;
			delete tptr;
		}
	}
	else
	{
		if (r->left != nullptr)
		{
			Node* t = r;//new r is sent back thru ref param
			r = r->left;
			delete t;
		}
		else
		{
			Node* t = r;
			r = r->right; //new r is sent back...
			delete t;
		}
	}
	return 0;
}

int BST::range(int low, int high)
{
	int hi = 0;
	bool found = false;
	rankAux(root, high, hi, found);
	int lo = 0;
	rankAux(root, low, lo, found);
	return hi - lo;

	//return rangeAux(root, low, high);
}

void BST::rankAux(Node *r, int val, int &ranknum, bool &found)
{
	if (r != nullptr)
	{
		if (val > r->val)
		{
			ranknum++;
		}
		if (val >= r->val)
		{
			rankAux(r->left, val, ranknum, found);
			if (val == r->val)
			{
				found = true;
			}
		}
		rankAux(r->right, val, ranknum, found);
	}
}

//returns the rank of a node. if no node exists, returns -1.
int BST::rank(int val)
{
	int i = 0;
	bool found = false;
	rankAux(root, val, i, found);
	if (found)
	{
		return i;
	}
	return -1;
}