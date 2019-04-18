#include<iostream>
using namespace std;

class Solution {
private:
	int num;
	int* set;
	void Input_connection() {
		int u, v, root1, root2;
		cin >> u >> v;
		root1 = Find(u - 1);
		root2 = Find(v - 1);
		if (root1 != root2)
			Union(root1, root2);
	}

	void Check_connection() {
		int u, v, root1, root2;
		cin >> u >> v;
		root1 = Find(u - 1);
		root2 = Find(v - 1);
		if (root1 == root2)
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}

	void Check_network() {
		int count = 0;
		for (int i = 0; i < num; ++i)
			if (set[i] < 0)
				++count;

		if (count == 1)
			cout << "The network is connected." << endl;
		else
			cout << "There are " << count << " components." << endl;
	}

	void Union(int root1, int root2) {
		if (set[root2] < set[root1]) {
			set[root2] += set[root1];
			set[root1] = root2;
		}
		else {
			set[root1] += set[root2];
			set[root2] = root1;
		}
	}

	int Find(int X)
	{
		if (set[X] < 0)
			return X;
		else
			return set[X] = Find(set[X]);		//路径压缩
	}
public:
	Solution(int n) {
		num = n;
		set = new int[n];
		for (int i = 0; i < num; ++i)
			set[i] = -1;
	}

	void Input() {
		char in;
		do {
			cin >> in;
			switch (in) {
			case 'I':Input_connection(); break;
			case 'C':Check_connection(); break;
			case 'S':Check_network(); break;
			}
		} while (in != 'S');
	}
};

int main()
{
	int n;
	cin >> n;
	Solution s(n);
	s.Input();
	return 0;
}