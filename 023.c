//全部测试通过
#include <stdio.h>
#include <stdlib.h>

struct node
{
	int address;
	int data;
	int nextadd;
	struct node *next;
};
typedef struct node *List;

List CreateList(int n)
{
	List link, list, addlist;
	list = (List)malloc(sizeof(struct node));
	link = list;

	while(n--)
	{
		addlist = (List)malloc(sizeof(struct node));
		scanf("%d %d %d", &addlist->address, &addlist->data, &addlist->nextadd);
		addlist->next = NULL;
		link->next = addlist;
		link = link->next;
	}
	addlist = NULL;
	link = list;
	list = list->next;
	free(link);
	free(addlist);

	return list;
}

List SortList(List orignlist, int address, int *cnt)
{
	List link;
	List SortedList, SortLink, AddSortList;
	SortedList = (List)malloc(sizeof(struct node));
	SortedList->next = NULL;
	SortLink = SortedList;

	while(address != -1)
	{
        link = orignlist;
        while(link)
        {
            if(link->address == address)
            {
                AddSortList = (List)malloc(sizeof(struct node));
                AddSortList->address = link->address;
                AddSortList->data = link->data;
                AddSortList->nextadd = link->nextadd;
                AddSortList->next = NULL;
                SortLink->next = AddSortList;
                link = link->next;
                SortLink = SortLink->next;
                (*cnt)++;
                address = SortLink->nextadd;
            }
            else
            {
                link = link->next;
            }
        }
	}

	link = orignlist;
	while(link)
    {
        orignlist = orignlist->next;
        free(link);
        link = orignlist;
    }

    link = SortedList;
    SortedList = SortedList->next;
    free(link);
	return SortedList;
}

List Reversr(List head, int k, int n)
{
    List New, old, tmp;
    int cnt = 1;
    New = head;
    old = New->next;
    while(cnt < k)
    {
        tmp = old->next;
        old->next = New;
        old->nextadd = New->address;
        New = old;
        old = tmp;
        cnt++;
    }
    head->next = old;
    if (old != NULL){
        head->nextadd = old->address;
    }else{
        head->nextadd = -1;
    }

    if(--n)
    {
        head->next = Reversr(head->next, k, n);
        head->nextadd = head->next->address;
    }

    return New;
}

int main()
{
	int Address, n, k;
	int *cnt;
	cnt = (int*)malloc(sizeof(int));
	*cnt = 0;
	List orignlist, tmp;
	orignlist = (List)malloc(sizeof(struct node));
	scanf("%d %d %d", &Address, &n, &k);

	orignlist = CreateList(n);
	orignlist = SortList(orignlist, Address, cnt);
	tmp = orignlist;
//	while(tmp)
//	{
//        printf("%05d %d %05d\n", tmp->address, tmp->data, tmp->nextadd);
//        tmp = tmp->next;
//	}
    if(k!=1)
        orignlist = Reversr(orignlist, k, *cnt/k);

	tmp = orignlist;
	while(tmp)
	{
	    if(tmp->nextadd != -1)
            printf("%05d %d %05d\n", tmp->address, tmp->data, tmp->nextadd);
        else
            printf("%05d %d -1\n", tmp->address, tmp->data);
		tmp = tmp->next;
	}

	free(cnt);
	tmp = orignlist;
	while(tmp)
    {
        orignlist = orignlist->next;
        free(tmp);
        tmp = orignlist;
    }

	return 0;
}
