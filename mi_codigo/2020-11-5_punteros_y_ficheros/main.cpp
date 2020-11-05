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

void leerFichero(){
    string Fecha;
    string Hora;
    string Email;
    string Nombre;
    string Apellidos;
    bool Repite;
    int Exp;
    string Git;
    int Nivel;
    bool Exponer;
    bool Act1;
    int Mes;
    int Ano;
    int Hyflex;

    ifstream fin("../encuesta.tsv"); //Llamamos "fin" a la variable fichero de entrada
    fin >> Fecha; //Leemos el primer valor, el nombre
    try{ // Declaro inicio del bloque que pudiese generar alguna excepcion
        while(!fin.eof()){ //Mientras no hayamos terminado de recorrer el fichero
            fin >> Hora >> Email >>Nombre >> Apellidos >> Repite >> Exp >> Git >> Nivel >> Exponer >> Act1 >> Mes >> Ano >> Hyflex;
            cout << Fecha << Hora << Email << Nombre << Apellidos << Repite << Exp << Git << Nivel << Exponer << Act1 << Mes << Ano << Hyflex << endl;

            //Creamos un nodo auxiliar, y lo rellenamos con lo extraído del fichero, nodo por nodo, de forma iterativa.
                nodo *aux = new nodo;
                aux->fecha=Fecha;
                aux->hora=Hora;
                aux->email=Email;
                aux->nombre=Nombre;
                aux->apellidos=Apellidos;
                aux->repite=Repite;
                aux->exp=Exp;
                aux->git=Git;
                aux->nivel=Nivel;
                aux->exponer=Exponer;
                aux->act1=Act1;
                aux->mes=Mes;
                aux->ano=Ano;
                aux->hyflex=Hyflex;

                if(head==NULL&&final==NULL){
                    head=aux;
                    final=aux;
                    aux->sgt=NULL;
                }
                else{
                    aux->sgt=head;
                    head=aux;
                }


            fin>>Nombre;//Leemos para saber si estamos en fin de archivo
        }
    }
        //Cerramos archivos de texto y binarios
    catch(...){//Captura todas las excepciones posibles para no romper el program de forma descontrolada.
        fin.close();
        cout<< ">Error al leer el archivo"<<endl;
    }
    cout << ">El fichero se ha leido con exito"<<endl;

}


int main() {
leerFichero();

cout<<">Main finalizado"<<endl;
}

