#include<iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

struct Node
{
	string account;
	string password;
	Node() :account("None"), password("None") {}
};

class Solution {
private:
	int N;
	int TableSize;
	vector<int> Number;//记录相应位置有多少个数据
	vector<vector<Node>> HashTable;

	int GetNextPrime(int x) {
		if (x == 1)
			return 2;
		int tmp, i;
		tmp = x % 2 == 1 ? x : x + 1;//偶数肯定不是素数，所以只计算奇数
		while (true) {
			for (i = sqrt(tmp); i >= 2; --i)
				if (tmp % i == 0)
					break;
			if (i == 1)//则tmp为素数
				break;
			else
				tmp += 2;
		}
		return tmp;
	}

	int GetPosition(string account) {
		int tmp = 0, pos;
		for (int i = 0; i < 4; ++i)//选取字符串前四位作为初始散列地址
			tmp = tmp * 10 + (account[i] - '0');
		pos = tmp % TableSize;
		return pos;
	}

	void Insert(int position, string account, string password) {
		++Number[position];
		Node tmp;
		tmp.account = account;
		tmp.password = password;
		HashTable[position].push_back(tmp);
	}

	void isInsert(int position, string account, string password) {
		if (Number[position] == 0) {
			Insert(position, account, password);
			cout << "New: OK" << endl;
		}
		else {
			bool flag = true;
			for (int i = 1; i <= Number[position]; ++i) {
				if (HashTable[position][i].account == account) {
					flag = false;
					break;
				}
			}
			if (flag) {
				Insert(position, account, password);
				cout << "New: OK" << endl;
			}
			else
				cout << "ERROR: Exist" << endl;
		}
	}

	void SignIn(int position, string account, string password) {
		bool flag = false;
		int i;
		for (i = 1; i <= Number[position]; ++i) {
			if (HashTable[position][i].account == account) {
				flag = true;
				break;
			}
		}
		if (flag) {
			if (HashTable[position][i].password == password)
				cout << "Login: OK" << endl;
			else
				cout << "ERROR: Wrong PW" << endl;
		}
		else
			cout << "ERROR: Not Exist" << endl;
	}

public:
	Solution(int n) {
		N = n;
		vector<Node> tmp;
		TableSize = GetNextPrime(n);
		Number.assign(TableSize, 0);
		for (int i = 0; i < TableSize; ++i) {
			tmp.push_back(Node());
			HashTable.push_back(tmp);//vector必须有数据才能进行下标索引
			tmp.clear();
		}
	}

	void Result() {
		int posi;
		string command, account, password;
		for (int i = 0; i < N; ++i) {
			cin >> command >> account >> password;
			posi = GetPosition(account);
			if (command == "N") {
				isInsert(posi, account, password);
			}
			else {
				SignIn(posi, account, password);
			}
		}
	}
};

int main() {
	int N;
	cin >> N;
	Solution s(N);
	s.Result();
	return 0;
}