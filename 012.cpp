#include<cstdio>
#include<vector>
using namespace std;

class Soultion {
private:
	int K, maxsum, thissum, maxstart, maxend, thisstart;
	vector<int> v;
public:
	Soultion(int num) :K(num), maxsum(0), thissum(0), maxstart(0),
		maxend(num - 1), thisstart(0) {}
	void input();
	int max_sub_sum();
	int get_start() { return maxstart; }
	int get_end() { return maxend; }
};

void Soultion::input() {
	int tmp;
	for (int i = 0; i < K; ++i) {
		scanf("%d", &tmp);
		v.push_back(tmp);
	}
}

int Soultion::max_sub_sum() {
	for (int i = 0; i < K; ++i) {
		thissum += v[i];
		if (thissum > maxsum) {
			maxsum = thissum;
			maxstart = thisstart;
			maxend = i;
		}
		else if (thissum < 0) {
			thissum = 0;
			if (i < K - 1)
				thisstart = i + 1;
		}
	}
	maxstart = v[maxstart];
	maxend = v[maxend];
	if (maxsum == 0) {
		int flag = 0;
		for (int i = 0; i < K; ++i) {
			if (v[i] == 0) {
				flag = 1;
				break;
			}
		}
		if (flag)
			maxstart = maxend = 0;
	}

	return maxsum;
}

int main() {
	int K;
	scanf("%d", &K);
	Soultion sou(K);
	sou.input();
	printf("%d", sou.max_sub_sum());
	printf(" %d %d\n", sou.get_start(), sou.get_end());
	return 0;
}