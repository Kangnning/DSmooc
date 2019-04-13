#include<iostream>
#include<stack>
#include<vector>
#include<string>
using namespace std;

class Solution {
private:
	int num;
	vector<int> Preorder;
	vector<int> Inorder;
	vector<int> Postorder;
public:
	Solution(int n) :num(n) { Postorder.assign(num, 0); }		//给Postorder分配内存
	int* getPostPosi() { return Postorder.data(); }				//返回Postorder的地址，方便修改
	void Input() {												//模拟堆栈，输入前序中序遍历
		stack<int> temp_stack;
		int temp_data;
		string tmp;
		for (int i = 0; i < 2 * num; ++i) {
			cin >> tmp;
			if (tmp[1] == 'u') {
				cin >> temp_data;
				temp_stack.push(temp_data);
				Preorder.push_back(temp_data);
			}
			else {
				Inorder.push_back(temp_stack.top());
				temp_stack.pop();
			}
		}
	}

	void PostOrder(int preL, int inL, int postL, int n, int* post) {
		int root;
		int i, L, R;

		if (n == 0)					//树为空
			return;
		if (n == 1) {				//树只有一个结点
			post[postL] = Preorder[preL];
			return;
		}

		root = Preorder[preL];		//此次的根结点
		post[postL + n - 1] =  root;//将根结点插入后序遍历
		for (i = 0; i < n; i++)
			if (Inorder[inL + i] == root)
				break;

		L = i;						//左子树的结点数	
		R = n - L - 1;				//右子树的结点数
		PostOrder(preL + 1, inL, postL, L, post);
		PostOrder(preL + L + 1, inL + L + 1, postL + L, R, post);
	}

	void print() {
		for (int i = 0; i < num; ++i) {
			cout << Postorder[i];
			if (i != num - 1)
				cout << " ";
		}
	}
};

int main()
{
	int n;
	int* posi;
	cin >> n;
	Solution s(n);
	s.Input();
	posi = s.getPostPosi();
	s.PostOrder(0, 0, 0, n, posi);
	s.print();
	return 0;
}