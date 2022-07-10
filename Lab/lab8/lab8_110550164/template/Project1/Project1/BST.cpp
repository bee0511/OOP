#include "BST.h"
#include<iostream>
#include<queue>
using namespace std;

BST::BST(int* arr, int size) {
	root = new Node(arr[0]);
	for (int i = 1; i < size; i++) {
		insert(new Node(arr[i]));
	}
}

void BST::insert(Node* insertNode) {
	//TODO: insert a node to BST
	if (!root) {
		root = insertNode;
		return;
	}
	Node* current = root;
	while (true) {
		//cout << "getvalue" << current->getValue() << endl;
		if (insertNode->getValue() < current->getValue()) {
			if (current->getLchild() != 0)
				current = current->getLchild();
			else {
				current->setLchild(insertNode);
				insertNode->setparent(current);
				return;
			}
		}
		else if (insertNode->getValue() > current->getValue()) {
			if(current->getRchild() != 0)
				current = current->getRchild();
			else {
				current->setRchild(insertNode);
				insertNode->setparent(current);
				return;
			}
		}
	}
	/*if (insertNode->getValue() < current->getValue()) {
		if (current->getLchild() != 0) {
			insert(current->getLchild());
			cout << "a";
		}
		else {
			current->setLchild(insertNode);
			return;
		}
		return;
	}
	if (insertNode->getValue() > current->getValue()) {
		if (current->getRchild() != 0) {
			insert(current->getRchild());
		}
		else {
			current->setRchild(insertNode);
			return;
		}
		return;
	}*/
}

void BST::Print_InOrder_traversal(Node* root)
{
	//TODO: Inorder traversal
	if (root != 0) {
		Print_InOrder_traversal(root->getLchild());
		cout << root->getValue() << " ";
		//cout << root->getparent() << " " << endl;
		Print_InOrder_traversal(root->getRchild());
	}
	//cout << root->getValue() << " ";
}

void BST::inorder_computeheight(Node* root, std::vector<int>& v) {
	if (root != 0) {
		inorder_computeheight(root->getLchild(), v);
		v.push_back(root->getValue());
		inorder_computeheight(root->getRchild(), v);
	}
}

int BST::ComputeHeight(Node* node) {
	// Compute the height of the binary search tree.
	// Notice that the root level is 1
	int height = 0;
	std::vector<int> v;
	inorder_computeheight(node, v);
	int size = v.size();
	while (size) {
		size /= 2;
		height++;
	}
	return height;
}
void BST::Print_LevelOrder_traversal(Node* root)
{
	//TODO: Level order traversal
	queue<Node*> q;
	q.push(root);
	while (!q.empty())
	{
		Node* p = q.front(); 
		q.pop();
		cout << p->getValue() << " ";
		if (p->getLchild())  q.push(p->getLchild());
		if (p->getRchild()) q.push(p->getRchild());
	}
}


Node* BST::getRoot() {
	//TODO: return root of BST
	return root;
}

void BST::Print_PreOrder_traversal(Node* root){
	if (root != 0) {
		cout << root->getValue() << " ";
		Print_PreOrder_traversal(root->getLchild());
		Print_PreOrder_traversal(root->getRchild());
	}
}

void BST::Print_PostOrder_traversal(Node* root) {
	if (root != 0) {
		Print_PostOrder_traversal(root->getLchild());
		Print_PostOrder_traversal(root->getRchild());
		cout << root->getValue() << " ";
	}
}

Node* BST::Search(int key) {

	Node* current = root;               // 將curent指向root作為traversal起點

	while (current != NULL && key != current->getValue()) {  // 兩種情況跳出迴圈：
													  // 1.沒找到 2.有找到
		if (key < current->getValue()) {
			current = current->getLchild();   // 向左走
		}
		else {
			current = current->getRchild();  // 向右走
		}
	}
	return current;
}

Node* BST::leftmost(Node* current) {
	while (current->getLchild() != NULL) {
		current = current->getLchild();
	}
	return current;
}

Node* BST::rightmost(Node* current) {
	while (current->getRchild() != NULL) {
		current = current->getRchild();
	}
	return current;
}


Node* BST::InorderSuccessor(Node* current) {
	if (current->getRchild() != NULL) {
		return leftmost(current->getRchild());
	}

	// 利用兩個pointer: successor與current做traversal 

	Node* successor = current->getparent();
	while (successor != NULL && current == successor->getRchild()) {
		current = successor;
		successor = successor->getparent();
	}
	return successor;
}

Node* BST::InorderPredecessor(Node* current) {
	if (current->getLchild() != NULL) {
		return rightmost(current->getLchild());
	}
	// 利用兩個pointer: predecessor與current做traversal
	Node* predecessor = current->getparent();

	while (predecessor != NULL && current == predecessor->getLchild()) {
		current = predecessor;
		predecessor = predecessor->getparent();
	}

	return predecessor;
}

