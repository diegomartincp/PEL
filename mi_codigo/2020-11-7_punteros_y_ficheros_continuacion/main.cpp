#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

//Creamos la estructura de los nodos, que almacenan las respuestas de cada estudiante en la encuesta y se almacenan como una linked list
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

nodo *head=NULL, *final=NULL;   //Creamos el head y final de la lista
ofstream fout("../registro.txt");//Declaramos fout como variable de salida

//Declaramos las funciones
int recogerMes();
int recogerAno();
void leerFichero();
int menu();
void masEdad(int mes, int ano, nodo *head);
void cumple(int mes, nodo *head);
void expImpar(nodo *head);
void expPar(nodo *head);
void entrega(nodo *head);
void presencialidad(nodo *head);

//Recogemos el mes y año del sistema para realizar los cálculos
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

//Leemos el archivo generado por la encuesta y almacenamos las respuestas como una linked list
void leerFichero(){

    ifstream fin("../encuesta.tsv"); //Llamamos "fin" a la variable fichero de entrada
    try{
        while(!fin.eof()){ //Mientras no hayamos terminado de recorrer el fichero
            //Creamos un nodo auxiliar, y lo rellenamos con lo extraído del fichero, nodo por nodo, de forma iterativa.
            nodo *aux = new nodo;
            fin >> aux->fecha>> aux->hora >> aux->email >> aux->nombre >> aux->apellidos >> aux->repite >> aux->exp >> aux->git >> aux->nivel >>  aux->exponer >> aux->act1 >> aux->mes >> aux->ano >> aux->hyflex;
            //cout << aux->fecha << aux->hora << aux->email << aux->nombre << aux->apellidos << aux->repite << aux->exp << aux->git << aux->nivel << aux->exponer << aux->act1 << aux->mes << aux->ano << aux->hyflex << endl;

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

        cout<< ">Error al leer el archivo"<<endl;
        fout<< ">Error al leer el archivo"<<endl;   //Esto también lo guardamos en el registro
    }
    fin.close();
    cout << ">El fichero se ha importado como una linked list"<<endl;
    fout << ">El fichero se ha importado como una linked list"<<endl;   //Lo guardamos en el registro
}

//Mostramos el menú del programa
int menu(){
    int op;
    cout << "\n-------------------------------Menu-------------------------------"<<endl;
    cout << "| 1. Quien es el alumno mas viejo                                |"<<endl;
    cout << "| 2. Cuantos alumnos cumplen anos este mes                       |"<<endl;
    cout << "| 3. Listado de alumnos con expediente impar                     |"<<endl;
    cout << "| 4. Listado de alumnos con expediente par                       |"<<endl;
    cout << "| 5. Porcentaje de alumnos que entregaron la act. 1              |"<<endl;
    cout << "| 6. Numero y listado de asistentes a clase Hyflex y presencial  |"<<endl;
    cout << "| 0. Salir                                                       |"<<endl;
    cout << "------------------------------------------------------------------"<<endl;
    cin >> op;
    return op;
}
/*
 * calculamos quien es el estudiante más mayor, viendo primero quien es el que nació en un año menor y
 * posteriormente quien nació en ese mismo año, en un mes anteior
 */
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
    //Lo imprimimos por consola y guardamos en el fichero
    cout << ">El mas mayor es: "<<alumno ->nombre << " " << alumno->apellidos<<endl;
    fout << endl<<">El mas mayor es: "<<alumno ->nombre << " " << alumno->apellidos<<endl;
}

//Recorremos la lista para mostrar todos los estudiantes que cumplen años este mes
void cumple(int mes, nodo *head){
    nodo *aux=head;
    //Lo imprimimos por consola y guardamos en el fichero
    cout<<">Este mes "<<mes<<" es el cumpleanos de :"<<endl;
    fout <<endl<<">Este mes "<<mes<<" es el cumpleanos de :"<<endl;
    do{
        if(aux->mes==mes){
            cout<< aux->nombre <<" "<<aux->apellidos<<endl;
            fout<< aux->nombre <<" "<<aux->apellidos<<endl; //Lo guardamos en el fichero
        }
        aux=aux->sgt;
    }while(aux!=NULL);
}

