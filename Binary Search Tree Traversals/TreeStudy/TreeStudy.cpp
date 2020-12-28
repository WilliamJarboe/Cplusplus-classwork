//William Jarboe
//Richard Simpson's class
//Binary Search Tree Program
//DSAA 3013 2019
//This program shows advanced practice with binary search trees.
#include <iostream>
#include <vector>
#include <initializer_list>
#include "BST.h"
using namespace std;

BST MakeRandTree(int n, int limit) {
	BST T;
	for (int i = 0; i < n; i++)
	{
		T.Insert(i);
	}
	return T;
}

BST MakeFlatTree(int n) {
	BST T;
	for (int i = 0; i < n; i++)
	{
		T.Insert(i);
	}
	return T;
}

int main()
{
	
	BST T;
	T = MakeFlatTree(1000);
	int a = 0;
	int val;
	cin >> a;
		for (int i = 0; i < a; i++)
	{
		cin >> val;
		T.Insert(val);
		cin >> val;
		T.Remove(val);
	}

	//print it out
	T.InorderPrint(cout);
	//1 line space
	cout << "\n";

	//part 2, rank() function test
	cin >> a;
	for(int i = 0; i < a; i++)
	{
		cin >> val;
		cout << T.rank(val) << "\n";
	}
	//1 line space
	cout << "\n";

	//part 3, range() function test
	cin >> a;
	
	for (int i = 0; i < a; i++) {
		int t = 0;
		cin >> t;
		cin >> val;
		cout << T.range(t, val) << "\n";
	}
	//uncomment for checking results.
	system("pause");
}