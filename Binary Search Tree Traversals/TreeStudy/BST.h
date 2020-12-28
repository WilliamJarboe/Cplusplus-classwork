#pragma once
#include <ostream>
#include <initializer_list>
using namespace std;
class BST {
private:
	struct Node {
		Node* left;
		Node* right;
		int val;
		int size;
		Node(int v) {
			val = v;
		}
	};
	Node* root;
	int SumAux(Node * r);
	void InorderPrintAux(Node* r, ostream& os);
	void InsertAux(Node*& r, int v);
	int RemoveAux(Node*& r, int v);
	void copyTree(Node*& r, Node *sr);
	int rangeAux(Node *root, int low, int high);
	void rankAux(Node *r, int val, int &ranknum, bool &found);
public:
	int BST::rank(int val);
	int range(int low, int high);
	void Remove(int v);
	int Sum();
	void Flatten();
	int SumNR();
	void Clear(Node*& r);
	//void copyTree(BST::Node*& r, const BST::Node *sr); it is not in the class
	void InorderPrint(ostream& os);
	void Insert(int v);
	BST& operator=(BST&& r);
	BST(BST&& r);
	BST& operator=(const BST& T);
	BST(const BST& T);
	~BST();
	BST(initializer_list<int> lst);
	BST();
	int rank_of(Node *tree, int val);
};