#include <iostream>
using namespace std;

int factorialRecursivo(long valor){
    cout << valor<<endl;
    if(valor==1){
        cout<<"El valor es: "<<endl;
        return 1;
    }
    else{
        return valor*factorialRecursivo(valor-1);
    }
}


int main() {
    cout << "Introduce el numero del que quieres calcular el factorial"<<endl;
    long numero;
    cin >> numero;
    cout<<factorialRecursivo(numero);

    return 0;
}
