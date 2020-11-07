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

int recogerMes();
int recogerAno();
void leerFichero();
int * recogerHora();
void leerFichero();
int menu();
void masEdad(int mes, int ano, nodo *head);
void cumple(int mes, nodo *head);
void expImpar(nodo *head);
void expPar(nodo *head);
void entrega(nodo *head);
void presencialidad(nodo *head);


void presencialidad(nodo *head);

int recogerMes(){
    time_t t = time(NULL);
    struct tm *tlocal = localtime(&t);
    int mes=tlocal->tm_mon+1;
    return mes;
}
int recogerAno(){
    time_t t = time(NULL);
    struct tm *tlocal = localtime(&t);
    int ano=tlocal->tm_year+1900;
    return ano;
}

void leerFichero(){

    ifstream fin("../encuesta.tsv"); //Llamamos "fin" a la variable fichero de entrada
    try{ // Declaro inicio del bloque que pudiese generar alguna excepcion
        while(!fin.eof()){ //Mientras no hayamos terminado de recorrer el fichero
            nodo *aux = new nodo; //Creamos un nodo auxiliar, y lo rellenamos con lo extraído del fichero, nodo por nodo, de forma iterativa.
            fin >> aux->fecha>> aux->hora >> aux->email >> aux->nombre >> aux->apellidos >> aux->repite >> aux->exp >> aux->git >> aux->nivel >>  aux->exponer >> aux->act1 >> aux->mes >> aux->ano >> aux->hyflex;
           // cout << aux->fecha << aux->hora << aux->email << aux->nombre << aux->apellidos << aux->repite << aux->exp << aux->git << aux->nivel << aux->exponer << aux->act1 << aux->mes << aux->ano << aux->hyflex << endl;

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
    cout << ">El fichero se ha importado como una linked list"<<endl;
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
    cout<<">Este mes "<<mes<<" es el cumpleanos de :"<<endl;
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
void entrega(nodo *head){
    nodo *aux=head;
    int entrega=0;  //Guardamos el número de alumnos que SI han entregado la actividad 1
    int nAlumnos=0; //Guardamos el número de alumnos sobre los que realizamos el estudio
    cout<<"Han entregado la actividad 1: "<<endl;
    do{
        if(!aux->act1){
            entrega++;
            cout << aux->nombre << " " << aux->apellidos <<endl;
        }
        aux=aux->sgt;
        nAlumnos++;
    }while(aux!=NULL);
    cout <<endl<<">Entregan "<<entrega<<endl;
    cout <<">Alumnos totales " <<nAlumnos<<endl;
    float porcentage = entrega/nAlumnos;
    cout<<">Han entregado la actividad un "<< entrega*100/nAlumnos <<"% de la clase"<<endl;
}

void presencialidad(nodo *head){
    nodo *aux=head;
    int hyflex=0, presencial=0;
    cout<<endl<<">Listado presencial:"<<endl;
    do{
        if(!aux->hyflex){
            presencial++;
            cout<<aux->nombre<<" "<<aux->apellidos<<endl;
        }
        aux=aux->sgt;
    }while(aux!=NULL);
    aux=head;
    cout<<endl<<">Listado hyflex:"<<endl;
    do{
        if(aux->hyflex){
            hyflex++;
            cout<<aux->nombre<<" "<<aux->apellidos<<endl;
        }
        aux=aux->sgt;
    }while(aux!=NULL);

    cout <<endl<< ">Total asistentes via presencial: " << presencial << endl;
    cout << ">Total asistentes via virtual: " << hyflex << endl;


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
                cout << "5. Porcentaje de alumnos que entregaron la act. 1  "<<endl<<endl;
                entrega(head);
                break;
            case 6:
                cout<<"6. Numero y listado de asistentes a clase Hyflex y presencial"<<endl;
                presencialidad(head);
                break;
            case 0:
                cout <<">Saliendo..."<<endl;
                break;
        }

        cout <<endl << ">Operacion  finalizada"<<endl;
    }
    cout<<">Programa finalizado"<<endl;

}





