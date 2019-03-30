BinTree Insert( BinTree BST, ElementType X )
{
    if(!BST)
    {
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }

    else if(BST->Data > X)
        BST->Left = Insert(BST->Left, X);
    else
        BST->Right = Insert(BST->Right, X);

    return BST;
}

Position Find( BinTree BST, ElementType X )
{
    BinTree Node = NULL;

    if(BST)
    {
        if(BST->Data < X)
            Node = Find(BST->Right, X);
        else if(BST->Data > X)
            Node = Find(BST->Left, X);
        else
            Node = BST;
    }
    else
        Node = NULL;

    return Node;
}

BinTree Delete(BinTree BST, ElementType X)
{
    BinTree Tmp;

    if(!BST)
        printf("Not Found\n");
    else {
        if(X < BST->Data)
            BST->Left = Delete(BST->Left, X);
        else if(X > BST->Data)
            BST->Right = Delete(BST->Right, X);
        else
        {
            if( BST->Left && BST->Right )           //如果被删除结点有左右两个子结点
            {
                Tmp = FindMin(BST->Right);
                BST->Data = Tmp->Data;
                BST->Right = Delete(BST->Right, BST->Data);
            }
            else                                    //被删除结点有一个或无子结点
            {
                Tmp = BST;
                if(!BST->Left)
                    BST = BST->Right;
                else
                    BST = BST->Left;
                free(Tmp);
            }
        }
    }
    return BST;
}

Position FindMin( BinTree BST )
{
    BinTree Node = BST;

    if(BST)
        while(Node->Left)
            Node = Node->Left;

    return Node;
}

Position FindMax( BinTree BST )
{
    BinTree Node = BST;

    if(BST)
        while(Node->Right)
            Node = Node->Right;

    return Node;
}