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
void menu();
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
    }
    fin.close();
    cout << ">El fichero se ha importado como una linked list"<<endl;
}

//Mostramos el menú del programa
void menu(){
    cout << "ACTIVIDAD 2 - DIEGO MARTIN CAMPOS" <<endl;
    cout << "UNIVERSIDAD EUROPEA DE MADRID" <<endl;

    //También lo guardamos en el fichero
    fout << "ACTIVIDAD 2 - DIEGO MARTIN CAMPOS" <<endl;
    fout << "UNIVERSIDAD EUROPEA DE MADRID" <<endl<<endl;

    cout << "\n----------------------------------------------------------------"<<endl;
    cout << "| EL PROGRAMA GUARDA EN FICHERO EL SIGUINTE CONTENIDO:           |"<<endl;
    cout << "| 1. Quien es el alumno mas viejo                                |"<<endl;
    cout << "| 2. Cuantos alumnos cumplen anos este mes                       |"<<endl;
    cout << "| 3. Listado de alumnos con expediente impar                     |"<<endl;
    cout << "| 4. Listado de alumnos con expediente par                       |"<<endl;
    cout << "| 5. Porcentaje de alumnos que entregaron la act. 1              |"<<endl;
    cout << "| 6. Numero y listado de asistentes a clase Hyflex y presencial  |"<<endl;
    cout << "------------------------------------------------------------------"<<endl;

}
/*
 * calculamos quien es el estudiante más mayor, viendo primero quien es el que nació en un año menor y
 * posteriormente quien nació en ese mismo año, en un mes anteior
 */
void masEdad(int mes, int ano, nodo *head) {
    cout <<"1. Quien es el alumno mas viejo  "<<endl;
    fout <<"1. Quien es el alumno mas viejo  "<<endl;

    nodo *aux = head;
    nodo *alumno = new nodo;
    int anoAlto=ano, mesAlto=mes;
    while(aux->sgt!=NULL){
        if(aux->ano<=anoAlto){
            anoAlto=aux->ano;
            alumno=aux;
            if(aux->mes<=mesAlto){
                mesAlto=aux->mes;
                alumno=aux;
            }
        }
        if(aux->sgt!=NULL)aux=aux->sgt;
    }
    //Lo imprimimos por consola y guardamos en el fichero
    cout << ">El mas mayor es: "<<alumno ->nombre << " " << alumno->apellidos<<endl<<endl;
    fout << ">El mas mayor es: "<<alumno ->nombre << " " << alumno->apellidos<<endl<<endl;
}

//Recorremos la lista para mostrar todos los estudiantes que cumplen años este mes
void cumple(int mes, nodo *head){
    cout << "2. Cuantos alumnos cumplen anos este mes"<<endl;
    fout << "2. Cuantos alumnos cumplen anos este mes"<<endl;
    int alumnos=0;
    nodo *aux=head;
    do{
        if(aux->mes==mes){
            alumnos++;
            cout<< aux->nombre <<" "<<aux->apellidos<<endl;
            fout<< aux->nombre <<" "<<aux->apellidos<<endl; //Lo guardamos en el fichero
        }
        aux=aux->sgt;
    }while(aux!=NULL);
    cout<<">Es el cumpleaños de "<<alumnos<<" alumnos"<<endl<<endl;
    fout<<">Es el cumpleaños de "<<alumnos<<" alumnos"<<endl<<endl;
}

//Recorremos la lista para mostrar los estudiantes con número de expediente impar
void expImpar(nodo *head) {
    cout << "3. Listado de alumnos con expediente impar "<<endl;
    fout << "3. Listado de alumnos con expediente impar "<<endl;

    nodo *aux = head;
    do {
        if (aux->exp % 2 != 0) {
            cout << aux->nombre << " " << aux->apellidos << " con expediente: " << aux->exp << endl;
            fout << aux->nombre << " " << aux->apellidos << " con expediente: " << aux->exp << endl;  //Guardamos en el fichero
        }
        aux=aux->sgt;
    }while(aux!=NULL);
    cout<<endl;
    fout<<endl;
}

//Recorremos la lista para mostrar los estudiantes con número de expediente par
void expPar(nodo *head){
    cout << "4. Listado de alumnos con expediente par  "<<endl;
    fout << "4. Listado de alumnos con expediente par  "<<endl;

    nodo *aux = head;
    do {
        if (aux->exp % 2 == 0) {
            cout << aux->nombre << " " << aux->apellidos << " con expediente: " << aux->exp << endl;
            fout << aux->nombre << " " << aux->apellidos << " con expediente: " << aux->exp << endl;  //Guardamos en fichero
        }
        aux=aux->sgt;
    }while(aux!=NULL);
    cout<<endl;
    fout<<endl;
}

//Recorremos la lista para mostrar quienes son los estudiantes que han entregado la actividad 1
void entrega(nodo *head){
    cout << "5. Porcentaje de alumnos que entregaron la act. 1  "<<endl;
    fout << "5. Porcentaje de alumnos que entregaron la act. 1  "<<endl;

    nodo *aux=head;
    int entrega=0;  //Guardamos el número de alumnos que SI han entregado la actividad 1
    int nAlumnos=0; //Guardamos el número de alumnos sobre los que realizamos el estudio
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
    cout<<">Han entregado la actividad un "<< entrega*100/nAlumnos <<"% de la clase"<<endl<<endl;

    //Guardamos en el fichero
    fout <<endl<<">Han entregado la actividad "<<entrega<<endl;
    fout <<">Alumnos totales " <<nAlumnos<<endl;
    fout<<">Han entregado la actividad un "<< entrega*100/nAlumnos <<"% de la clase"<<endl<<endl;
}

//Mostramos los estudiantes que acudieron a clase de forma virtual y presencial, así como el número de estos.
void presencialidad(nodo *head){
    cout<<"6. Numero y listado de asistentes a clase Hyflex y presencial"<<endl;
    fout<<"6. Numero y listado de asistentes a clase Hyflex y presencial"<<endl;

    nodo *aux=head;
    int hyflex=0, presencial=0;
    cout<<">Listado presencial:"<<endl;
    fout<<">Listado presencial:"<<endl;
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
    cout << ">Total asistentes via virtual: " << hyflex << endl<<endl;

    //Guardamos en el fichero
    fout <<endl<< ">Total asistentes via presencial: " << presencial << endl;
    fout << ">Total asistentes via virtual: " << hyflex << endl<<endl;
}

int main() {
    int mes=recogerMes();   //Recogemos el mes y año del sistema
    int ano=recogerAno();
    leerFichero();
    menu();
        //Guardamos el contenido en e fichero y lo mostramos por consola
        masEdad(mes, ano, head);
        cumple(mes, head);
        expImpar(head);
        expPar(head);
        entrega(head);
        presencialidad(head);
    cout<<">Programa finalizado"<<endl;
    fout.close();
}