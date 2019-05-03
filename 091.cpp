#include<cstdio>
#include<cstdlib>
typedef int ElementType;

void Insertion_Sort(ElementType A[], int n)
{
    int i, P;
    ElementType Temp;

    if(n == 1)
    {
        return;
    }
    else
    {
         for (P=1;P<n;P++)
         {
             Temp = A[P];
             for (i=P;i>0 && A[i-1]>Temp;i--)
                A[i] = A[i-1];
             A[i] = Temp;
        }
    }
}

void Bubble_Sort(ElementType A[], int n)
{
    ElementType tmp;
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(A[i]>A[j])
            {
                tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
}

void Shell_Sort(ElementType A[], int n)
{
     int Si, D, P, i;
     ElementType Tmp;

     int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};

     for (Si=0;Sedgewick[Si]>=n;Si++)
         ;

     for (D=Sedgewick[Si];D>0;D=Sedgewick[++Si] )
         for (P=D;P<n;P++)
         {
             Tmp = A[P];
             for (i=P;i>=D && A[i-D]>Tmp;i-=D)
                 A[i] = A[i-D];
             A[i] = Tmp;
         }
}

void Swap( ElementType *a, ElementType *b )
{
     ElementType t = *a; *a = *b; *b = t;
}

void PercDown( ElementType A[], int p, int N )
{
    int Parent, Child;
    ElementType X;

    X = A[p];
    for( Parent=p; (Parent*2+1)<N; Parent=Child ) {
        Child = Parent * 2 + 1;
        if( (Child!=N-1) && (A[Child]<A[Child+1]) )
            Child++;
        if( X >= A[Child] ) break;
        else
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}

void Heap_Sort( ElementType A[], int N )
{
     int i;

     for (i=N/2-1;i>=0;i--)
        PercDown(A, i, N);

     for (i=N-1;i>0;i--)
     {
        Swap(&A[0], &A[i]);
        PercDown(A, 0, i);
     }
}

void Merge( ElementType A[], ElementType TmpA[], int L, int R, int RightEnd )
{
     int LeftEnd, NumElements, Tmp;
     int i;

     LeftEnd = R - 1;
     Tmp = L;
     NumElements = RightEnd - L + 1;

     while( L <= LeftEnd && R <= RightEnd ) {
         if ( A[L] <= A[R] )
             TmpA[Tmp++] = A[L++];
         else
             TmpA[Tmp++] = A[R++];
     }

     while( L <= LeftEnd )
         TmpA[Tmp++] = A[L++];
     while( R <= RightEnd )
         TmpA[Tmp++] = A[R++];

     for( i = 0; i < NumElements; i++, RightEnd -- )
         A[RightEnd] = TmpA[RightEnd];
}

void Merge_pass( ElementType A[], ElementType TmpA[], int N, int length )
{
     int i, j;

     for ( i=0; i <= N-2*length; i += 2*length )
         Merge( A, TmpA, i, i+length, i+2*length-1 );
     if ( i+length < N )
         Merge( A, TmpA, i, i+length, N-1);
     else
         for ( j = i; j < N; j++ ) TmpA[j] = A[j];
}

void Merge_Sort( ElementType A[], int N )
{
     int length;
     ElementType *TmpA;

     length = 1;
     TmpA = (ElementType*)malloc(N*sizeof(ElementType));
     if ( TmpA != NULL ) {
          while( length < N ) {
              Merge_pass( A, TmpA, N, length );
              length *= 2;
              Merge_pass( TmpA, A, N, length );
              length *= 2;
          }
          free( TmpA );
     }
     else printf( "空间不足" );
}

void Print(ElementType A[], int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d", A[i]);
        if(i<n-1)
            printf(" ");
    }
}

int main()
{
    int i, n;
    ElementType *A;
    scanf("%d", &n);
    A = (ElementType*)malloc(sizeof(ElementType)*n);

    for(i=0;i<n;i++)
        scanf("%d", &A[i]);

//    Insertion_Sort(A, n);
//    Print(A, n);
//    Bubble_Sort(A, n);
//    printf("\n");
//    Print(A, n);
//    Shell_Sort(A, n);
//    printf("\n");
//    Print(A, n);
//    Heap_Sort(A, n);
//    printf("\n");
//    Print(A, n);
    Merge_Sort(A, n);
//    printf("\n");
    Print(A, n);

    return 0;
}
