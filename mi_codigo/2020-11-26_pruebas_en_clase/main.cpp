#include <iostream>

int main() {
    std::cout <<1000u-100<<std::endl;

    int a[]={1,2,3,4,5,6};
    std::cout <<(1+3)[a] - a[0]+(a+1)[2];
    return 0;
}
