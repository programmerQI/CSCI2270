#include <iostream>
int main()
{
    int a[] = {1, 2, 3, 4, 5};
    for(int i = 0; i < 5; i ++){
      std::cout << *(a + i) << std::endl;
    }
    return 0;
}
