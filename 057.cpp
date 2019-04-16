#include<iostream>
#include<climits>
using namespace std;

class Solution {
private:
	int n;
	int m;
	int size;
	int* MinHeap;
public:
	Solution(int N, int M) {
		n = N;
		m = M;
		size = 0;
		MinHeap = new int[N + 1];
		MinHeap[0] = INT_MIN;		//设置哨兵
	}

	void InputData() {
		int x;
		for (int i = 0; i < n; ++i) {
			cin >> x;
			Insert(x);
		}	
	}
	
	void Insert(int x) {
		int i;
		for (i = ++size; MinHeap[i / 2] > x; i /= 2)	//若插入数据比根大，则根下潜
			MinHeap[i] = MinHeap[i / 2];
		MinHeap[i] = x;
	}

	void Print() {
		int j;
		for (int i = 0; i < m; i++) {
			cin >> j;
			cout << MinHeap[j];
			if (j > 1)
				cout << " ";
			while (j > 1) {
				j /= 2;
				cout << MinHeap[j];
				if (j > 1)
					cout << " ";
			}
			cout << endl;
		}
	}
};

int main()
{
	int n, m;
	cin >> n >> m;
	Solution s(n, m);
	s.InputData();
	s.Print();
	return 0;
}