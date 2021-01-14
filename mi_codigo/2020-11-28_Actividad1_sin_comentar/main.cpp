#include <iostream>
#include <vector>

using namespace std;

struct box{
    float v;
    box *sgt;
    box *ant;
};
// Bien Diego, tu estrategia es usar un nodo que sea bidirectional. Eso facilita las operaciones pero ocupa más memoria ya que reserva 2X que una LL simple

box *head=NULL, *final=NULL,*i=NULL, *temp, *a, *b;  //Creamos el head y el auxiliar

//Declaramos los métodos
void mostrar();
void addFirst(float x);
void addBefore(float x);
void addAfter(float x);
void addInPosition(int pos, float x);
void calcularMayor();
void suma();
void checkOrden();
void borrar(box *a);
void borrarRecursivo(int valor, box *b);
void borrarIterativo(int valor);
void push(box *temp);
void rellenar(box *temp);
void pop();
void printStack();
void invertirStack();
void intercambiarBox(int p, int p2);
void esperar();


//MOSTRAR LOS DATOS
void mostrar(){
    if (head==NULL){
        cout << " --> Lista vacia, nada que imprimir"<<endl;
    }
    else{
        cout << "La lista contiene los siguientes elementos:" <<endl;
        cout << "HEAD: " << head->v <<endl;
        cout <<"FINAL: " << final->v <<endl;
        box *a=head;

        do{
            cout << a->v;
            if (a->sgt!=head && a->sgt!=NULL){
                cout << " -> ";
            }

            if(a->sgt!=NULL){
                a=a->sgt;
            }

        }while(a!=head);    //Imprimimos el contenido de la ll HASTA llegar de nuevo al head. No se muestra de esa forma el contenido en búcle.
    }
}
//AÑADIR ANTES Y DESPUÉS EN LA LISTA
void addFirst(float x){   //Dado que para añadir antes o después, el primero es igual, reutilizamos el código.
    box *a=new box;
    a->v=x;
    a->sgt=NULL;    //El siguiente y anterior son nulos al ser el único elemento en la lista
    a->ant=NULL;
    head=a;         //El head y el final apuntan al mismso box
    final=a;
}

void addAfter(float x){  //Añadir un box, al final de la lista
    if(head==NULL){ //Si el head apunta a null, es que la lista está vacía. Añadimos el primero
        addFirst(x);
    }

    else{   //Si hay dos o más box en la lista
        box *a=new box;
        a->v=x;
        a->sgt=head;    //Actualizamos el siguiente del nuevo box
        a->ant=final;   //Actualizamos el anterior del nuevo box
        a->ant->sgt=a;  //Actualizamos el siguiente del box ANTERIOR
        head->ant=a;    //Actualizamos el anterior del box siguiente
        final=a;        //El final ahora es el nuevo box

    }
}

void addBefore(float x){   //Añadir un box al inicio de la lista
    if(head==NULL){
        addFirst(x);
    }
    else{
        box *a=new box;
        a->v=x;
        a->sgt=head;    //Introdcimos el siguiente del nuevo box
        a->ant=final;   //Introducimos el anterior del nuevo box
        a->ant->sgt=a;  //Actualizamos el siguiente del box ANTERIOR
        a->sgt->ant=a;  //Actualizamos el anterior del box siguiente
        head=a;         //El head ahora es el nuevo box

    }
}

//AÑADIR EN UNA APOSICIÓN DETERMINADA DE LA LISTA
void addInPosition(int pos, float x) {

    if(head==NULL || head->sgt==NULL ){    //Controlamos que al menos ha de haber DOS elementos en nuestra lista ya que sino no tiene sentido.
        cout << ">No hay suficientes posiciones elementos en la lista como para llevar a cabo esta accion";
    }
    else{
        box *a = head;
        cout<<">Buscando la posicion"<<endl;

        if(pos!=1){
            for (int i=1; i<pos; i++) {
                if(a==final){
                    cout<< ">La operacion no puede realizarse para la posicion seleccionada"<<endl;
                    pos=-1; //Reutilizamos la memoria de esta variable para indicar que la operación no puede realizarse, por lo que a continuación no se realizarán cambios ni añadirán punteros
                }
                else{
                    a=a->sgt;   //Nos colocamos sobre el espacio que deseamos ocupar
                }

            }
        }
        cout<<">Posicion encontrada, tratando de colocar"<<endl;
        if(a==head){
            addBefore(x);

        }
        else if (a==final){
            addAfter(x);
        }
        else{
            box *a2=new box;
            a2->v=x;
            a2->sgt=a;
            a2->ant=a->ant;
            a2->ant->sgt=a2;
            a->ant=a2;
            cout<<">Nuevo elemento colocado"<<endl;
        }
    }
}

