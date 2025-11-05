#include <iostream>
using namespace std;

//Nodos de arboles 
struct Nodo
{
    int dato;
    Nodo *der;
    Nodo *izq;
};

//Función para la creacion de un nodo nuevo
Nodo *crearNodoNuevo(int numero){
    Nodo *nodo = new Nodo();
    nodo->dato = numero;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

//Buscar un nodo por su valor dentro del arbol
Nodo* buscarValor(Nodo *raiz, int numero){
    if (raiz == NULL)
        return NULL;

    if (raiz->dato == numero)
        return raiz;

    Nodo *resultado = buscarValor(raiz->izq, numero);
    if (resultado != NULL)
        return resultado;
    
    return buscarValor(raiz->der, numero);
}

// saber si un valor ya esta existene en el arbol
bool existeValor(Nodo *raiz, int numero){
    return buscarValor(raiz, numero) != NULL;
}

//Insertar un nuevo hijo en un nodo específico
void agregarNodo(Nodo* raiz){
    if (raiz == NULL){
        cout << "Debe de crear la raiz\n";
        return;
    }
    
    int padre, hijo;
    char posicion;
    
    cout << "Ingrese el valor del nodo padre: ";
    cin >> padre;
    
    Nodo *nodoPadre = buscarValor(raiz, padre);
    if (nodoPadre == NULL){
        cout << "No existe un nodo con ese valor\n";
        return;
    }
    
    cout << "Ingrese el valor del nuevo hijo: ";
    cin >> hijo;
    
    if(existeValor(raiz, hijo)){
        cout << "El valor ya existe en el arbol. No se agregara\n";
        return;
    }
    
    cout << "Desea colocar a la izquierda (I) o a la derecha (D)? ";
    cin >> posicion;
    
    Nodo *nuevoHijo = crearNodoNuevo(hijo);
    
    if ((posicion == 'I' || posicion == 'i') && nodoPadre->izq == NULL){
        nodoPadre->izq = nuevoHijo;
    }
    else if ((posicion == 'D' || posicion == 'd') && nodoPadre->der == NULL){
        nodoPadre->der = nuevoHijo;
    }
    else{
        cout << "No se puede agregar: lado ocupado o entrada invalida\n"; 
    }
}

// Funciones para recorrer árbol en in, pre y post orden
void preorden(Nodo *nodo){
    if(nodo == NULL){
        return;
    }
    cout << nodo->dato << " ";
    preorden(nodo->izq);
    preorden(nodo->der);
}

void inorden(Nodo *nodo){
    if (nodo == NULL){ 
        return;
    }
    inorden(nodo->izq);
    cout << nodo->dato << " ";
    inorden(nodo->der);
}

void postorden(Nodo *nodo){
    if (nodo == NULL){
        return;
    }
    postorden(nodo->izq);
    postorden(nodo->der);
    cout << nodo->dato << " ";
}

void leerarbol(Nodo *raiz){
    if (raiz == NULL) {
        cout << "El árbol es nulo o está vacío \n";
        return;
    }
    cout << "Ordenando nodos en pre-orden" << endl;
    preorden(raiz);
    cout << endl;
    cout << "Ordenando nodos en in-orden" << endl;
    inorden(raiz);
    cout << endl;
    cout << "Ordenando nodos en post-orden" << endl;
    postorden(raiz);
    cout << endl;
}

// Función para determinar si el árbol es binario
bool esa_ondaesbinaria(Nodo* raiz, int menor, int mayor){
    if (raiz == NULL){
        return true;
    }
    if (raiz->dato <= menor || raiz->dato >= mayor){
        return false;
    }
    return esa_ondaesbinaria(raiz->izq, menor, raiz->dato) && esa_ondaesbinaria(raiz->der, raiz->dato, mayor);
}

void generobinario(Nodo* raiz){ 
    if (raiz == NULL){
        cout << "No hay nada en el árbol aún...";
        return;
    }
    if (esa_ondaesbinaria(raiz, -1000000, 1000000)){
        cout << "El árbol es binario";
    }else{
        cout << "El árbol se identifica como NO binario";
    }
}

// Mostrar el arbol de forma textual
void imprimirArbol(Nodo *raiz, int nivel = 0) {
    if (raiz == NULL)
        return;

    imprimirArbol(raiz->der, nivel + 1);

    for (int i = 0; i < nivel; i++)
        cout << "   ";

    cout << raiz->dato << endl;

    imprimirArbol(raiz->izq, nivel + 1);
}

// Clase Arbol para manejar el menú
class Arbol {
private:
    Nodo* raiz;

public:
    Arbol() : raiz(NULL) {}
    
    void EstablecerlaRaiz() {
        if (raiz != NULL) {
            cout << "El árbol ya tiene raíz." << endl;
            return;
        }
        int valor;
        cout << "Ingrese el valor de la raíz: ";
        cin >> valor;
        raiz = crearNodoNuevo(valor);
        cout << "Raíz creada exitosamente." << endl;
    }
    
    void AgregarunHijo() {
        agregarNodo(raiz);
    }
    
    void mostrar() {
        if (raiz == NULL) {
            cout << "El árbol está vacío." << endl;
            return;
        }
        cout << "Árbol:" << endl;
        imprimirArbol(raiz);
        cout << endl;
        leerarbol(raiz);
        cout << endl;
        generobinario(raiz);
        cout << endl;
    }
};

//Menu para seleccionar la opcion que se desea utilizar.
int main(){    
    Arbol arbol;
    int opcion;

    do{
        cout << "\n**Menu tipos de arboles" << endl;
        cout << "1. Establecer una raiz" << endl;
        cout << "2. Agregar hijos a un nodo" << endl;
        cout << "3. Mostrar arbol creado" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion del menu: ";
        cin >> opcion;

        //Casos de opcion para cuando el usuario desee ingresar informacion.    
        switch(opcion){
            case 1: 
                arbol.EstablecerlaRaiz();
                break;
            case 2:
                arbol.AgregarunHijo();
                break;
            case 3:
                arbol.mostrar();
                break;
            case 4:
                cout << "Esta saliendo del programa..." << endl;
                break;
            default:
                cout << "La opcion es invalida ingrese otro numero." << endl;
        }
    } while (opcion != 4);

    return 0;
}
