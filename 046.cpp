#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

class Solution {
private:
	int num;
	int* Leave, * CBST;                 //用数组存储树

	int GetLeftLength(int n) {          //计算左子树有多少个结点
		int H, X, L;

		H = (int)log2(n + 1);
		X = n - (int)pow(2, H) + 1;
		X = X > (int)pow(2, H - 1) ? (int)pow(2, H - 1) : X;
		L = (int)pow(2, H - 1) - 1 + X;

		return L;
	}
public:
	Solution(int n) {
		num = n;
		Leave = new int[n];             //开辟内存
		CBST = new int[n];
	}

	void Input() {
		for (int i = 0; i < num; ++i)
			cin >> Leave[i];
		sort(Leave, Leave + num);
	}

	void Complete_BST(int ALeft, int ARight, int TRoot) {
		int n, L, LeftTRoot, RightTRoot;

		n = ARight - ALeft + 1;         //本次树的结点
		if (n == 0)
			return;
		L = GetLeftLength(n);
		CBST[TRoot] = Leave[ALeft + L]; //存储根节点值
		LeftTRoot = TRoot * 2 + 1;      //左子树根节点位置
		RightTRoot = LeftTRoot + 1;     //右子树根节点位置

		Complete_BST(ALeft, ALeft + L - 1, LeftTRoot);
		Complete_BST(ALeft + L + 1, ARight, RightTRoot);
	}

	void print() {
		for (int i = 0; i < num; ++i) {
			cout << CBST[i];
			if (i != num - 1)
				cout << " ";
		}
	}
};

int main()
{
	int n;
	cin >> n;
	Solution s(n);
	s.Input();
	s.Complete_BST(0, n - 1, 0);
	s.print();
	return 0;
}