#include<iostream>
int* df(int *a)
{
    delete a;
    a = NULL;
    int *b = new int[1000];
    return b;
}
void opt(int **a)
{
    *a = df(*a);
    *a = df(*a);
}
int main()
{
    int *a = new int[1000];
    opt(&a);
    return 0;
}
