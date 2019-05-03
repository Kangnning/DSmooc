#include<cstdio>
#define num 51

void Count(int Bucket[], int Judge[], int Size)
{
    int tmp;
    for(int i=0;i<Size;i++)
    {
        scanf("%d", &tmp);
        if(!Judge[tmp])
            Judge[tmp] = 1;
        Bucket[tmp]++;
    }
}

void Print(int Bucket[], int Judge[])
{
    int i;
    for(i=0;i<num;i++)
        if(Judge[i])
            printf("%d:%d\n", i, Bucket[i]);
}

int main()
{
    int n, Bucket[num], Judge[num];
    scanf("%d", &n);
    for(int i=0;i<51;i++)
        Bucket[i] = Judge[i] = 0;

    Count(Bucket, Judge, n);
    Print(Bucket, Judge);

    return 0;
}
