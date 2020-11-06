#include <iostream>
#include <fstream>
using namespace std;

struct nodo{
    string fecha;
    string hora;
    string email;
    string nombre;
    string apellidos;
    bool repite;
    int exp;
    string git;
    int nivel;
    bool exponer;
    bool act1;
    int mes;
    int ano;
    int hyflex;

    nodo *sgt;
};

nodo *head=NULL, *final=NULL;

void leerFichero();
int menu();

void masEdad(nodo *pNodo);

void leerFichero(){
    nodo *aux = new nodo; //Creamos un nodo auxiliar, y lo rellenamos con lo extraído del fichero, nodo por nodo, de forma iterativa.
    ifstream fin("../encuesta.tsv"); //Llamamos "fin" a la variable fichero de entrada
    fin >> aux->fecha; //Leemos el primer valor, el nombre
    try{ // Declaro inicio del bloque que pudiese generar alguna excepcion
        while(!fin.eof()){ //Mientras no hayamos terminado de recorrer el fichero
            fin >> aux->hora >> aux->email >> aux->nombre >> aux->apellidos >> aux->repite >> aux->exp >> aux->git >> aux->nivel >>  aux->exponer >> aux->act1 >> aux->mes >> aux->ano >> aux->hyflex;
            cout << aux->fecha << aux->hora << aux->email << aux->nombre << aux->apellidos << aux->repite << aux->exp << aux->git << aux->nivel << aux->exponer << aux->act1 << aux->mes << aux->ano << aux->hyflex << endl;

                if(head==NULL&&final==NULL){
                    head=aux;
                    final=aux;
                    aux->sgt=NULL;
                }
                else{
                    aux->sgt=head;
                    head=aux;
                }
            fin>> aux->fecha;//Leemos para saber si estamos en fin de archivo
        }
    }
        //Cerramos archivos de texto
    catch(...){//Captura todas las excepciones posibles para no romper el program de forma descontrolada.
        fin.close();
        cout<< ">Error al leer el archivo"<<endl;
    }
    cout << ">El fichero se ha leido con exito"<<endl;
}

int menu(){
    int op;
    cout << "ACTIVIDAD 2 - DIEGO MARTIN CAMPOS" <<endl;
    cout << "UNIVERSIDAD EUROPEA DE MADRID" <<endl;
    cout << "-------------------------------Menu-------------------------------"<<endl;
    cout << "| 1. Quien es el alumno mas viejo                                |"<<endl;
    cout << "| 2. Cuantos alumnos cumplen anos este mes                       |"<<endl;
    cout << "| 3. Listado de alumnos con expediente impar                     |"<<endl;
    cout << "| 4. Listado de alumnos con expediente par                       |"<<endl;
    cout << "| 5. Porcentaje de alumnos que entregaron la act. 1              |"<<endl;
    cout << "| 6. Numero y listado de asistentes a clase Hyflex y presencial  |"<<endl;
    cout << "------------------------------------------------------------------"<<endl;
    cin >> op;
    return op;
}
void masEdad(nodo *head) {

}

int main() {
leerFichero();
int op;
while(op!=0) {
    op = menu();

    switch (op) {
        case 1:
            masEdad(head);
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
        case 0:
            cout <<">Saliendo..."<<endl;
            break;
    }
}
cout<<">Programa finalizado"<<endl;
}





