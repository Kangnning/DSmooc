#include<iostream>
#include<cmath>
using namespace std;

struct Coord {
	int x, y;		//根据题目所给数据可以看出，整型足够用
};

class Solution {
private:
	int N, D;
	Coord* coordinate;
	int* visited;
	//第一次跳跃需要考虑岛的半径
	int FirstJump(int i) {
		return (sqrt(pow(coordinate[i].x, 2) + pow(coordinate[i].y, 2)) <= (D + 15));
	}

	int Jump(int i, int j) {
		return (sqrt(pow(coordinate[i].x - coordinate[j].x, 2) + 
			pow(coordinate[i].y - coordinate[j].y, 2)) <= D);	//两条鳄鱼之间的距离
	}

	//判断是否可以上岸
	bool IsSafe(int i) {
		int X_distant, Y_distant;

		X_distant = abs(coordinate[i].x) - 50;
		Y_distant = abs(coordinate[i].y) - 50;

		return (abs(X_distant) <= D || abs(Y_distant) <= D);
	}

	bool DFS(int i) {
		bool answer = false;
		visited[i] = 1;
		if (IsSafe(i))
			answer = true;
		else {
			for (int j = 0; j < N; ++j) {
				if (!visited[j] && Jump(i, j)) {
					answer = DFS(j);
					if (answer == true)
						break;
				}
			}
		}
		return answer;
	}

public:
	Solution(int n, int d) {
		N = n;
		D = d;
		coordinate = new Coord[n];
		visited = new int[n]();
	}

	void InputPosi() {
		for (int i = 0; i < N; ++i)
			cin >> coordinate[i].x >> coordinate[i].y;
	}

	void Save007() {
		bool answer = false;
		for (int i = 0; i < N; ++i) {
			if (!visited[i] && FirstJump(i)) {
				answer = DFS(i);
				if (answer == true)
					break;
			}
		}
		if (answer == true)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
};

int main()
{
	int N, D;
	cin >> N >> D;
	Solution s(N, D);
	s.InputPosi();
	s.Save007();
	return 0;
}