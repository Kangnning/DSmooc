#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class Solution {
private:
	int M, N;
	vector<int> HashTable;

	int GetNextPrime(int x) {
		if (x == 1)
			return 2;
		int tmp, i;
		tmp = x % 2 == 1 ? x : x + 1;//偶数肯定不是素数，所以只计算奇数
		while (true) {
			for (i = sqrt(tmp); i >= 2; --i)
				if (tmp % i == 0)
					break;
			if (i == 1)//则tmp为素数
				break;
			else
				tmp += 2;
		}
		return tmp;
	}

	int GetPos(int data) {
		int oldkey, newkey, step, retpos;
		oldkey = data % M;
		newkey = oldkey;
		step = 1;
		while (true) {
			if (HashTable[newkey] == -1) {
				HashTable[newkey] = data;//若该键未被占用，则占用
				retpos = newkey;
				break;
			}
			else {
				newkey = (oldkey + step * step) % M;//若产生冲突，则寻找新的键
			}
			++step;
			if (step > M) {
				retpos = -1;
				break;
			}
		}
		return retpos;
	}

public:
	Solution(int m, int n) :M(GetNextPrime(m)), N(n) {
		HashTable.assign(M, -1);
	}

	void Print() {
		int tmp, pos;
		for (int i = 0; i < N; ++i) {
			cin >> tmp;
			pos = GetPos(tmp);
			if (pos == -1)
				cout << "-";
			else
				cout << pos;
			if (i != N - 1)
				cout << " ";
			else
				cout << endl;
		}
	}
};

int main() {
	int m, n;
	cin >> m >> n;
	Solution s(m, n);
	s.Print();
	return 0;
}