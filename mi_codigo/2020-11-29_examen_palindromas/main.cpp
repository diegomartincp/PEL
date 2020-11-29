#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
struct nodo{
    char v;
    nodo *sgt=NULL;
    nodo *ant=NULL;
};
nodo *head=NULL, *final=NULL;

void add(char elemento_){
    nodo *a=new nodo;
    a->v=elemento_;

    if(head==NULL){
        head=a;
        final=a;
    }
    else{
        final->sgt=a;
        a->ant=final;
        final=a;
    }
    cout<<"Se ha anadido "<<elemento_<<endl;
}
void rellenarLista(){
    ifstream fin("../file.txt");
    string palabra;
    fin>>palabra;   //SOLO cogemos la primera palabra

    char elemento;
    for(int i=0;i<=palabra.length()-1;i++){ //Separamos la palabra en varios caracteres que son los que añadimos a la DLL
        elemento=palabra[i];
        add(elemento);
    }
    fin.close();
}
void imprimirLista(nodo *head_){
    nodo *a=head_;
    while(a!=NULL){
        cout<<a->v<<" ";
        a=a->sgt;
    }
    cout<<endl;
}
bool palindroma(nodo *head_, nodo *final_){ //Leemos la lista en ambos sentidos a la vez
    nodo *derecho = head_;
    nodo *reves = final_;

    while(derecho!=NULL){
        if(derecho->v==reves->v){
            //Vamos bien
            derecho=derecho->sgt;
            reves=reves->ant;
        }
        else {
            return false;
        }
    }
    return true;
}
int main() {
    rellenarLista();
    imprimirLista(head);
    if(palindroma(head,final)) cout<<"Es palindroma"<<endl;
    else cout<<"No es palindroma"<<endl;
    return 0;
}
