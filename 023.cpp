//最大数据测试超时
#include<cstdio>
#define NodePosi Node*

struct Node {
	int address, next, data;
	NodePosi succ;
	Node():succ(nullptr) {}			//头结点构造
	Node(int posi, int next_posi, int value) :address(posi), next(next_posi), data(value), succ(nullptr) {}
};

class Solution {
private:
	int start_posi, num, K;
	NodePosi head;
	NodePosi link;
public:
	Solution(int start, int n, int k) :start_posi(start), num(n), K(k), head(new Node) {}
	~Solution() { del(head); }

	int getnum() { return num; }
	NodePosi gethead() { return head; }

	void del(NodePosi p) {
		NodePosi temp;
		while (p->succ != nullptr) {
			temp = p->succ;
			delete p;
			p = temp;
		}
		delete p;
	}

	void input() {
		int address, next_address, data;
		link = head;
		for (int i = 0; i < num; ++i) {
			scanf("%d %d %d", &address, &data, &next_address);
			NodePosi temp = new Node(address, next_address, data);
			link->succ = temp;
			link = link->succ;
		}
	}
	//对结点按照初始顺序排序
	void rearrange() {
		int temp_num = 1;
		NodePosi new_head = nullptr;
		NodePosi temp_link = nullptr;
		for (int i = 0; i < num; ++i) {
			link = head->succ;
			if (i == 0) {
				while (!(link->address == start_posi))
					link = link->succ;
				new_head = new Node(link->address, link->next, link->data);
				temp_link = new_head;
			}
			else {
				if (temp_link->next == -1)
					break;
				while (!(link->address == temp_link->next))
					link = link->succ;
				NodePosi temp = new Node(link->address, link->next, link->data);
				temp_link->succ = temp;
				temp_link = temp_link->succ;
				++temp_num;
			}
		}
		del(head->succ);
		head->succ = new_head;
		if (temp_num != num)				//因为内存中可能会有无用结点，因此这里只存储有用结点个数，便于后续操作
			num = temp_num;
	}

	NodePosi reverse(NodePosi Lhead, int k, int n) {
		NodePosi new_node = Lhead;
		NodePosi old_node = new_node->succ;
		NodePosi tmp;
		int cnt = 1;
		while (cnt < K) {					//完成一次翻转
			tmp = old_node->succ;
			old_node->succ = new_node;
			old_node->next = new_node->address;
			new_node = old_node;
			old_node = tmp;
			++cnt;
		}
		Lhead->succ = old_node;
		if (n == num / K)					//若是第一次递归，则修改head结点指向的第一个数据
			head->succ = new_node;

		if (old_node != nullptr)
			Lhead->next = old_node->address;
		else
			Lhead->next = -1;

		if (--n) {							//若还未处理完整个链表，则递归进行
			Lhead->succ = reverse(Lhead->succ, k, n);
			Lhead->next = Lhead->succ->address;
		}

		return new_node;
	}

	void print() {
		link = head->succ;
		for (int i = 0; i < num; ++i) {
			if (link->next != -1)
				printf("%05d %d %05d\n", link->address, link->data, link->next);
			else {
				printf("%05d %d %d\n", link->address, link->data, link->next);
				break;
			}
			link = link->succ;
		}
	}
};

int main()
{
	int start, num, k;
	scanf("%d %d %d", &start, &num, &k);
	Solution s(start, num, k);
	s.input();
	s.rearrange();
	if (k != 1)				//若K为1，则不用翻转
		s.reverse(s.gethead()->succ, k, s.getnum() / k);
	s.print();
	return 0;
}