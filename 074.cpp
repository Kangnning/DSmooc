#include<iostream>
#define MaxVertexNum 100
#define Edge ENode*
#define PtrToGNode GNode*
#define INFINITY 65535
using namespace std;

struct ENode {
	int v1, v2;
	int weight;
	ENode(int v1, int v2, int weight) {
		this->v1 = v1;
		this->v2 = v2;
		this->weight = weight;
	}
};

struct GNode {
	int Nv;
	int Ne;
	int G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

class Solution {
private:
	MGraph Graph;

	void Floyd(int D[][MaxVertexNum]) {
		int i, j, k;

		for (i = 0; i < Graph->Nv; i++)
			for (j = 0; j < Graph->Nv; j++)
				D[i][j] = Graph->G[i][j];

		for (k = 0; k < Graph->Nv; k++)
			for (i = 0; i < Graph->Nv; i++)
				for (j = 0; j < Graph->Nv; j++)
					if (D[i][k] + D[k][j] < D[i][j])
						D[i][j] = D[i][k] + D[k][j];
	}

	int FindMaxDist(int D[][MaxVertexNum], int i, int n) {
		int MaxDist = 0;

		for (int j = 0; j < n; ++j)
			if (i != j && D[i][j] > MaxDist)
				MaxDist = D[i][j];

		return MaxDist;
	}

public:
	Solution(int N, int M) {
		Graph = new GNode;
		Graph->Nv = N;
		Graph->Ne = M;
		for (int i = 0; i < Graph->Nv; ++i)
			for (int j = 0; j < Graph->Nv; ++j)
				Graph->G[i][j] = INFINITY;
	}

	void BuildGraph() {
		Edge E;
		if (Graph->Ne != 0) {
			for (int i = 0; i < Graph->Ne; i++) {
				int v1, v2, weight;
				cin >> v1 >> v2 >> weight;
				E = new ENode(v1, v2, weight);
				--E->v1;
				--E->v2;
				Graph->G[E->v1][E->v2] = E->weight;
				Graph->G[E->v2][E->v1] = E->weight;
			}
		}
	}

	void FindAnimal() {
		int D[MaxVertexNum][MaxVertexNum], MaxDist, MinDist, Animal;
		Floyd(D);
		MinDist = INFINITY;

		for (int i = 0; i < Graph->Nv; ++i) {
			MaxDist = FindMaxDist(D, i, Graph->Nv);
			if (MaxDist == INFINITY) {
				cout << "0" << endl;
				return;
			}
			if (MinDist > MaxDist) {
				MinDist = MaxDist;
				Animal = i + 1;
			}
		}
		cout << Animal << " " << MinDist << endl;
	}
};

int main()
{
	int N, M;
	cin >> N >> M;
	Solution s(N, M);
	s.BuildGraph();
	s.FindAnimal();
	return 0;
}