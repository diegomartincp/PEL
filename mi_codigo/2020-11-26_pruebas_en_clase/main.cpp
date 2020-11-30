#include <iostream>
#include <fstream>

using namespace std;

void ficheri(){
    ifstream fin("../hola.txt");
    char hola;
    while(!fin.eof()){
        fin>>hola;
        cout<<hola<<endl;
    }
}

int main() {
    ficheri();
    std::cout <<1000u-100<<std::endl;

    int a[]={1,2,3,4,5,6};
    std::cout <<(1+3)[a] - a[0]+(a+1)[2];
    return 0;
}