void BST::Print_Inorder_by_parent(Node* root) {
	Node* current = new Node(0);
	current = leftmost(root);

	while (current) {
		std::cout << current->getValue() << " ";
		current = InorderSuccessor(current);
	}
}

void BST::Print_Inorder_Reverse(Node* root) {
	Node* current = new Node(0);
	current = rightmost(root);

	while (current) {
		std::cout << current->getValue() << " ";
		current = InorderPredecessor(current);
	}
}

int BST::kthSmallest(Node* root, int k) {
	std::vector<int> v;
	InOrder_traversal_kthSmallest(root, v);
	if (k > v.size()) {
		cout << "Error: out of bound." << endl;
		return -1;
	}
	cout << k << "th smallest value is " << v[k - 1] << "." << endl;
	return v[k - 1];
}

void BST::InOrder_traversal_kthSmallest(Node* root, std::vector<int> &v) {
	if (root != 0) {
		InOrder_traversal_kthSmallest(root->getLchild(), v);
		v.push_back(root->getValue());
		InOrder_traversal_kthSmallest(root->getRchild(), v);
	}
}

void BST::isValidBST_Inorder(Node* root, vector<int>& v)
{
	if (root->getLchild())
		isValidBST_Inorder(root->getLchild(), v);
	v.push_back(root->getValue());
	if (root->getRchild())
		isValidBST_Inorder(root->getRchild(), v);
}

bool BST::isValidBST(Node* root)
{
	if (root == NULL)
		return true;

	vector<int> v;
	isValidBST_Inorder(root, v);

	for (int i = 1; i < v.size(); i++)
	{
		if (v[i] <= v[i - 1])
			return false;
	}
	return true;
}

void BST::rangeSumBST_helper(Node* root, int low, int high) {
	if (root == NULL)
		return;
	if (root->getValue() >= low && root->getValue() <= high)
		sum += root->getValue();
	if (root->getValue() > low)
		rangeSumBST_helper(root->getLchild(), low, high);
	if (root->getValue() < high)
		rangeSumBST_helper(root->getRchild(), low, high);
}

int BST::rangeSumBST(Node* root, int low, int high) {
	rangeSumBST_helper(root, low, high);
	return sum;
}

Node* BST::lowestCommonAncestor(Node* root, Node* p, Node* q) {
	if (root->getValue() > p->getValue() && root->getValue() > q->getValue())
		return lowestCommonAncestor(root->getLchild(), p, q);

	if (root->getValue() < p->getValue() && root->getValue() < q->getValue())
		return lowestCommonAncestor(root->getRchild(), p, q);
	cout << "Lowest Common Ancestor of " << p->getValue() << " and " << q->getValue() << " is " << root->getValue() << endl;
	return root;
}


void BST::Delete(int key) {
	Node* delete_node = Search(key);    // 先確認BST中是否有具有KEY的node
	if (delete_node == NULL) {
		std::cout << "data not found.\n";
		return;
	}

	Node* y = 0;      // 真正要被刪除並釋放記憶體的node
	Node* x = 0;      // 要被刪除的node的"child"
	if (delete_node->getLchild() == NULL || delete_node->getRchild() == NULL) {
		y = delete_node;
	}
	else {
		y = InorderSuccessor(delete_node);        // 將y設成delete_node的Successor
	}                                      // 經過這組if-else, y調整成至多只有一個child
										   // 全部調整成case1或case2來處理
	if (y->getLchild() != NULL) {
		x = y->getLchild();                  // 將x設成y的child, 可能是有效記憶體,
	}                                      // 也有可能是NULL
	else {
		x = y->getRchild();
	}

	if (x != NULL) {                        // 在y被刪除之前, 這個步驟把x接回BST
		x->setparent(y->getparent());             // 此即為圖二(c)中, 把基紐接回龜仙人的步驟
	}
	// 接著再把要被釋放記憶體的node之"parent"指向新的child
	Node* y_parent = y->getparent();
	if (y_parent == NULL) {                // 若刪除的是原先的root, 就把x當成新的root 
		this->root = x;
	}
	else if (y == y_parent->getLchild()) {    // 若y原本是其parent之left child
		y_parent->setLchild(x);           // 便把x皆在y的parent的left child, 取代y
	}
	else {                                   // 若y原本是其parent之right child
		y_parent->setRchild(x);           // 便把x皆在y的parent的right child, 取代y
	}
	// 針對case3
	if (y != delete_node) {                 // 若y是delete_node的替身, 最後要再將y的資料
		delete_node->setValue(y->getValue());         // 放回delete_node的記憶體位置, 並將y的記憶體位置釋放
	}

	delete y;                               // 將y的記憶體位置釋放
	y = 0;
}
