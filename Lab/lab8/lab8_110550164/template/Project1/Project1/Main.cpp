#include <iostream>
#include <fstream>
#include "BST.h"
#include "Node.h"

using namespace std;

int main() {
	/*  Do not modify the content in "int main ()". */

	/*fstream file;
	file.open("input2.txt");

	if (!file.is_open()) {
		cout << "Fail to open file" << endl;
		return 0;
	}

	int TestCase = 0;
	file >> TestCase;

	while (TestCase) {
		BST bst;

		int NumberOfNode;
		file >> NumberOfNode;

		for (int i = 0; i < NumberOfNode; i++) {
			int NodeValue;
			file >> NodeValue;
			bst.insert(new Node(NodeValue));
		}

		//Inorder traversal
		cout << "Inorder_traversal: ";
		bst.Print_InOrder_traversal(bst.getRoot());
		cout << endl;

		cout << "Preorder_traversal: ";
		bst.Print_PreOrder_traversal(bst.getRoot());
		cout << endl;

		cout << "Postorder_traversal: ";
		bst.Print_PostOrder_traversal(bst.getRoot());
		cout << endl;

		//Level order traversal
		cout << "Level_traversal: ";
		bst.Print_LevelOrder_traversal(bst.getRoot());
		cout << endl << endl;

		TestCase--;
	}*/

	int a[] = { 1,23,3,5,2,61,7 };
	BST bst_2(a, sizeof(a) / sizeof(int)), bst;
	bst.insert(new Node(513));
	bst.insert(new Node(8));
	bst.insert(new Node(888));
	bst.insert(new Node(2));
	bst.insert(new Node(79));
	bst.insert(new Node(666));
	bst.insert(new Node(999));
	bst.insert(new Node(69));
	bst.insert(new Node(520));
	bst.insert(new Node(881));
	bst.insert(new Node(995));
	bst.insert(new Node(1991));

	cout << "height: " << bst.ComputeHeight(bst.getRoot());
	cout << "Inorder_traversal: ";
	bst.Print_InOrder_traversal(bst.getRoot());
	cout << endl;

	cout << "Preorder_traversal: ";
	bst.Print_PreOrder_traversal(bst.getRoot());
	cout << endl;

	cout << "Postorder_traversal: ";
	bst.Print_PostOrder_traversal(bst.getRoot());
	cout << endl;

	//Level order traversal
	cout << "Level_traversal: ";
	bst.Print_LevelOrder_traversal(bst.getRoot());
	cout << endl << endl;
	//a = bst.Search(5);
	//cout << a->getValue() << endl;
	//bst.Delete(666);

	cout << "Inorder_traversal: ";
	bst.Print_InOrder_traversal(bst.getRoot());
	cout << endl;

	cout << "Inorder_Reverse: ";
	bst.Print_Inorder_Reverse(bst.getRoot());
	cout << endl;

	cout << "Inorder_by_parent: ";
	bst.Print_Inorder_by_parent(bst.getRoot());
	cout << endl;

	//bst.kthSmallest(bst.getRoot(),8);
	bst.lowestCommonAncestor(bst.getRoot(), bst.Search(520), bst.Search(881));
	int sum = bst.rangeSumBST(bst.getRoot(),1,100);
	cout << sum << endl;
	cout << bst.isValidBST(bst.getRoot()) << endl;
	system("pause");
	return 0;

}