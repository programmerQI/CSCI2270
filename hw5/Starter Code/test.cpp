#include <iostream>
int f(int x)
{
    return (x > 0) ? x*f(x - 1) : 2;
}
int main()
{
    int i = f(f(2));
    std::cout << i << std::endl;
}
