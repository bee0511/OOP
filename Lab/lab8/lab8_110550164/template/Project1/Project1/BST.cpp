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

	Node* current = root;               // �Ncurent���Vroot�@��traversal�_�I

	while (current != NULL && key != current->getValue()) {  // ��ر��p���X�j��G
													  // 1.�S��� 2.�����
		if (key < current->getValue()) {
			current = current->getLchild();   // �V����
		}
		else {
			current = current->getRchild();  // �V�k��
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

	// �Q�Ψ��pointer: successor�Pcurrent��traversal 

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
	// �Q�Ψ��pointer: predecessor�Pcurrent��traversal
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
	Node* delete_node = Search(key);    // ���T�{BST���O�_���㦳KEY��node
	if (delete_node == NULL) {
		std::cout << "data not found.\n";
		return;
	}

	Node* y = 0;      // �u���n�Q�R��������O���骺node
	Node* x = 0;      // �n�Q�R����node��"child"
	if (delete_node->getLchild() == NULL || delete_node->getRchild() == NULL) {
		y = delete_node;
	}
	else {
		y = InorderSuccessor(delete_node);        // �Ny�]��delete_node��Successor
	}                                      // �g�L�o��if-else, y�վ㦨�ܦh�u���@��child
										   // �����վ㦨case1��case2�ӳB�z
	if (y->getLchild() != NULL) {
		x = y->getLchild();                  // �Nx�]��y��child, �i��O���İO����,
	}                                      // �]���i��ONULL
	else {
		x = y->getRchild();
	}

	if (x != NULL) {                        // �by�Q�R�����e, �o�ӨB�J��x���^BST
		x->setparent(y->getparent());             // ���Y���ϤG(c)��, ���ñ��^�t�P�H���B�J
	}
	// ���ۦA��n�Q����O���骺node��"parent"���V�s��child
	Node* y_parent = y->getparent();
	if (y_parent == NULL) {                // �Y�R�����O�����root, �N��x���s��root 
		this->root = x;
	}
	else if (y == y_parent->getLchild()) {    // �Yy�쥻�O��parent��left child
		y_parent->setLchild(x);           // �K��x�Ҧby��parent��left child, ���Ny
	}
	else {                                   // �Yy�쥻�O��parent��right child
		y_parent->setRchild(x);           // �K��x�Ҧby��parent��right child, ���Ny
	}
	// �w��case3
	if (y != delete_node) {                 // �Yy�Odelete_node������, �̫�n�A�Ny�����
		delete_node->setValue(y->getValue());         // ��^delete_node���O�����m, �ñNy���O�����m����
	}

	delete y;                               // �Ny���O�����m����
	y = 0;
}
