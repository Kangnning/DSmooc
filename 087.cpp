#include<iostream>
#include<vector>
#define INFINITY 65535
using namespace std;

class Solution {
private:
	int N, M;
	vector<int> distance;
	vector<vector<int>> graph;

	int FindMinDist() {
		int MinV, MinDist = INFINITY;
		for (int i = 0; i < N; ++i) {
			if (distance[i] != 0 && distance[i] < MinDist) {
				MinDist = distance[i];
				MinV = i;
			}
		}
		if (MinDist < INFINITY)
			return MinV;
		else
			return -1;
	}

	int Prim() {
		int TotalWeight, V, W;
		int Vcount;
		for (V = 0; V < N; ++V)
			distance[V] = graph[0][V];
		TotalWeight = 0;
		Vcount = 0;

		distance[0] = 0;
		++Vcount;
		while (1) {
			V = FindMinDist();
			if (V == -1)
				break;
			TotalWeight += distance[V];
			distance[V] = 0;
			++Vcount;
			for (W = 0; W < N; ++W)
				if (distance[W] != 0 && graph[V][W] < INFINITY)
					if (graph[V][W] < distance[W])
						distance[W] = graph[V][W];
		}
		if (Vcount < N)
			TotalWeight = -1;
		else
			return TotalWeight;
	}

public:
	Solution(int N, int M) {
		vector<int> temp;
		this->N = N;
		this->M = M;
		distance.assign(N, INFINITY);
		for (int i = 0; i < N; ++i) {
			temp.assign(N, INFINITY);
			graph.push_back(temp);
			temp.clear();
		}
	}

	void InputWeight() {
		int p1, p2, weight;
		for (int i = 0; i < M; ++i) {
			cin >> p1 >> p2 >> weight;
			--p1;
			--p2;
			graph[p1][p2] = graph[p2][p1] = weight;
		}
	}

	void PrintResult() {
		int res = Prim();
		cout << res << endl;
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