//CALCULAR EL ELEMENTO MAYOR Y CUANTAS VECES ESTE SE REPITE
void calcularMayor(){
    if(head!=NULL){
        box *a=head;
        float mayor;
        int repite=1;
        do{
            if(a->v>mayor){
                mayor=a->v;
                repite=1;
            }
            else if(a->v==mayor){
                repite++;
            }
            a=a->sgt;
        }while(a->sgt!=NULL && a!= head);
        cout << ">El mayor es: " << mayor <<endl <<">Se repite " <<repite <<" veces" <<endl;
    }
    else{
        cout<<" ---> La lista no ha sido rellenada por lo que no existe un valor MAYOR "<<endl;
    }
}

//SUMAR TODOS LOS ELEMENTOS DE LA LISTA
void suma(){
    box *a=head;
    float suma;
    do{
        suma=suma+a->v;
        a=a->sgt;
    }while(a!=head);
    cout << ">La suma de todos los elementos es: " <<suma;
}

//COMPROBAMOS EL ORDEN DE LOS ELEMENTOS DE LA LISTA
void checkOrden(){
    box *a=head;
    while(a->v <= a->sgt->v && a!=final){
        a=a->sgt;
    }
    if(a==final){cout<<" --> La lista esta ordenada"<<endl;}    //Si a = final, es que se ha cumplido la condición y la lista está ordenada
    else{cout<<" --> La lista NO esta ordenada"<<endl;}
}


//ELIMINAR TODAS LAS OCURRENCIAS DE UN ELEMENTO DE LA LISTA
void borrar(box *a){
    cout<<">Borrando elemento con valor: " << a->v<<endl;
    if(head==final){
        head=NULL;
        final=NULL;
    }
    else if(a==head) {
        head = head->sgt;
        head->ant = final;
        final->sgt = head;
    }
    else if(a==final){
        final=final->ant;
        final->sgt=head;
        head->ant=final;
    }
    else{
        a->ant->sgt=a->sgt;
        a->sgt->ant=a->ant;
    }
    cout<<">Elemento borrado"<<endl;
}
//BORRAR DE FORMA RECURSIVA
void borrarRecursivo(int valor, box *b){
    if(b->v==valor && head!=final){
        borrar(b);
        b=b->sgt;
        borrarRecursivo(valor,b);
    }
    else if(b->v==valor && head==final){    //De querer borrar el último elemento de la lista dejamos de llamar a la función
        borrar(b);
    }
    else if(b!=final){
        b=b->sgt;
        borrarRecursivo(valor,b);
    }
    //De haber llegado al final de la lista, dejamos de llamar a la función
}

//BORRAR DE FORMA ITERATIVA
void borrarIterativo(int valor){
    box *a=head;
    bool finalAlcanzado=false;
    bool ultimaInteraccion=false;
    while(ultimaInteraccion || a!=NULL && !finalAlcanzado){

        if(a->v==valor){
            borrar(a);
            cout<<">Borrando nodo con un "<<a->v<<endl;
        }
        a=a->sgt;
        if(head==final){
            ultimaInteraccion=false;
            finalAlcanzado=true;
        }
        else if(a==final){
            finalAlcanzado=true;
            ultimaInteraccion=true;
        }
        else{
            ultimaInteraccion=false;
        }
    }
    cout<<">No hay mas elementos que borrar"<<endl;
    mostrar(); //Una vez eliminado el nodo, mostramos la lista

}

