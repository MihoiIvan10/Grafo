#include <iostream>
using namespace std;


struct Nodo {
    int destino;
    Nodo *siguiente;
};

void agregarArista(Nodo **listaAdyacencia, int v1, int v2);
void Transitividad(Nodo **listaAdyacencia, int v1, int v2);


Nodo *crearNodo(int destino) {
    Nodo *nuevoNodo = new Nodo;
    nuevoNodo -> destino = destino;
    nuevoNodo -> siguiente = nullptr;
    return nuevoNodo;
}

int main() {
    int numVertices ;
    cin>>numVertices;

    // Crear un arreglo de punteros a nodos
    Nodo **listaAdyacencia = new Nodo *[numVertices];
    for (int i = 0; i < numVertices; i++) {
        listaAdyacencia[i] = nullptr;
    }
    int v1,v2;
    char continuar;
    do{
        cin>>v1;
        cout<<endl;
        cin>>v2;
        cout<<endl;
        agregarArista(listaAdyacencia,v1,v2);
        cout << "¿Desea agregar otra arista? (S/N): ";
        cin >> continuar;
    } while (continuar == 'S' || continuar == 's');

    cout<<"hacemos la lista transitiva"<<endl;
    for(int i=0; i<numVertices; i++){
	    for(int j=0; j<numVertices; j++){
		    if(i != j){
			    Transitividad(listaAdyacencia, i,j);
		    }
	    }
    }


    // Imprimir la lista de adyacencia
    for (int i = 0; i < numVertices; i++) {
        Nodo *nodoActual = listaAdyacencia[i];
        cout << "Vértice " << i << ": ";
        while (nodoActual != nullptr) {
            cout << nodoActual -> destino << " ";
            nodoActual = nodoActual -> siguiente;
        }
        cout <<endl;
    }
    delete[] listaAdyacencia;

    return 0;
}

//       Función que agrega una arista
void agregarArista(Nodo **listaAdyacencia, int v1, int v2) {
    Nodo *nuevoNodo1 = crearNodo(v2);
    nuevoNodo1->siguiente = listaAdyacencia[v1];
    listaAdyacencia[v1] = nuevoNodo1;

    Nodo *nuevoNodo2 = crearNodo(v1);
    nuevoNodo2->siguiente = listaAdyacencia[v2];
    listaAdyacencia[v2] = nuevoNodo2;
}

//       Función para liberar la memoria que se ocupo en la lista de adyacencia
void liberarMemoria(Nodo **listaAdyacencia, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        Nodo *nodoActual = listaAdyacencia[i];
        while (nodoActual != nullptr) {
            Nodo *nodoAEliminar = nodoActual;
            nodoActual = nodoActual->siguiente;
            delete nodoAEliminar;
        }
        listaAdyacencia[i] = nullptr; 
    }
}

//       Función que hace el grafo transitivo 
void Transitividad(Nodo **listaAdyacencia, int v1, int v2){
    if(v1 == v2){
        return;    
    }
    bool encontrada = false;
    for(Nodo *nodoActual = listaAdyacencia[v1]; nodoActual != nullptr; nodoActual = nodoActual ->siguiente){
        if(nodoActual->destino == v2){
            encontrada = true;
            break;
        }
    }
    if (!encontrada) {
        agregarArista(listaAdyacencia, v1, v2);
    }
}