//Recorremos la lista para mostrar los estudiantes con número de expediente impar
void expImpar(nodo *head) {
    nodo *aux = head;
    cout << "Tienen expediente impar: " << endl;
    fout <<endl<< "Tienen expediente impar: " << endl;  //Guardamos en el fichero
    do {
    if (aux->exp % 2 != 0) {
        cout << aux->nombre << " " << aux->apellidos << " con expediente: " << aux->exp << endl;
        fout << aux->nombre << " " << aux->apellidos << " con expediente: " << aux->exp << endl;  //Guardamos en el fichero
    }
    aux=aux->sgt;
    }while(aux!=NULL);
}

//Recorremos la lista para mostrar los estudiantes con número de expediente par
void expPar(nodo *head){
    nodo *aux = head;
    cout << "Tienen expediente par: " << endl;
    fout <<endl<< "Tienen expediente par: " << endl;  //Guardamos en el fichero
    do {
        if (aux->exp % 2 == 0) {
            cout << aux->nombre << " " << aux->apellidos << " con expediente: " << aux->exp << endl;
            fout << aux->nombre << " " << aux->apellidos << " con expediente: " << aux->exp << endl;  //Guardamos en fichero
        }
        aux=aux->sgt;
    }while(aux!=NULL);
}

//Recorremos la lista para mostrar quienes son los estudiantes que han entregado la actividad 1
void entrega(nodo *head){
    nodo *aux=head;
    int entrega=0;  //Guardamos el número de alumnos que SI han entregado la actividad 1
    int nAlumnos=0; //Guardamos el número de alumnos sobre los que realizamos el estudio
    cout<<">Listado de estudiantes que han entregado la actividad 1: "<<endl;
    fout<<endl<<">Listado de estudiantes que han entregado la actividad 1: "<<endl; //Guardamos en fichero
    do{
        if(!aux->act1){
            entrega++;
            cout << aux->nombre << " " << aux->apellidos <<endl;
            fout << aux->nombre << " " << aux->apellidos <<endl;
        }
        aux=aux->sgt;
        nAlumnos++;
    }while(aux!=NULL);
    cout <<endl<<">Han entregado la actividad "<<entrega<<endl;
    cout <<">Alumnos totales " <<nAlumnos<<endl;
    cout<<">Han entregado la actividad un "<< entrega*100/nAlumnos <<"% de la clase"<<endl;

    //Guardamos en el fichero
    fout <<endl<<">Han entregado la actividad "<<entrega<<endl;
    fout <<">Alumnos totales " <<nAlumnos<<endl;
    fout<<">Han entregado la actividad un "<< entrega*100/nAlumnos <<"% de la clase"<<endl;
}

//Mostramos los estudiantes que acudieron a clase de forma virtual y presencial, así como el número de estos.
void presencialidad(nodo *head){
    nodo *aux=head;
    int hyflex=0, presencial=0;
    cout<<endl<<">Listado presencial:"<<endl;
    fout<<endl<<">Listado presencial:"<<endl;
    do{
        if(!aux->hyflex){
            presencial++;
            cout<<aux->nombre<<" "<<aux->apellidos<<endl;
            fout<<aux->nombre<<" "<<aux->apellidos<<endl;

        }
        aux=aux->sgt;
    }while(aux!=NULL);
    aux=head;
    cout<<endl<<">Listado hyflex:"<<endl;
    fout<<endl<<">Listado hyflex:"<<endl;
    do{
        if(aux->hyflex){
            hyflex++;
            cout<<aux->nombre<<" "<<aux->apellidos<<endl;
            fout<<aux->nombre<<" "<<aux->apellidos<<endl;
        }
        aux=aux->sgt;
    }while(aux!=NULL);

    cout <<endl<< ">Total asistentes via presencial: " << presencial << endl;
    cout << ">Total asistentes via virtual: " << hyflex << endl;

    //Guardamos en el fichero
    fout <<endl<< ">Total asistentes via presencial: " << presencial << endl;
    fout << ">Total asistentes via virtual: " << hyflex << endl;
}

int main() {
    cout << "ACTIVIDAD 2 - DIEGO MARTIN CAMPOS" <<endl;
    cout << "UNIVERSIDAD EUROPEA DE MADRID" <<endl;

    //También lo guardamos en el fichero
    fout << "ACTIVIDAD 2 - DIEGO MARTIN CAMPOS" <<endl;
    fout << "UNIVERSIDAD EUROPEA DE MADRID" <<endl;


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
            default:
                cout<<">Valor introducido no valido";
                break;
        }
        cout <<endl << ">Operacion  finalizada"<<endl;
    }
    cout<<">Programa finalizado"<<endl;
    fout.close();
}





