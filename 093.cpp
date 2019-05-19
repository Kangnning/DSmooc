#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class Solution {
private:
	int N;
	vector<int> OrignSeq;
	vector<int> MiddleSeq;

	bool IsSame(vector<int>& SortSeq) {
		bool flag = true;
		for (int i = 0; i < N; ++i) {
			if (SortSeq[i] != MiddleSeq[i]) {
				flag = false;
				break;
			}
		}
		return flag;
	}

	void PercDown(int p, int n) {
		int Parent, Child;
		int X;

		X = OrignSeq[p];
		for (Parent = p; (Parent * 2 + 1) < n; Parent = Child) {
			Child = Parent * 2 + 1;
			if ((Child != n - 1) && (OrignSeq[Child] < OrignSeq[Child + 1]))
				++Child;
			if (X >= OrignSeq[Child]) break;
			else
				OrignSeq[Parent] = OrignSeq[Child];
		}
		OrignSeq[Parent] = X;
	}

	void Heap_Sort() {
		int i;

		for (i = N / 2 - 1; i >= 0; --i)
			PercDown(i, N);

		for (i = N - 1; i > 0; --i)
		{
			int temp = OrignSeq[0];
			OrignSeq[0] = OrignSeq[i];
			OrignSeq[i] = temp;
			PercDown(0, i);
			if (IsSame(OrignSeq))
				break;
		}
		//再进行一次heapsort
		--i;
		int temp = OrignSeq[0];
		OrignSeq[0] = OrignSeq[i];
		OrignSeq[i] = temp;
		PercDown(0, i);
	}

public:
	Solution(int N) {
		this->N = N;
		OrignSeq.assign(N, 0);
		MiddleSeq.assign(N, 0);
	}

	void InputSeq() {
		for (int i = 0; i < N; ++i)
			cin >> OrignSeq[i];
		for (int i = 0; i < N; ++i)
			cin >> MiddleSeq[i];
	}

	void Judge() {
		int i, count, length;
		bool flag = true;
		//插入排序的特点，前面有序，后面无序
		for (i = 1; MiddleSeq[i] >= MiddleSeq[i - 1]; ++i);
		count = i;
		for (; i < N && MiddleSeq[i] == OrignSeq[i]; ++i);

		if (i == N) {
			cout << "Insertion Sort" << endl;
			sort(MiddleSeq.begin(), MiddleSeq.begin() + count + 1);//再进行一次插入排序
			cout << MiddleSeq[0];
			for (i = 1; i < N; ++i)
				cout << " " << MiddleSeq[i];
		}
		else {
			cout << "Heap Sort" << endl;
			Heap_Sort();
			cout << OrignSeq[0];
			for (i = 1; i < N; ++i)
				cout << " " << OrignSeq[i];
		}
	}
};

int main() {
	int N;
	cin >> N;
	Solution s(N);
	s.InputSeq();
	s.Judge();
	return 0;
}