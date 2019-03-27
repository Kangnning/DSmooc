#include<cstdio>
#define ListNodePosi ListNode*

struct ListNode {
	int coef;			//系数
	int index;			//指数
	ListNodePosi succ;
	ListNode() :succ(nullptr) {}		//首结点的构造
	ListNode(int coef, int index) {
		this->coef = coef;
		this->index = index;
		succ = nullptr;
	}
};

class Unpoly {
private:
	ListNodePosi link;
	ListNodePosi L1;
	ListNodePosi L2;
	ListNodePosi L1_add_L2;
	ListNodePosi L1_mul_L2;
public:
	Unpoly() {
		L1 = new ListNode;
		L2 = new ListNode;
		L1_add_L2 = new ListNode;
		L1_mul_L2 = new ListNode;
	}

	~Unpoly() {
		del(L1);
		del(L2);
		del(L1_add_L2);
		del(L1_mul_L2);
	}

	void del(ListNodePosi L) {
		ListNodePosi temp0 = L;
		ListNodePosi temp1;
		if (L->succ != nullptr) {
			temp1 = temp0->succ;
			delete temp0;
			temp0 = temp1;
		}
		else
			delete temp0;
	}

	void input() {
		int n, temp_coef, temp_index;
		scanf("%d", &n);
		while (n--) {
			scanf("%d %d", &temp_coef, &temp_index);
			ListNodePosi temp = new ListNode(temp_coef, temp_index);
			link->succ = temp;
			link = link->succ;
		}
	}
	void input_L1() {
		link = L1;
		input();
	}
	void input_L2() {
		link = L2;
		input();
	}
	void add() {
		link = L1_add_L2;
		ListNodePosi temp1 = L1->succ;
		ListNodePosi temp2 = L2->succ;
		while (temp1 && temp2) {
			if (temp1->index == temp2->index) {
				ListNodePosi temp = new ListNode(temp1->coef + temp2->coef, temp1->index);
				temp1 = temp1->succ;
				temp2 = temp2->succ;
				if (temp->coef == 0)			//若二者相加系数为0，则不添加
					continue;
				link->succ = temp;
			}
			else if (temp1->index > temp2->index) {
				ListNodePosi temp = new ListNode(temp1->coef, temp1->index);
				link->succ = temp;
				temp1 = temp1->succ;
			}
			else {
				ListNodePosi temp = new ListNode(temp2->coef, temp2->index);
				link->succ = temp;
				temp2 = temp2->succ;
			}
			link = link->succ;
		}
		if (temp1)
			link->succ = temp1;
		else if (temp2)
			link->succ = temp2;
	}

	void mul() {
		ListNodePosi temp1 = L1->succ;
		ListNodePosi temp2 = L2->succ;
		while (temp1) {
			temp2 = L2->succ;
			while (temp2) {
				link = L1_mul_L2;
				ListNodePosi temp = new ListNode(temp1->coef * temp2->coef, temp1->index + temp2->index);
				while (link) {
					if (link->succ == nullptr) {
						link->succ = temp;
						break;
					}
					else if (link->succ->index == temp->index) {
						link->succ->coef += temp->coef;
						if (link->succ->coef == 0) {		//若二者相加系数为0，则删去
							ListNodePosi temp = link->succ;
							link->succ = temp->succ;
							delete temp;
						}
						break;
					}
					else if (link->succ->index > temp->index)
						link = link->succ;
					else {
						temp->succ = link->succ;
						link->succ = temp;
						break;
					}
				}
				temp2 = temp2->succ;
			}
			temp1 = temp1->succ;
		}
	}
	void print() {
		if (L1_mul_L2->succ == nullptr)
			printf("0 0\n");
		else {
			ListNodePosi temp = L1_mul_L2->succ;
			while (temp) {
				printf("%d %d", temp->coef, temp->index);
				if (temp->succ != nullptr)
					printf(" ");
				temp = temp->succ;
			}
			printf("\n");
		}

		if (L1_add_L2->succ == nullptr)
			printf("0 0\n");
		else {
			ListNodePosi temp = L1_add_L2->succ;
			while (temp) {
				printf("%d %d", temp->coef, temp->index);
				if (temp->succ != nullptr)
					printf(" ");
				temp = temp->succ;
			}
			printf("\n");
		}
	}
};

int main()
{
	Unpoly poly;
	poly.input_L1();
	poly.input_L2();
	poly.add();
	poly.mul();
	poly.print();
	return 0;
}