#include <iostream>
#include <fstream>
using namespace std;


struct nodo{
    string v;
    nodo *sgt=NULL;
};
nodo *head=NULL;



void push(string var_){ //Hacemos push del nodo a la pila
    nodo *a=new nodo();
    a->v=var_;
    if(head==NULL){
        head=a;
    }
    else{
        a->sgt=head;
        head=a;
    }
}
void pop(){
    if(head!=NULL) head=head->sgt;
}

bool sacar(string elemento){
    if(head!= NULL){
        if(head->v==elemento){
            pop();
            cout<<"Correcto"<<endl;
            return true;

        }
        else{
            cout<<"El elemento no coincide"<<endl;
            return false;
        }
    }
    else{
        cout<<"No quedan elementos en la pila que eliminar"<<endl;
        return false; //Nos sobra entonces un elemento
    }

}

int main() {
        ifstream fin("../file.txt");
        string var;
        bool coincide=true;
        while(!fin.eof()&&coincide){
            fin>>var;
            if(var=="(" || var=="[" || var=="{" || var=="/*"){
                push(var);
            }
            else if(var==")"){
                if(sacar("(")){

                }
                else{
                    coincide=false;
                }
            }
            else if(var=="]"){
                if(sacar("[")){

                }
                else{
                    coincide=false;
                }
            }
            else if(var=="}"){
                if(sacar("{")){

                }
                else{
                    coincide=false;
                }
            }
            else if(var=="*/"){
                if(sacar("/*")){

                }
                else{
                    coincide=false;
                }
            }
            else{
                //Hay introducido algo raro
                coincide=false;
            }
        }
        if(head==NULL && coincide){
            cout<<"Los elementos SI coinciden"<<endl;
        }
        else{
            cout<<"Los elementos NO coinciden"<<endl;
        }
    return 0;
}
