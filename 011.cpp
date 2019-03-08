#include<cstdio>
#include<vector>
using namespace std;

class Soultion {
private:
	int K, maxsum, thissum;
	vector<int> v;
public:
	Soultion(int num) :K(num), maxsum(0), thissum(0){}
	void input();
	int max_sub_sum();
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
		thissum += v[i];			//求出当前序列的和
		if (thissum > maxsum)		//若大于已知最大值，则代替
			maxsum = thissum;
		else if (thissum < 0)		//若当前和小于0，则重新开始
			thissum = 0;
	}
	return maxsum;
}

int main() {
	int K;
	scanf("%d", &K);
	Soultion sou(K);
	sou.input();
	printf("%d\n", sou.max_sub_sum());
	return 0;
}