//INVERTIR LISTA CON UNA PILA
void push(box *temp){
    cout << ">Hacemos push de "<< temp->v <<endl;
    if(i==NULL){
        //Rellenamos el primer espacio de la pila
        temp->sgt=NULL;
        temp->ant=NULL;//NO NECESARIO
        i=temp;
    }
    else{
        //rellenamos la cola
        temp->sgt=i;
        temp->ant=NULL;//NO NECESARIO
        i=temp;
    }
}
void rellenar(box *temp){
    if(head==NULL){
        head=temp;
        final=temp;
        temp->sgt=NULL;
        temp->ant=NULL;
    }
    else{
        final->sgt=temp;
        temp->ant=final;
        temp->sgt=head;
        head->ant=temp;
        final=temp;
    }
    cout << ">Hemos restaurado un"<< temp->v<<endl;
}

void pop(){
    if(i!=NULL){
        i=i->sgt;
    }
    else{
        cout << "No se puede hacer pop"<<endl;
    }
}

void printStack(){
    cout<<"\nEl contenido de la pila es el siguiente:"<<endl;
    cout <<"Head: "<<i->v<<endl;
    box *a=i;
    while (a!=NULL){
        cout<<a->v <<" -> ";
        a=a->sgt;
    }
    cout <<"\n"<<endl;
}

void invertirStack(){
    do{
        box *temp=new box;
        //Hacemos una copia del head en el temporal
        temp->v=head->v;
        temp->sgt=head->sgt;
        temp->ant=head->ant;//NO NECESARIO

        if(head==final){
            cout <<">Ultimo elemento de la lista borrado"<<endl;
            head=NULL;
            final=NULL;
        }
        else{
            //Desconectamos el head de la lista
            head->ant->sgt=head->sgt;
            head->sgt->ant=head->ant;
            head=head->sgt;
        }


        //Hacemos un push del temp, que es una copia del head
        push(temp);
    }while(head!=NULL);
    cout << "\n>Hemos pasado el contenido de la lista a la pila"<<endl;
    printStack();

    //Ahora volvemos a rellenar
    while(i!=NULL){
        box *temp=new box;
        temp->v=i->v;
        temp->sgt=i->sgt;
        temp->ant=i->ant;

        rellenar(temp);
        pop();
    }
    cout<<">Hemos restaurado los elementos de la pila a la lista"<<endl;
}


//INTERCAMBIAR NODOS
void intercambiarBox(int p, int p2){
    //Recorremos con un auxiliar hasta la posición del primer box
    box *a=head;
    for(int i=1; i<p;i++){
        a=a->sgt;
    }

    //Recorremos con un nuevo auxiliar la lista hasta llegar al segundo box
    box *b=head;
    for(int i=1; i<p2;i++){
        b=b->sgt;
    }

    cout << "Se intercambian los siguientes nodos:" <<endl;
    cout << "Posicion de a" << p << " --> " << a->v <<endl;
    cout << "Posicion de b" << p2 << " --> " << b->v <<endl;

    if(a!=b){   //Si se quisiera intercambiar el mismo nodo no habría que hacer ninguna operación.

        //Almacenamos uno de los valores en el temporal  y los intercambiamos
        box *temp=new box;
        //temp->v=a->v;
        temp->sgt=a->sgt;
        temp->ant=a->ant;

        a->ant->sgt=b;
        b->ant->sgt=a;

        if(p2==p+1){ //En caso de que los nodos estén juntos
            cout <<"NODOS JUNTOS"<<endl;
            a->sgt=b->sgt;
            b->sgt=a;
        }
        else{    //En caso de que los nodos no estén juntos
            //Funciona bien
            cout <<"NODOS SEPARADOS"<<endl;
            a->sgt=b->sgt;
            b->sgt=temp->sgt;
        }

        a->ant=b->ant;
        b->ant=temp->ant;

        a->sgt->ant=a;
        b->sgt->ant=b;

        if(a==head){
            head=b;
        }
        else if(b==final){
            final=a;
        }
    }
    cout << " --> Nodos intercambiados con exito" <<endl;
}


//ESPERAR UNA ACCIÓN DESPUES DE CADA RESPUESTA
void esperar(){
    char aux;
    cout << "\n\nPulse una tecla para volver al menu..."<<endl;
    cin >> aux;
}

