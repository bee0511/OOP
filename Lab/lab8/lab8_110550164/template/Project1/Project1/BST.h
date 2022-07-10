#pragma once
#include "iostream"
#include <vector>
#include "Node.h"
using namespace std;
class BST {
public:
	BST() {
		root = NULL;
		sum = 0;
	}
	BST(int* arr, int size);
	void insert(Node* node);
	void Delete(int key);
	void Print_InOrder_traversal(Node* root);
	void Print_PreOrder_traversal(Node* root);
	void Print_PostOrder_traversal(Node* root);
	void Print_LevelOrder_traversal(Node* root);

	bool isValidBST(Node* root);
	void isValidBST_Inorder(Node* root, vector<int>& v);

	int kthSmallest(Node* root, int k);
	void InOrder_traversal_kthSmallest(Node* root, std::vector<int> &v);

	Node* lowestCommonAncestor(Node* root, Node* p, Node* q);

	int ComputeHeight(Node* node);
	void inorder_computeheight(Node* root, std::vector<int>& v);
	void rangeSumBST_helper(Node* root, int low, int high);
	int rangeSumBST(Node* root, int low, int high);

	Node* Search(int key);
	Node* getRoot();
	Node* leftmost(Node* current);
	Node* rightmost(Node* current);
	Node* InorderSuccessor(Node* current);
	Node* InorderPredecessor(Node* current);
	void Print_Inorder_by_parent(Node* root);
	void Print_Inorder_Reverse(Node* root);
private:
	Node* root;
	int sum;
};
