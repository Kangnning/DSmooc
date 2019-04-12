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
	Solution(int n) :num(n) { Postorder.assign(num, 0); }
	int* getPostPosi() { return Postorder.data(); }
	void Input() {
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

		if (n == 0)
			return;
		if (n == 1) {
			post[postL] = Preorder[preL];
			return;
		}

		root = Preorder[preL];
		post[postL + n - 1] =  root;
		for (i = 0; i < n; i++)
			if (Inorder[inL + i] == root)
				break;

		L = i;
		R = n - L - 1;
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