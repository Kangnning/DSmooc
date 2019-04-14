#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
	bool Check(vector<int> init, vector<int> needcheck, int n) {
		if (n == 0)						//迭代到最后
			return true;
		if (init[0] != needcheck[0])	//根不相等
			return false;
		bool flag = true;
		vector<int> init_left, init_right, needcheck_left, needcheck_right;
		for (int i = 1; i < n; ++i) {
			if (init[i] < init[0])
				init_left.push_back(init[i]);
			else
				init_right.push_back(init[i]);
			if (needcheck[i] < needcheck[0])
				needcheck_left.push_back(needcheck[i]);
			else
				needcheck_right.push_back(needcheck[i]);
		}

		flag = Check(init_left, needcheck_left, init_left.size()) &&
			Check(init_right, needcheck_right, init_right.size());			//取左右子树的与结果

		return flag;
	}

	void Print(bool flag) {
		if (flag)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
};

int main()
{
	int N, L, tmp;
	bool flag;
	while (1) {
		vector<int> Initial;
		cin >> N;
		if (N == 0)
			break;
		cin >> L;
		for (int i = 0; i < N; ++i) {
			cin >> tmp;
			Initial.push_back(tmp);
		}
		Solution s;
		while (L--) {
			vector<int> NeedCheck;
			for (int i = 0; i < N; ++i) {
				cin >> tmp;
				NeedCheck.push_back(tmp);
			}
			flag = s.Check(Initial, NeedCheck, N);
			s.Print(flag);
		}
	}
	return 0;
}