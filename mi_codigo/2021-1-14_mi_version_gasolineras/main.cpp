#include <iostream>
#include <fstream>
using namespace std;

//Estructura que almacena en memória dinámica el contenido de cada una de las líneas del CSV
struct nodo{
    string provincia;
    string municipio;
    string localidad;
    int codigoPostal;
    string direccion;
    string margen;
    float longitud;
    float latitud;
    float precio95E5;
    float precio95E10;
    float precio95E5Premium;
    float precio98E5;
    float precio98E10;
    float precioGaseleoA;
    float precioGasoleoPremium;
    float precioGasoleoB;
    float precioGasoleoC;
    float precioBioetanol;
    float bioalcohol;
    float precioBiodiesel;
    float estermetilico;
    float precioGasesLicuados;
    float precioGasNaturalComprimido;
    float precioGasNaturalLicuado;
    float precioHidrogeno;
    string rotulo;
    string tipoVenta;
    string rem; //Creo que esto es el tipo de distribuidor
    string horario;
    string tipoServicio;

    nodo *sgt=NULL;
};
nodo *head=NULL, *final=NULL;   //Declaramos el head, final y

//Dejamos este espacio para declarar las funciones
void add(nodo *a);

//Declaramos las funciones a continuación:

//Le pasamos el nodo que queremos añadir a la lista
void add(nodo *a){
    if(head==NULL && final==NULL){  //Si la lista está vacía
        head=a;
        final=a;
    }
    else{   //Si la lista contiene al menos un elemento
        final->sgt=a;
        final=a;
    }
}

void eQ(nodo *actual){
    if(final==NULL){
        actual->sgt=NULL;
        final=actual;
        head=actual;
    }else{
        final->sgt=actual;
        actual->sgt=NULL;
        final=actual;
    }
    //cout<<actual->precio95E5<<endl;
}
void readFile(){
    ifstream read("../hoja_modificada_UK.tsv");
    try{
        while(!read.eof()){
            nodo *actual= new nodo();
            read >>actual->provincia>>actual->municipio>> actual->localidad>> actual->codigoPostal>> actual->direccion>> actual->margen>> actual->longitud>> actual->latitud>> actual->precio95E5>>
                 actual->precio95E10>> actual->precio95E5Premium>> actual->precio98E5>> actual->precio98E10>> actual->precioGaseleoA>> actual->precioGasoleoPremium>>
                 actual->precioGasoleoB>> actual->precioGasoleoC>> actual->precioBioetanol>> actual->bioalcohol>> actual->precioBiodiesel>> actual->estermetilico>>
                 actual->precioGasesLicuados>> actual->precioGasNaturalComprimido>> actual->precioGasNaturalLicuado>> actual->precioHidrogeno>> actual->rotulo>>
                 actual->tipoVenta>> actual->rem>> actual->horario>> actual->tipoServicio;
            eQ(actual);
        }
    }catch(...){
        read.close();
        cout<<"El archivo no se ha podido leer."<<endl;
    }
}

void showQueue(){
    nodo *aux=new nodo();
    aux=head;
    while(aux!=final){
        cout<<aux->municipio<<endl;
        aux=aux->sgt;
    }
    cout<<"Lista mostrada"<<endl;
}
void verGasolinerasOrdenadas(){

}
int main() {
    readFile();
    //showQueue();
    string provinciaPedida;
    string municipioPedido;
    string localidadPedida;
    int tipoGasolina;
    int op;
        cout << "-------------------------------------------------" << endl;
        cout << "      Bienvenido al buscador de gasolineras" << endl;
        cout << "-------------------------------------------------" << endl;
            cout << "Ingrese la provincia: " << endl;
            cin >> provinciaPedida;
            cout << "Ingrese el municipio: " << endl;
            cin >> municipioPedido;
            cout << "Ingrese la localidad: " << endl;
            cin >> localidadPedida;
            cout << "Que tipo gasolina necesita?" << endl;
            cout << " Tipos gasolina:  " << endl;
            cout << " 1/ Gasolina 95 E5" << endl;
            cout << " 2/ Gasolina 95 E10" << endl;
            cout << " 3/ Gasolina 95 E5 Premium" << endl;
            cout << " 4/ Gasolina 98 E5" << endl;
            cout << " 5/ Gasolina 98 E10" << endl;
            cout << " 6/ Gasoleo A" << endl;
            cout << " 7/ Gasoleo Premium" << endl;
            cout << " 8/ Gasoleo B" << endl;
            cin >> tipoGasolina;

        //Creamos los nodos necesarios
        nodo *aux=new nodo();
        nodo *g1=NULL, *g2=NULL, *g3=NULL, *g4=NULL, *g5=NULL;   //Las 5 gasolineras más baratas
        aux=head;

        //Buscamos la más barata
        while(aux!=final){
            cout<<"-";
                if(aux->provincia==provinciaPedida && aux->municipio==municipioPedido && aux->localidad==localidadPedida){
                    switch (tipoGasolina) {
                        case 1:
                                    cout<<"+";
                                    if (g1 == NULL &&
                                        aux->precio95E5 != 0) {  //Si no hay ningun nodo en la segunda lista se añade
                                        g1 = aux;
                                        cout << "Anade el primero" << endl;
                                        cout << g1->precio95E5 << endl;
                                    } else if (aux->precio95E5 < g1->precio95E5 &&
                                               aux->precio95E5 != 0) {   //Si es menor se sobreescribe
                                        g1 = aux;
                                        cout << "Sobreescribe el primero" << endl;
                                        cout << g1->precio95E5 << endl;
                                    }
                            break;
                        case 2:

                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                        case 6:
                            break;
                        case 7:
                            break;
                        case 8:
                            break;

                    }
                }
        aux=aux->sgt;
        }

        //Buscamos la segunda más barata
        aux=head;
    while(aux!=final){
        cout<<"-";
        if(aux->provincia==provinciaPedida && aux->municipio==municipioPedido && aux->localidad==localidadPedida){
            switch (tipoGasolina) {
                case 1:
                    cout<<"+";
                    if(g2==NULL)cout<<"?";
                    if (g2 == NULL && aux->precio95E5 != 0 && aux->precio95E5>g1->precio95E5) {  //Si no hay ningun nodo en la segunda lista se añade
                        g2 = aux;
                        cout << "Anade el primero" << endl;
                        cout << g1->precio95E5 << endl;
                    } else if (aux->precio95E5 < g2->precio95E5 && aux->precio95E5>g1->precio95E5 &&
                               aux->precio95E5 != 0) {   //Si es menor se sobreescribe
                        g2 = aux;
                        cout << "Sobreescribe el primero" << endl;
                        cout << g1->precio95E5 << endl;
                    }
                    break;
                case 2:

                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;

            }
        }
        aux=aux->sgt;
    }


    cout<<endl<<"1 -> "<<g1->precio95E5<<endl;
    cout<<endl<<"2 -> "<<g2->precio95E5<<endl;
        //Buscamos la segunda más barata

    }