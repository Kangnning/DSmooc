#include<cstdio>
#include<queue>
#define MaxTreeNode 10

struct  TreeNode {
	int data;
	int Left;
	int Right;
};

class Solution {
private:
	TreeNode T[MaxTreeNode];
	int num, root;
public:
	Solution(int n) :num(n) {}
	void BuildTree() {
		int check[MaxTreeNode] = { 0 };
		for (int i = 0; i < num; ++i) {
			getchar();				//去掉\n
			T[i].data = i;
			char left, right;
			scanf("%c %c", &left, &right);
			if (left - '0' < 0)
				T[i].Left = -1;
			else {
				T[i].Left = left - '0';
				check[T[i].Left] = 1;
			}
			if (right - '0' < 0)
				T[i].Right = -1;
			else {
				T[i].Right = right - '0';
				check[T[i].Right] = 1;
			}
		}
		for (root = 0; root < num; ++root)
			if (!check[root])
				break;
	}

	void HierTraversal() {			//层次遍历
		std::queue<TreeNode> traver;
		TreeNode temp;
		traver.push(T[root]);
		while (!traver.empty()) {
			temp = traver.front();
			traver.pop();
			if (temp.Left != -1)
				traver.push(T[temp.Left]);
			if (temp.Right != -1)
				traver.push(T[temp.Right]);
			if (temp.Left == -1 && temp.Right == -1) {
				printf("%d", temp.data);
				if (!traver.empty())
					printf(" ");
			}
		}
	}
};

int main()
{
	int num;
	scanf("%d", &num);
	Solution s(num);
	s.BuildTree();
	s.HierTraversal();
	return 0;
}