int main() {
    int op, p, p2;   //op - opción del menú  | p & p2 - posición
    float v;     // v - dato a almacenar
    cout <<"Diego Martin Campos ------ UNIVERSIDAD EUROPEA DE MADRID ------ ESCUALA DE ARQUITECTURA, INGENIERIA Y DISENO"<< endl;
    do{
        cout <<"--------------------------------------------------------"<< endl;
        cout <<"Menu"<< endl;
        cout <<"--------------------------------------------------------"<< endl;
        cout <<"< 1 >  MOSTRAR LISTA "<< endl;
        cout <<"< 2 >  INSERTAR AL INICIO DE LA LISTA "<< endl;
        cout <<"< 3 >  INSERTAR AL FINAL DE LA LISTA "<< endl;
        cout <<"< 4 >  INSERTAR UN ELEMENTO EN UNA POSICION DETERMINADA "<< endl;
        cout <<"< 5 >  CALCULAR EL MAYOR ELEMENTO Y CUANTAS VECES SE REPITE "<< endl;
        cout <<"< 6 >  SUMA DE TODOS LOS DATOS DE LA LISTA "<< endl;
        cout <<"< 7 >  COMPROBAR SI LA LISTA ESTA ORDENADA "<< endl;
        cout <<"< 8 >  BORRAR TODAS LAS OCURRENCIAS DE UN ELEMENTO "<< endl;
        cout <<"< 9 >  INVERTIR LA LISTA "<< endl;
        cout <<"< 10 > INTERCAMBIAR DOS NODOS DADOS EN UNA LISTA "<< endl;
        cout <<"< 0 >  SALIR " << endl;
        cout << "Introduzca su opcion (0 - 10)"<< endl;
        cin >> op;
        cout << "\n";

        switch (op){
            case 1:
                mostrar();
                break;

            case 2:
                cout <<"Inserte el dato que desea introducir al inicio de la lista\n"<<endl;
                cin >> v;
                cout << "\n";
                addBefore(v);
                break;

            case 3:
                cout <<"Inserte el dato que desea introducir al final de la lista\n"<<endl;
                cin >> v;
                cout << "\n";
                addAfter(v);
                break;

            case 4:
                cout <<"Inserte la posicion en la que se desea insertar"<<endl;
                cin >> p;
                cout << "\n";
                cout <<"Inserte el dato a almacenar"<<endl;
                cin >> v;
                cout << "\n";
                addInPosition(p,v);
                break;

            case 5:
                cout << "Se va a calcular el mayor elemento guardado:\n " <<endl;
                calcularMayor();
                break;

            case 6:
                cout << "Se van a sumar todos los elementos: \n " <<endl;
                suma();
                break;

            case 7:
                cout << "Comprobando si la lista esta ordenada:\n"<<endl;
                checkOrden();
                break;

            case 8:
                cout << "Borrar todas las ocurrencias de un valor:\n"<<endl;
                cout << "Introduzca el valor que se desea eliminar:\n"<<endl;
                cin >> v; //Reutilizamos la variable v para recoger el valor

                cout<<"<1>Borrar de forma recursiva"<<endl<<"<2>Borrar de forma iterativa"<<endl;
                cin>>op;
                if(op==1){
                    cout<<">Borrando de forma recursiva"<<endl;
                    box *a=head;
                    borrarRecursivo(v,a);
                }
                else if(op==2){
                    cout<<">Borrando de forma iterativa"<<endl;
                    borrarIterativo(v);
                }
                else{
                    cout<<">Dato no correcto"<<endl;
                }

                break;

            case 9:
                cout << "Invirtiendo lista: \n"<<endl;
                invertirStack();
                break;

            case 10:
                cout << "Introduzca la posicion del primer nodo: "<<endl;
                cin >> p;
                cout << "Introduzca la posicion del segundo nodo: " <<endl;
                cin >> p2;
                intercambiarBox(p,p2);
                break;

            case 0:
                op=0;
                cout << " ---> Saliendo...";
                break;

            default:
                cout << " ---> Valor introducido no válido";
        }
        esperar();
    } while (op!=0);

    return 0;
}
// revisión finalizada