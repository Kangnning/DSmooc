List Merge(List L1, List L2)
{
	List p1, p2, p, head;
	p1 = L1->Next;              //带头结点的链表
	p2 = L2->Next;
	p = (List)malloc(sizeof(List));
	head = p;
    //合并p和p2
	while(p1 && p2)
	{
		if (p1->Data > p2->Data)
		{
			p->Next = p2;
			p2 = p2->Next;
			p = p->Next;
		}
		else
		{
			p->Next = p1;
			p1 = p1->Next;
			p = p->Next;
		}
	}

	if(p1)                  //若p1不为空，则将p1后续结点直接挂在后面
		p->Next = p1;
	if(p2)                  //p2同
		p->Next = p2;

	L1->Next = NULL;        //根据题目要求，L1，L2均需指向NULL
	L2->Next = NULL;

	return head;
}