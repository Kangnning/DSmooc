#include<iostream>
#include<vector>
using namespace std;

class Solution {
private:
	int N, count;
	vector<int> data;
	vector<int> point;

	void CountSwapTimes() {
		vector<bool> visited;
		visited.assign(N, false);
		for (int i = 0; i < N; ++i) {
			int j = i;
			if (data[i] == i && !visited[i])
				visited[i] = true;
			else if (data[i] != i && !visited[i]) {
				while (!visited[j]) {
					if (j == 0)
						count -= 1;//如果多元环含0，则交换次数为n-1
					else
						++count;
					visited[j] = true;
					j = point[j];
				}
				++count;//如果多元环不含0，则交换次数为n+1
			}
		}
	}

public:
	Solution(int N) {
		this->N = N;
		count = 0;
		data.assign(N, 0);
		point.assign(N, 0);
	}

	void InputData() {
		for (int i = 0; i < N; ++i) {
			cin >> data[i];
			point[data[i]] = i;
		}
	}

	void PrintResult() {
		CountSwapTimes();
		cout << count << endl;
	}
};

int main() {
	int N;
	cin >> N;
	Solution s(N);
	s.InputData();
	s.PrintResult();
	return 0;
}