#include<iostream>
#include<vector>
#define TreeNodePosi TreeNode*
using namespace std;

struct TreeNode {
	int data;
	int height;
	TreeNodePosi left;
	TreeNodePosi right;
	TreeNode() :left(nullptr), right(nullptr) {}
	TreeNode(int num, int h) :data(num), height(h), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
	int num;
	TreeNodePosi T;
	TreeNodePosi SingleLeftRotation(TreeNodePosi Tree) {
		TreeNodePosi New = Tree->left;
		Tree->left = New->right;
		New->right = Tree;
		Tree->height = Max(GetHeight(Tree->left), GetHeight(Tree->right)) + 1;
		New->height = Max(GetHeight(New->left), GetHeight(Tree)) + 1;

		return New;
	}

	TreeNodePosi SingleRightRotation(TreeNodePosi Tree)
	{
		TreeNodePosi New = Tree->right;
		Tree->right = New->left;
		New->left = Tree;
		Tree->height = Max(GetHeight(Tree->left), GetHeight(Tree->right)) + 1;
		New->height = Max(GetHeight(New->right), GetHeight(Tree)) + 1;

		return New;
	}

	TreeNodePosi DoubleLeftRightRotation(TreeNodePosi Tree) {
		Tree->left = SingleRightRotation(Tree->left);
		return SingleLeftRotation(Tree);
	}

	TreeNodePosi DoubleRightLeftRotation(TreeNodePosi Tree) {
		Tree->right = SingleLeftRotation(Tree->right);
		return SingleRightRotation(Tree);
	}

	int GetHeight(TreeNodePosi Tree) {
		if (!Tree)
			return -1;
		else
			return Tree->height;
	}

	int Max(int a, int b) {
		return a > b ? a : b;
	}

	TreeNodePosi Insert(TreeNodePosi Tree, int data) {
		if (!Tree)
			Tree = new TreeNode(data, 0);
		else if (data < Tree->data) {
			Tree->left = Insert(Tree->left, data);
			if (GetHeight(Tree->left) - GetHeight(Tree->right) == 2)   //判断是否需要调整
				if (data < Tree->left->data)
					Tree = SingleLeftRotation(Tree);               //左单旋
				else
					Tree = DoubleLeftRightRotation(Tree);          //左-右双旋
		}
		else if (data > Tree->data) {
			Tree->right = Insert(Tree->right, data);
			if (GetHeight(Tree->left) - GetHeight(Tree->right) == -2)  //判断是否需要调整
				if (data > Tree->right->data)
					Tree = SingleRightRotation(Tree);              //右单旋
				else
					Tree = DoubleRightLeftRotation(Tree);          //右-左双旋
		}

		Tree->height = Max(GetHeight(Tree->left), GetHeight(Tree->right)) + 1;
		return Tree;
	}
public:
	AVLTree(int n) :num(n), T(new TreeNode) {}
	void BuildAVLTree() {
		TreeNodePosi Tree;
		Tree = nullptr;
		int data;

		for (int i = 0; i < num; ++i) {
			cin >> data;
			Tree = Insert(Tree, data);
		}

		T = Tree;
	}

	int GetRootData() { return T->data; }
};

int main()
{
	int n;
	cin >> n;
	AVLTree Tree(n);
	Tree.BuildAVLTree();
	cout << Tree.GetRootData();
	return 0;
}