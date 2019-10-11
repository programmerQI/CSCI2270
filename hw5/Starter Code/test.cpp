#include <iostream>
void fun(int* a)
{
    *a = 5;
}
void fun(int &a)
{
    a = 1;
}
int main()
{
    int a = 5;
    fun(a);
    std::cout << a << std::endl;
    return 0;
}
