#include <iostream>


int main() {
   const char* x = "hi";
    x[0] = 'd';
    std::cout << x << std::endl;

    return 0;
}