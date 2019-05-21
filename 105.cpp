/*未能通过全部测试点，数目多了会超时，且第一个
测试点没过去，按照我的理解，目前不知道如何改了*/

#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

struct User {
	vector<int> score;
	int total_score;
	int perfect;
	User(int K) {
		score.assign(K, -2);
		total_score = -1;
		perfect = 0;
	}
};

class Solution {
private:
	int N, K, M, minIndex;
	vector<int> full_score;
	vector<User> user;
	vector<int> SortIndex;

    //计算每个人的总分以及完美解决的题目数量
	void Sum() {
		int temp;
		for (int i = 0; i < N; ++i) {
			temp = 0;
			for (int j = 0; j < K; ++j) {
				if (user[i].score[j] != -1 && user[i].score[j] != -2) {
					temp += user[i].score[j];
				}
				if (user[i].score[j] == full_score[j])
					++user[i].perfect;
			}
			if (temp != 0 && minIndex == -1)
				minIndex = i;
			if (temp != 0) {
				user[i].total_score = temp;
				if (minIndex != -1 && temp < user[minIndex].total_score)
					minIndex = i;
			}
		}
	}
	
    //按照规则进行排序
	void Sort() {
		int i = 0, max;
		vector<bool> visited;
		visited.assign(N, true);
		for (; i < N; ++i) {
			max = minIndex;
			for (int j = 0; j < N; ++j) {
				if (visited[j] && user[j].total_score > user[max].total_score)
					max = j;
				else if (visited[j] && user[j].total_score == user[max].total_score)
					if (user[j].perfect > user[max].perfect)
						max = j;
			}
			if (visited[max]) {
				visited[max] = false;
				SortIndex.push_back(max);
			}
		}
	}

public:
	Solution(int N, int K, int M) {
		this->N = N;
		this->M = M;
		this->K = K;
		minIndex = -1;
		full_score.assign(K, 0);
		user.assign(N, K);
	}

	void InputData() {
		int user_pos, pro_pos, temp;
		for (int i = 0; i < K; ++i)
			cin >> full_score[i];
		for (int i = 0; i < M; ++i) {
			cin >> user_pos >> pro_pos >> temp;
			--user_pos;
			--pro_pos;
			if (temp > user[user_pos].score[pro_pos])
				user[user_pos].score[pro_pos] = temp;
		}
		Sum();
	}

	void Result() {
		Sort();
		for (unsigned int i = 0; i < SortIndex.size(); ++i) {
			printf("%d %05d %d", i + 1, SortIndex[i] + 1, user[SortIndex[i]].total_score);
			for (int j = 0; j < K; ++j) {
				if (user[SortIndex[i]].score[j] == -1)
					printf(" 0");
				else if (user[SortIndex[i]].score[j] == -2)
					printf(" -");
				else
					printf(" %d", user[SortIndex[i]].score[j]);
			}
			printf("\n");
		}
	}
};

int main() {
	int N, K, M;
	cin >> N >> K >> M;
	Solution s(N, K, M);
	s.InputData();
	s.Result();
	return 0;
}