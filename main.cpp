#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include "Grafo.h"
#include "Vehiculos.h"

using namespace std;


//recipiente universal para un grafo de tamaño "4"
int N=3;
GrafoMatriz G(N, true);


void leerArchivo() {

    ifstream archivo("C:\\Users\\VicPa\\OneDrive\\Desktop\\Projecto final DATOS 2\\grafo.txt");
    if (!archivo.is_open()) {
        cout << "no se pudo abrir grafo.txt\n";
        return;
    }

    string linea;

    while (getline(archivo, linea)) {

        if (linea == "" || linea[0] == '#')
            continue;

        
        //LEE texto como si fuera un archivo, esto es el corazon de la logica.
        //para no poner tanta madre y que lo lea facilmente, le estoy diciendo que
        //lea todo como si fuera texto. (NO caracteres, num, etc.)
        stringstream ss(linea);

        string tipo;
        getline(ss, tipo, ';');  //lee tipo

        //usa el primer carcter de referencia
        char t = tipo[0];

        //ahora que ya sabe de que tipo es cada una, decide en cual entrar
        if (t == 'N') {
            string id, nombre;
            getline(ss, id, ';');
            getline(ss, nombre, ';');
            cout << "[nodo] id=" << id << " nombre=" << nombre << "\n";
        }

        else if (t == 'E') {
            string a, b, peso;
            getline(ss, a, ';');
            getline(ss, b, ';');
            getline(ss, peso, ';');

            //cada que lea algo, verifica:
            //"ES(1,2,3,4,5,6,7,8,9)??????"
            //si es, pasalo de STRING a INT.
            if (!isdigit(a[0])) continue;
            int ia = stoi(a);
            int ib = stoi(b);
            
            
            int ipeso = stoi(peso); //convertir peso.
            G.agregarArista(ia,ib,ipeso);
                

            cout << "[arista] " << a << " -> " << b << " peso=" << peso << "\n";

        }
        
    }//FIN CICLO IF

    cout << "\n";
    G.imprimir();
    archivo.close();

} //FIN DE LEER ARCHIVOS 




int CargarArchivo(){

    ofstream archivo("C:\\Users\\VicPa\\OneDrive\\Desktop\\Projecto final DATOS 2\\grafo.txt");
    if (!archivo.is_open()) {
        cout << "no se pudo abrir grafo.txt\n";
        return 1;
    }


    //guardar Nodos Y recorre vector
    for(size_t i=0; i< G.numVertices(); i++){
        archivo << "N;" << i << ";nodo_" << i << "\n";
    }

    //guardar aristas, 2 for por recorrer matriz se mete en un VECTOR desde otro VECTOR
    for (size_t i = 0; i < G.numVertices(); i++) {
        for (size_t j = 0; j < G.numVertices(); j++) {
            if (G.existeArista(i, j)) {
            archivo << "E;" << i << ";" << j << ";" << G.obtenerPeso(i,j) << "\n"; 
            }
        }
    }
    archivo.close();
}




int AltaArista(){
    
    int a,b,p;
    int band = 1;
    
    while(band==1){
        cout << "Dame el punto de donde empezara la arista.";
            cin >> a;
        cout << "Dame el punto al que llegara.";
            cin >> b;
        cout << "Dame el peso.";
            cin >> p;
            
            //validacion  <--- van a ver mas de estas
            //checka que no borren mas de lo que hay, borre todo o borre "0" nodos para joder el programa
            if (a >= G.numVertices() || b >= G.numVertices()) {
            cout << "Arista no existe / nodo no existente ERROR.\n";
            continue;
        }

            G.agregarArista(a,b,p);
            cout << "\n";
            G.imprimir();
            cout << "\n";
        cout << "Deseas poner otra arista? (1 = Si / 0 = No)";
        cin >> band; 
    } 
    //toda la info que metio el usuario mas la matriz actualizada se mete en el archivo.
    CargarArchivo();
}



int BajaArista(){
    
    int a,b;
    int band = 1;
    
    while(band==1){
        cout << "Dame el punto de donde empieza la arista.";
            cin >> a;
        cout << "Dame el punto al que llega.";
            cin >> b;

            //validacion
            if (a >= G.numVertices() || b >= G.numVertices()) {
            cout << "Error, nodo no existe.\n";
            continue;
        }

            G.eliminarArista(a,b);
            cout << "\n";
            G.imprimir();
            cout << "\n";
            cout << "Deseas poner otra arista? (1 = Si / 0 = No)";
            cin >> band; 
    } 
    //toda la info que metio el usuario mas la matriz actualizada se mete en el archivo.
    CargarArchivo();
}



int AltaNodo(){
    int NSUMA;
    G.imprimir();
        cout << "\n";
        cout << "Cuantos nodos Deseas crear?";
            cin >> NSUMA;
            
            
            size_t nuevoTamano = G.numVertices() + NSUMA;
            G.redimensionar(nuevoTamano);

            G.imprimir();

            CargarArchivo();
}


int BajaNodo(){
    int NRESTA;
    G.imprimir();
        cout << "\n";
        cout << "Cuantos nodos Deseas dar de baja?";
            cin >> NRESTA;
            
        //validacion    
        if (NRESTA <= 0 || NRESTA >= G.numVertices()) {
        cout << "Error.\n";
        return 1;
        }

            size_t nuevoTamano = G.numVertices() - NRESTA;
            G.redimensionar(nuevoTamano);

            G.imprimir();

            CargarArchivo();
}


int EjecutarDijkstra() {
    int fuente;
    cout << "Ingresa el nodo fuente para Dijkstra: ";
    cin >> fuente;
    
    if(fuente >= G.numVertices()) {
        cout << "Error: nodo fuente no existe.\n";
        return 1;
    }

    vector<int> dist, parent;
    G.dijkstra(fuente, dist, parent);

    cout << "\nDistancias minimas desde " << fuente << ":\n";
    for(size_t u = 0; u < G.numVertices(); ++u) {
        if(dist[u] == 1e9)
            cout << u << ": Inf\n";
        else  
            cout << u << ": " << dist[u] << "\n";
    }

    return 0;
}



int main(){
    int selec;

    do{
        cout << "\n---------------------------------------------------------";
        cout << "\n\t\t\t ---> MENU <---";
        cout << "\n\t [1] Cargar red.";
        cout << "\n\t [2] Cargar nueva red a archivo.";
        cout << "\n\t [3] AltaArista.";
        cout << "\n\t [4] BajaArista.";
        cout << "\n\t [5] AltaNodo.";
        cout << "\n\t [6] BajaNodo.";
        cout << "\n\t [7] Dijkstra.";
        cout << "\n\t [0] Salir";
        cout << "\n\n\t Elige una opcion: ";
        cin >> selec;

        switch(selec){
            case 1: leerArchivo();
            break;
            
            case 2: CargarArchivo();
            break;

            case 3: AltaArista();
            break;

            case 4: BajaArista();
            break;

            case 5: AltaNodo();
            break;

            case 6: BajaNodo();
            break;

            case 7: EjecutarDijkstra();
            break;

            case 0: cout << "\n\t Saliendo del programa...\n";
                break;
            default: cout << "\n\t Opcion invalida.\n";
                break;
        }
    }while(selec != 0);
    return 0;
}