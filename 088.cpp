#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
private:
	vector<vector<int>> Edge;
	vector<int> Distance;
	vector<int> InDegree;
	int N, M;

	int TopSort() {
		queue<int> q;
		int cnt = 0;
		for (int i = 0; i < N; ++i)
			if (InDegree[i] == 0)
				q.push(i);

		while (!q.empty()) {
			int v = q.front();
			++cnt;
			q.pop();
			for (int i = 0; i < N; ++i) {
				if (Edge[v][i] != -1) {
					Distance[i] = max(Distance[i], Edge[v][i] + Distance[v]);
					if (--InDegree[i] == 0)
						q.push(i);
				}
			}
		}

		if (cnt == N)
			return 0;
		else
			return 1;
	}

public:
	Solution(int N, int M) {
		this->N = N;
		this->M = M;
		InDegree.assign(N, 0);
		Distance.assign(N, 0);
		vector<int> temp;
		for (int i = 0; i < N; ++i) {
			temp.assign(N, -1);
			Edge.push_back(temp);
			temp.clear();
		}
	}

	void InputWeight() {
		int start, end, cost;
		for (int i = 0; i < M; ++i) {
			cin >> start >> end >> cost;
			Edge[start][end] = cost;
			++InDegree[end];
		}
	}

	void PrintResult() {
		int res = TopSort();
		if (res)
			cout << "Impossible";
		else {
			int cost = -1;
			for (int i = 0; i < N; ++i)
				if (cost < Distance[i])
					cost = Distance[i];

			cout << cost;
		}
	}
};

int main() {
	int N, M;
	cin >> N >> M;
	Solution s(N, M);
	s.InputWeight();
	s.PrintResult();
	return 0;
}