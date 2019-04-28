#include<iostream>
#include<queue>
#include<memory>
#include<iomanip>
#define NodePosi GNode*
using namespace std;

struct GNode {
	int data;
	NodePosi next;
	GNode() :data(0), next(nullptr) {}
	GNode(int d) :data(d), next(nullptr) {}
};

class Solution {
private:
	int N, M;
	NodePosi FirstEdge;

	int BFS(int v) {
		bool* visited = new bool[N]();
		int count = 1, level = 0, last = v, tail;
		NodePosi temp;
		NodePosi frontemp;
		queue<GNode> Q;
		visited[v - 1] = true;
		Q.push(FirstEdge[v - 1]);
		while (!Q.empty()) {
			frontemp = &FirstEdge[Q.front().data - 1];
			Q.pop();
			for (temp = frontemp->next; temp != nullptr; temp = temp->next) {
				if (!visited[temp->data - 1]) {
					visited[temp->data - 1] = true;
					Q.push(FirstEdge[temp->data - 1]);
					++count;
					tail = temp->data;
				}
			}
			if (frontemp->data == last) {
				++level;
				last = tail;
			}
			if (level == 6)
				break;
		}
		delete[] visited;
		return count;
	}

	void Output(int i, double socre) {
		cout << i << ": ";
		cout << setiosflags(ios::fixed) << setprecision(2) << socre * 100 << "%" << endl;
	}

public:
	Solution(int n, int m) {
		N = n;
		M = m;
		FirstEdge = new GNode[n];
		for (int i = 0; i < n; ++i)
			FirstEdge[i].data = i + 1;
	}

	~Solution() {
		NodePosi temp;
		NodePosi p;
		for (int i = 0; i < N; ++i) {
			temp = FirstEdge[i].next;
			p = temp->next;
			while (p != nullptr) {
				delete temp;
				temp = p;
				p = p->next;
			}
			delete temp;
		}
		delete[] FirstEdge;
	}

	void BuildGraph() {
		int temp0, temp1;
		NodePosi p;
		for (int i = 0; i < M; ++i) {
			cin >> temp0 >> temp1;
			p = &FirstEdge[temp0 - 1];
			while (p->next != nullptr)
				p = p->next;
			p->next = new GNode(temp1);		//构建图的边
			p = &FirstEdge[temp1 - 1];
			while (p->next != nullptr)
				p = p->next;
			p->next = new GNode(temp0);		//无向图，构建两次
		}
	}

	void SDS() {
		for (int i = 1; i <= N; ++i) {
			int count = BFS(i);
			Output(i, static_cast<double>(count) / N);//因为两个均为整型，所以将其中一个数转换为double，则根据运算规则生成double
		}
	}
};

int main()
{
	int N, M;
	cin >> N >> M;
	Solution s(N, M);
	s.BuildGraph();
	s.SDS();
	return 0;
}