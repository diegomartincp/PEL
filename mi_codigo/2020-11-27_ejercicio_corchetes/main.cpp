#include <iostream>
#include <fstream>
using namespace std;

struct nodo{
    string almacenar;
    nodo *sgt=NULL;
};
nodo *headList=NULL, *finalList=NULL, *headStack=NULL;



void addList(string simbolo){
nodo *a=new nodo();
a->almacenar=simbolo;
if(headList==NULL){ //Añadimos el primer elemento
    headList=a;
    finalList=a;
}
else{   //Añadimos al final
finalList->sgt=a;
finalList=a;
}
}

void push(nodo *b){
    nodo *a=new nodo();
    a->almacenar=b->almacenar; //Copiamos el contenido del nodo de la lista y ahora lo metemos en la pila
    if(headStack==NULL){
        headStack=a;
    }
    else{
        a->sgt=headStack;
        headStack=a;
    }
}

void hacerPushDeLista(nodo *head){
    nodo *a=head;
    while(a!=NULL){
        push(a);
        a=a->sgt;
    }
}
void mostrarStack(nodo *head){
    cout<<endl<<"EL CONTENIDO DE LA PILA ES EL SIGUIENTE: "<<endl;
    nodo *a=head;
    while(a!=NULL){
        cout << a->almacenar<<endl;
        a=a->sgt;
    }
}


void mostrarLista(nodo *head){
    cout<<"EL CONTENIDO DE LA LISTA ES EL SIGUIENTE: "<<endl;
nodo *a=head;
    while(a!=NULL){
        cout<<a->almacenar<<endl;
        a=a->sgt;
    }
}

bool comprobarOrden(nodo *headStack_, nodo *headList_){
    nodo *a=headStack_;
    nodo *b=headList_;
    cout<<endl<<"Comparamos la lista con la pila"<<endl;
    while(a!=NULL && b!=NULL){
        if(a->almacenar=="(" && b->almacenar==")" || a->almacenar==")" && b->almacenar=="("){
            cout<<a->almacenar<<" equivale con "<<b->almacenar<<endl;
            //Vamos bien
        }
        else if(a->almacenar=="[" && b->almacenar=="]" || a->almacenar=="]" && b->almacenar=="["){
            cout<<a->almacenar<<" equivale con "<<b->almacenar<<endl;
            //Vamos bien
        }
        else if(a->almacenar=="{" && b->almacenar=="}" || a->almacenar=="}" && b->almacenar=="{"){
            cout<<a->almacenar<<" equivale con "<<b->almacenar<<endl;
            //Vamos bien
        }
        else if(a->almacenar=="/*" && b->almacenar=="*/" || a->almacenar=="*/" && b->almacenar=="/*"){
            cout<<a->almacenar<<" equivale con "<<b->almacenar<<endl;
            //Vamos bien
        }
        else{
            cout<<a->almacenar<<" NO equivale con "<<b->almacenar<<endl;
            return false;
        }
        a=a->sgt;
        b=b->sgt;
    }

    return true;
}

void fileToList(){
    ifstream fin("../fichero.txt");
    string valor;
    while(!fin.eof()){
        fin>>valor;
        addList(valor);
    }
    fin.close();
}

int main() {
    /*
    string simbolo;
    while(simbolo!="0"){
        cout<< "Introduzca el simbolo o introduzca 0 si ha introducido todos" << endl;
        cin>>simbolo;
        if(simbolo!="0")addList(simbolo);
    }
    */

    fileToList();
    mostrarLista(headList);
    hacerPushDeLista(headList);
    mostrarStack(headStack);
    if(comprobarOrden(headStack,headList)) cout <<endl<<"->El orden es correcto";
    else{
        cout <<endl<<"->El orden NO es correcto";
    }
    return 0;
}
