#include<cstdio>
#define MaxTreeNode 10

struct TreeNode {
	char Element;
	int Left;
	int Right;
};

class Solution {
private:
	TreeNode T1[MaxTreeNode], T2[MaxTreeNode];
	int root1, root2;
	int num1, num2;
public:
	void set_num1(int num) { num1 = num; }
	void set_num2(int num) { num2 = num; }
	int get_root1() { return root1; }
	int get_root2() { return root2; }
	int BuildTree(TreeNode T[], int num) {
		if (!num)
			return -1;
		int check[MaxTreeNode] = { 0 };
		int posi;
		char left, right;
		for (int i = 0; i < num; ++i) {
			getchar();
			scanf("%c %c %c", &T[i].Element, &left, &right);
			if (left - '0' < 0)			//'-'的ASCII码值为45,'0'的ASCII值为48
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
		for (posi = 0; posi < num; ++posi)
			if (!check[posi])
				break;
		return posi;
	}
	void BuildT1() { root1 = BuildTree(T1, num1); }
	void BuildT2() { root2 = BuildTree(T2, num2); }

	int Isomorphic(int R1, int R2)
	{
		if (num1 != num2)//两棵树节点数不一样
			return 0;
		if ((R1 == -1) && (R2 == -1))//两棵树不存在
			return 1;
		if (((R1 == -1) && (R2 != -1)) || ((R1 != -1) && (R2 == -1)))//一棵存在一棵不存在
			return 0;
		if (T1[R1].Element != T2[R2].Element)//根节点不相等
			return 0;
		if ((T1[R1].Left == -1) && (T2[R2].Left == -1))//两棵树均无左子树
			return Isomorphic(T1[R1].Right, T2[R2].Right);
		if (((T1[R1].Left != -1) && (T2[R2].Left != -1)) && ((T1[T1[R1].Left].Element) == (T2[T2[R2].Left].Element)))//两棵树的左子树均存在且左子树的根节点相等
			return (Isomorphic(T1[R1].Left, T2[R2].Left) && Isomorphic(T1[R1].Right, T2[R2].Right));
		else
			return (Isomorphic(T1[R1].Left, T2[R2].Right) && Isomorphic(T1[R1].Right, T2[R2].Left));
	}
};

int main()
{
	int num;
	scanf("%d", &num);
	Solution s;
	s.set_num1(num);
	s.BuildT1();
	scanf("%d", &num);
	s.set_num2(num);
	s.BuildT2();
	if (s.Isomorphic(s.get_root1(), s.get_root2()))
		printf("Yes\n");
	else
		printf("No\n");
	return 0;
}