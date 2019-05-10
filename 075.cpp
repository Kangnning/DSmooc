#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<vector>
#include<algorithm>

struct Point {
	int x;
	int y;
};

using namespace std;
const double D = 15.0;
double jump;
Point crocodile[101];
int n;
bool cmp(int i, int j);
int bfs(int& v, vector<int>& path);
bool Jump(int v, int i, int jump);
double FirstJump(int i);

bool Jump(int v, int i, int jump) {
	return (sqrt(pow(crocodile[v].x - crocodile[i].x, 2) +
		pow(crocodile[v].y - crocodile[i].y, 2)) <= jump);
}

double FirstJump(int i) {
	return (sqrt(pow(crocodile[i].x, 2) + pow(crocodile[i].y, 2)));
}

int main() {
	int i, v = 0, flag = 0;
	scanf("%d%lf", &n, &jump);
	vector<int> path(n + 1, -1), spath;
	crocodile[0].x = 0;
	crocodile[0].y = 0;
	for (i = 1; i <= n; i++)
		scanf("%d%d", &crocodile[i].x, &crocodile[i].y);
	if (jump + D / 2 >= 50) //从岛上可以直接到岸
		flag = 1;
	else flag = bfs(v, path);
	if (!flag) printf("0");
	else {
		while (v) {
			spath.push_back(v);
			v = path[v];
		}
		printf("%d\n", spath.size() + 1);
		for (i = spath.size() - 1; i >= 0; i--)
			printf("%d %d\n", crocodile[spath[i]].x, crocodile[spath[i]].y);
	}
	return 0;
}


int bfs(int& v, vector<int> & path) {
	vector<int> dist(n + 1, -1), first(n + 1);
	queue<int> q;
	double firstdis;
	int flag = 0, i;
	dist[v] = 0;
	for (i = 0; i < n + 1; i++)
		first[i] = i;
	sort(first.begin(), first.end(), cmp);
	for (i = 1; i < n + 1; i++) {
		v = first[i];
		firstdis = FirstJump(v);
		if (firstdis > D / 2 && firstdis <= jump + D / 2) {
			q.push(v);
			dist[v] = 1;
			path[v] = 0;
		}
	}
	while (!q.empty()) {
		v = q.front();
		q.pop();
		if ((fabs(crocodile[v].x) + jump >= 50 || fabs(crocodile[v].y) + jump >= 50)) {
			flag = 1;
			break;
		}
		else {
			for (i = 1; i < n + 1; i++) {
				if (dist[i] == -1 && Jump(v, i, jump)) {
					dist[i] = dist[v] + 1;
					path[i] = v;
					q.push(i);
				}
			}
		}
	}
	return flag;
}

bool cmp(int i, int j) {
	return pow(crocodile[i].x, 2) + pow(crocodile[i].y, 2) < 
		pow(crocodile[j].x, 2) + pow(crocodile[j].y, 2);
}