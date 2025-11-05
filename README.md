# Código fuente en C++

```cpp
#include <iostream>
using namespace std;

// Nodos de árboles 
struct Nodo {
    int dato;
    Nodo *der;
    Nodo *izq;
};

// Función para la creación de un nodo nuevo
Nodo *crearNodoNuevo(int numero) {
    Nodo *nodo = new Nodo();
    nodo->dato = numero;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

// Buscar un nodo por su valor dentro del árbol
Nodo* buscarValor(Nodo *raiz, int numero) {
    if (raiz == NULL)
        return NULL;

    if (raiz->dato == numero)
        return raiz;

    Nodo *resultado = buscarValor(raiz->izq, numero);
    if (resultado != NULL)
        return resultado;

    return buscarValor(raiz->der, numero);
}

// Saber si un valor ya está existente en el árbol
bool existeValor(Nodo *raiz, int numero) {
    return buscarValor(raiz, numero) != NULL;
}

// Insertar un nuevo hijo en un nodo específico
void agregarNodo(Nodo* raiz) {
    if (raiz == NULL) {
        cout << "Debe de crear la raiz\n";
        return;
    }

    int padre, hijo;
    char posicion;

    cout << "Ingrese el valor del nodo padre: ";
    cin >> padre;

    Nodo *nodoPadre = buscarValor(raiz, padre);
    if (nodoPadre == NULL) {
        cout << "No existe un nodo con ese valor\n";
        return;
    }

    cout << "Ingrese el valor del nuevo hijo: ";
    cin >> hijo;

    if (existeValor(raiz, hijo)) {
        cout << "El valor ya existe en el arbol. No se agregara\n";
        return;
    }

    cout << "Desea colocar a la izquierda (I) o a la derecha (D)? ";
    cin >> posicion;

    Nodo *nuevoHijo = crearNodoNuevo(hijo);

    if ((posicion == 'I' || posicion == 'i') && nodoPadre->izq == NULL) {
        nodoPadre->izq = nuevoHijo;
    } else if ((posicion == 'D' || posicion == 'd') && nodoPadre->der == NULL) {
        nodoPadre->der = nuevoHijo;
    } else {
        cout << "No se puede agregar: lado ocupado o entrada invalida\n";
    }
}

// Mostrar el árbol de forma textual
void imprimirArbol(Nodo *raiz, int nivel = 0) {
    if (raiz == NULL)
        return;

    imprimirArbol(raiz->der, nivel + 1);

    for (int i = 0; i < nivel; i++)
        cout << "   ";

    cout << raiz->dato << endl;

    imprimirArbol(raiz->izq, nivel + 1);
}

// Funciones para recorrer árbol en pre, in y post orden

void preorden(Nodo *nodo) {
    if (nodo == NULL)
        return;

    cout << nodo->dato << " ";
    preorden(nodo->izq);
    preorden(nodo->der);
}

void inorden(Nodo *nodo) {
    if (nodo == NULL)
        return;

    inorden(nodo->izq);
    cout << nodo->dato << " ";
    inorden(nodo->der);
}

void postorden(Nodo *nodo) {
    if (nodo == NULL)
        return;

    postorden(nodo->izq);
    postorden(nodo->der);
    cout << nodo->dato << " ";
}

void leerarbol(Nodo *raiz) {
    if (raiz == NULL) {
        cout << "El árbol es nulo o está vacío\n";
        return;
    }

    cout << "Ordenando nodos en pre-orden:" << endl;
    preorden(raiz);
    cout << "\nOrdenando nodos en in-orden:" << endl;
    inorden(raiz);
    cout << "\nOrdenando nodos en post-orden:" << endl;
    postorden(raiz);
    cout << endl;
}

// Función para determinar si el árbol es binario
bool esa_ondaesbinaria(Nodo* raiz, int menor, int mayor) {
    if (raiz == NULL)
        return true;

    if (raiz->dato <= menor || raiz->dato >= mayor)
        return false;

    return esa_ondaesbinaria(raiz->izq, menor, raiz->dato) &&
           esa_ondaesbinaria(raiz->der, raiz->dato, mayor);
}

void generobinario(Nodo* raiz) {
    if (raiz == NULL) {
        cout << "No hay nada en el árbol aún...\n";
        return;
    }

    bool esbinaria = esa_ondaesbinaria(raiz, INT_MIN, INT_MAX);

    string motivo_posi = "cumple con las condiciones, como orden de izquierda a derecha y todos los nodos tienen menos de 3 hijos";
    string motivo_nega = "no cumple con las condiciones, como orden de izquierda a derecha, o algún nodo tiene más de 2 hijos";

    if (esbinaria) {
        cout << "El árbol es binario ya que " << motivo_posi << endl;
    } else {
        cout << "El árbol se identifica como NO binario porque " << motivo_nega << endl;
    }
}

// Esta función llama a la función esa_ondaesbinaria para leer el árbol y devolver un valor que procesa esta función e imprime si es binaria o no.

//Menu para seleccionar la opcion que se desea utilizar.
int main() {
    Nodo *raiz = NULL;
    int opcion;

    do {
        cout << "\n***Menu tipos de arboles***" << endl;
        cout << "1. Establecer una raiz" << endl;
        cout << "2. Agregar hijos a un nodo" << endl;
        cout << "3. Mostrar arbol creado" << endl;
        cout << "4. Ordenar nodos en los 3 órdenes" << endl;
        cout << "5. Verificar si es un árbol binario" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion del menu: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                if (raiz != NULL) {
                    cout << "La raíz ya existe." << endl;
                } else {
                    int valorRaiz;
                    cout << "Ingrese el valor de la raíz: ";
                    cin >> valorRaiz;
                    raiz = crearNodoNuevo(valorRaiz);
                    cout << "Raíz creada correctamente." << endl;
                }
                break;
            }

            case 2:
                agregarNodo(raiz);
                break;

            case 3:
                if (raiz == NULL)
                    cout << "El árbol está vacío.\n";
                else {
                    cout << "Estructura del árbol:\n";
                    imprimirArbol(raiz);
                }
                break;

            case 4:
                leerarbol(raiz);
                break;

            case 5:
                generobinario(raiz);
                break;

            case 6:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "La opcion es invalida, ingrese otro numero." << endl;
                break;
        }

    } while (opcion != 6);

    return 0;
}
