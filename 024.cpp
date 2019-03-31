#include<cstdio>
#include<stack>
#include<vector>
using namespace std;

class Solution {
private:
	int M, N;
	stack<int> s;
public:
	Solution(int m, int n) :M(m), N(n) {}
	bool check_seq(vector<int> seq) {
		int num = 1;
		bool flag = true;
		for (int i = 0; i < N; i++) {
			if (s.size() == 0) {	//每次栈为空时，压入一个数据
				s.push(num);
				++num;
			}
			if (seq[i] > s.top()) {
				for (; num <= seq[i]; ++num) {
					if (s.size() < M)//栈是否超过了最大容纳的数据量
						s.push(num);
					else {
						flag = 0;
						break;
					}
				}
				s.pop();
			}
			else if (seq[i] == s.top())//若结束之后栈不为空，则将其清空
				s.pop();
			else {
				flag = 0;
				break;
			}
		}
		while (!s.empty())
			s.pop();
		return flag;
	}
	void print(bool flag) {
		if (flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
};

int main()
{
	int M, N, K, temp;
	vector<int> seq;
	bool flag;
	scanf("%d %d %d", &M, &N, &K);
	Solution sol(M, N);
	for (int i = 0; i < K; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &temp);
			seq.push_back(temp);
		}
		flag = sol.check_seq(seq);
		sol.print(flag);
		seq.clear();
	}
	return 0;
}