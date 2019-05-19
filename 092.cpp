#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class Solution {
private:
	int N;
	vector<int> OrignSeq;
	vector<int> MiddleSeq;
public:
	Solution(int N) {
		this->N = N;
		OrignSeq.assign(N, 0);
		MiddleSeq.assign(N, 0);
	}

	void InputSeq() {
		for (int i = 0; i < N; ++i)
			cin >> OrignSeq[i];
		for (int i = 0; i < N; ++i)
			cin >> MiddleSeq[i];
	}

	void Judge() {
		int i, count, length;
		bool flag = true;
		//插入排序的特点，前面有序，后面无序
		for (i = 1; MiddleSeq[i] >= MiddleSeq[i - 1]; ++i);
		count = i;
		for (; i < N && MiddleSeq[i] == OrignSeq[i]; ++i);

		if (i == N) {
			cout << "Insertion Sort" << endl;
			sort(MiddleSeq.begin(), MiddleSeq.begin() + count + 1);//再进行一次插入排序
			cout << MiddleSeq[0];
			for (i = 1; i < N; ++i)
				cout << " " << MiddleSeq[i];
		}
		else {
			cout << "Merge Sort" << endl;
			//判断每次一归并排序的边界是否已经排好序
			for (length = 2; flag; length *= 2) {
				for (i = length; i < N; i += length * 2) {
					if (MiddleSeq[i - 1] > MiddleSeq[i]) {
						flag = false;
						break;
					}
				}
			}
			//在这里还有一种判断方法，就是以每一组内数字进行判断，若组内不等，则可知道目前最大长度是多少，进行下一次的归并
			//数据过大会超时
			/*for (length = 2; flag; length *= 2) {
				count = 0;
				for (i = length; i < N && flag; i += length) {
					for (int j = count * i; j < (count + 1) * 2 && j < (N - 1); ++j) {
						if (MiddleSeq[j] > MiddleSeq[j + 1]) {
							flag = false;
							break;
						}
					}
					++count;
				}
			}*/
			//再进行一次归并排序
			for (i = 0; i + length <= N; i += length)
				sort(MiddleSeq.begin() + i, MiddleSeq.begin() + i + length);
			//若最后所剩的数不够一组，则对剩余所有数字排序
			sort(MiddleSeq.begin() + i, MiddleSeq.end());
			cout << MiddleSeq[0];
			for (i = 1; i < N; ++i)
				cout << " " << MiddleSeq[i];
		}
	}
};

int main() {
	int N;
	cin >> N;
	Solution s(N);
	s.InputSeq();
	s.Judge();
	return 0;
}