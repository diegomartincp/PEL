#include <iostream>
#include <fstream>
#include <time.h>
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
int * recogerHora();
void leerFichero();
int menu();
void masEdad(nodo *pNodo);

int recogerMes(){
    time_t t = time(NULL);
    struct tm *tlocal = localtime(&t);
    cout <<tlocal->tm_mon <<endl<<tlocal->tm_year<<endl;

    int mes=tlocal->tm_mon+1;
    return mes;
}
int recogerAno(){
    time_t t = time(NULL);
    struct tm *tlocal = localtime(&t);
    cout <<tlocal->tm_mon <<endl<<tlocal->tm_year<<endl;

    int ano=tlocal->tm_year+1900;
    return ano;
}

void leerFichero(){

    ifstream fin("../encuesta.tsv"); //Llamamos "fin" a la variable fichero de entrada
    try{ // Declaro inicio del bloque que pudiese generar alguna excepcion
        while(!fin.eof()){ //Mientras no hayamos terminado de recorrer el fichero
            nodo *aux = new nodo; //Creamos un nodo auxiliar, y lo rellenamos con lo extraído del fichero, nodo por nodo, de forma iterativa.
            fin >> aux->fecha>> aux->hora >> aux->email >> aux->nombre >> aux->apellidos >> aux->repite >> aux->exp >> aux->git >> aux->nivel >>  aux->exponer >> aux->act1 >> aux->mes >> aux->ano >> aux->hyflex;
            cout << aux->fecha << aux->hora << aux->email << aux->nombre << aux->apellidos << aux->repite << aux->exp << aux->git << aux->nivel << aux->exponer << aux->act1 << aux->mes << aux->ano << aux->hyflex << endl;

            if(head==NULL&&final==NULL){
                head=aux;
                final=aux;
                aux->sgt=NULL;
            }
            else{
                final->sgt=aux;
                final=aux;
            }
        }
    }
        //Cerramos archivos de texto
    catch(...){//Captura todas las excepciones posibles para no romper el program de forma descontrolada.
        fin.close();
        cout<< ">Error al leer el archivo"<<endl;
    }
    cout << ">El fichero se ha leido con exito"<<endl;
    if(head!=NULL)cout << "Todo OK"<<endl;
}

int menu(){
    int op;

    cout << "\n-------------------------------Menu-------------------------------"<<endl;
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
void masEdad(int mes, int ano, nodo *head) {
    nodo *aux = head;
    nodo *alumno = new nodo;
    int anoAlto=ano, mesAlto=mes;
    while(aux->sgt!=NULL){
        if(aux->ano<=anoAlto){
            anoAlto=aux->ano;
            cout << ">El ano mas bajo es : "<<aux->nombre<<" -> "<< anoAlto<<endl;
            alumno=aux;
            if(aux->mes<=mesAlto){
                mesAlto=aux->mes;
                cout << ">El mes mas bajo es: "<<aux->nombre<<" -> "<<mesAlto<<endl;
                alumno=aux;
            }
        }
        if(aux->sgt!=NULL)aux=aux->sgt;
    }
    cout << ">El mas mayor es: "<<alumno ->nombre << " " << alumno->apellidos<<endl;
}

void cumple(int mes, nodo *head){
    nodo *aux=head;
    cout<<">Este mes "<<mes<<" es el cumpleanos de :";
    do{
        if(aux->mes==mes){
            cout<< aux->nombre <<" "<<aux->apellidos<<endl;
        }
        aux=aux->sgt;
    }while(aux!=NULL);
}

void expImpar(nodo *head) {
    nodo *aux = head;
    cout << "Tienen expediente impar: " << endl;
    do {
    if (aux->exp % 2 != 0) {
        cout << aux->nombre << " " << aux->apellidos << " con expediente: " << aux->exp << endl;
    }
    aux=aux->sgt;
    }while(aux!=NULL);
}

void expPar(nodo *head){
    nodo *aux = head;
    cout << "Tienen expediente impar: " << endl;
    do {
        if (aux->exp % 2 == 0) {
            cout << aux->nombre << " " << aux->apellidos << " con expediente: " << aux->exp << endl;
        }
        aux=aux->sgt;
    }while(aux!=NULL);
}

int main() {
    cout << "ACTIVIDAD 2 - DIEGO MARTIN CAMPOS" <<endl;
    cout << "UNIVERSIDAD EUROPEA DE MADRID" <<endl;
    int mes=recogerMes();   //Recogemos el mes y año del sistema
    int ano=recogerAno();
    leerFichero();
    int op=1;
    while(op!=0) {
        op = menu();

        switch (op) {
            case 1:
                cout <<"1. Quien es el alumno mas viejo  "<<endl<<endl;
                masEdad(mes, ano, head);
                break;
            case 2:
                cout << "2. Cuantos alumnos cumplen anos este mes"<<endl<<endl;
                cumple(mes, head);
                break;
            case 3:
                cout << "3. Listado de alumnos con expediente impar "<<endl<<endl;
                expImpar(head);
                break;
            case 4:
                cout << "4. Listado de alumnos con expediente par  "<<endl<<endl;
                expPar(head);
                break;
            case 5:
                break;
            case 6:
                break;
            case 0:
                cout <<">Saliendo..."<<endl;
                break;
        }

        cout <<endl << ">Operacion  finalizada"<<endl;
    }
    cout<<">Programa finalizado"<<endl;

}





