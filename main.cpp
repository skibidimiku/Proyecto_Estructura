#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <windows.h>
#include "Grafo.h"

#include "Vehiculos.h"

using namespace std;


//recipiente universal para un grafo de tamaño "4"

GrafoMatriz G(0, true, "");
VehiculoClase tablaVehiculos(10);

void leerArchivoVehi(){
        ifstream archivo("Vehiculo.txt");
        if (!archivo.is_open()) {
            cout << "no se pudo abrir Vehiculo.txt\n";
            return;
        }

        string linea;

         while (getline(archivo, linea)){
            if (linea == "" || linea[0] == '#')continue;

            stringstream ss(linea);

            string tipo;
            getline(ss, tipo, ';');

            char t = tipo[0];
            if(t == 'V'){
                string id, tip, pla, org, des, hor;
                getline(ss, id, ';');
                getline(ss, tip, ';');
                getline(ss, pla, ';');
                getline(ss, org, ';');
                getline(ss, des, ';');
                getline(ss, hor, ';');
                cout << "V: " << "(" << id << ", " << tip << ", " << pla << ", "
                         << org << ", " << des << ", " << hor << ") \n";

                Vehiculo v(id, tip, pla, org, des, hor);
                tablaVehiculos.insertarVehiculo(v);
                Sleep(1000);
                    
            }
        }
        archivo.close();
}

void leerArchivo() {
    int c=1;

    ifstream archivo("grafo.txt");
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
            G.redimensionar(c);
            G.setNombre(c-1, nombre);
            c++; Sleep(1000);
        }else if (t == 'E') {
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
            Sleep(1000);
        }
        
    }//FIN CICLO IF

    cout << "\n";
    G.imprimir();
    archivo.close();
    cout << "\n";

    leerArchivoVehi();

} //FIN DE LEER ARCHIVOS 

void CargarArchivo(){
    ofstream archivo("grafo.txt");
    if (!archivo.is_open()) {
        cout << "no se pudo abrir grafo.txt\n";
        return;
    }


    //guardar Nodos Y recorre vector
    for(size_t i=0; i< G.numVertices(); i++){
        archivo << "N;" << i << ";" << G.getNombre(i) << "\n";
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
    tablaVehiculos.guardarArchiv();
}




void AltaArista(){
    int nVertices = G.numVertices();
    int a,b,p;
    int band = 1;
    
    while(band==1){
        cout << "Dame el punto de donde empezara la arista: ";
            cin >> a;
        cout << "Dame el punto al que llegara: ";
            cin >> b;
        cout << "Dame el peso: ";
            cin >> p;
            
            //validacion  <--- van a ver mas de estas
            //checka que no borren mas de lo que hay, borre todo o borre "0" nodos para joder el programa
            if (a >= nVertices || b >= nVertices) {
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



void BajaArista(){
    int nVertices = G.numVertices();
    int a,b;
    int band = 1;
    
    while(band==1){
        cout << "Dame el punto de donde empieza la arista:";
            cin >> a;
        cout << "Dame el punto al que llega:";
            cin >> b;

            //validacion
            if (a >= nVertices || b >= nVertices) {
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



void AltaNodo(){
    string nom;
    G.imprimir();
        cout << "\n";
        cout << "Dame el nombre del nodo: ";
        cin>>nom;
            
            
            
            size_t nuevoTamano = G.numVertices() + 1;
            G.redimensionar(nuevoTamano);
            cout<<G.numVertices();
            G.setNombre(G.numVertices()-1, nom);


            G.imprimir();

            CargarArchivo();
}


void BajaNodo(){
    int NRESTA;
    int nVertices = G.numVertices();
    G.imprimir();
        cout << "\n";
        cout << "Cuantos nodos Deseas dar de baja:";
            cin >> NRESTA;
            
        //validacion    
        if (NRESTA <= 0 || NRESTA >= nVertices) {
        cout << "Error.\n";
        return;
        }

            size_t nuevoTamano = G.numVertices() - NRESTA;
            G.redimensionar(nuevoTamano);

            G.imprimir();

            CargarArchivo();
}


int EjecutarDijkstra() {
    int fuente;
    int nVertices = G.numVertices();
    cout << "Ingresa el nodo fuente para Dijkstra: ";
    cin >> fuente;
    
    if(fuente >= nVertices) {
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

int EjecutarDFS() {
    int opcion;
    cout << "\n[1] DFS desde todos los nodos (grafo completo)\n";
    cout << "[2] DFS desde un nodo especifico\n";
    cout << "Elige una opcion: ";
    cin >> opcion;

    GrafoDFS dfs(G);

    if(opcion == 1) {
        dfs.ejecutar();
        dfs.imprimirResultados();
    } else if(opcion == 2) {
        int nodo;
        cout << "Ingresa el nodo de inicio: ";
        cin >> nodo;
        
        if(nodo >= (int)G.numVertices() || nodo < 0) {
            cout << "Error: nodo no existe.\n";
            return 1;
        }
        
        dfs.ejecutarDesde(nodo);
        dfs.imprimirResultados();
    } else {
        cout << "Opcion invalida.\n";
        return 1;
    }

    return 0;
}

int EjecutarBFS() {
    int opcion;
    cout << "\n[1] BFS desde todos los componentes\n";
    cout << "[2] BFS desde un nodo especifico\n";
    cout << "Elige una opcion: ";
    cin >> opcion;

    GrafoBFS bfs(G);

    if(opcion == 1) {
        bfs.ejecutar();
        bfs.imprimirResultados();
    } else if(opcion == 2) {
        int nodo;
        cout << "Ingresa el nodo de inicio: ";
        cin >> nodo;

        if(nodo >= (int)G.numVertices() || nodo < 0) {
            cout << "Error: nodo no existe.\n";
            return 1;
        }

        bfs.bfsDesde(nodo);
        bfs.imprimirResultados();
    } else {
        cout << "Opcion invalida.\n";
        return 1;
    }

    return 0;
}

void AltaVeh() {
    string id, tipo, placa, origen, destino, hora;

    cout << "\n--- Alta de Vehiculo ---\n";

    cout << "ID del vehiculo: ";
    cin >> id;

    cout << "Tipo: ";
    cin >> tipo;

    cout << "Placa: ";
    cin >> placa;

    cout << "Origen: ";
    cin >> origen;

    cout << "Destino: ";
    cin >> destino;

    cout << "Hora de entrada: ";
    cin >> hora;

    Vehiculo v(id, tipo, placa, origen, destino, hora);
    tablaVehiculos.insertarVehiculo(v);

    cout << "\nVehiculo registrado correctamente.\n";
    CargarArchivo();
}

void BajaVeh() {
    string id;
    cout << "\n--- Baja de Vehiculo ---\n";
    cout << "ID del vehiculo a eliminar: ";
    cin >> id;

    if (tablaVehiculos.eliminar(id))
        cout << "Vehiculo eliminado correctamente.\n";
    else
        cout << "No se encontro el vehiculo.\n";

}

void BuscarVeh() {
    string id;
    cout << "\n--- Buscar Vehiculo ---\n";
    cout << "Ingresa el ID del vehiculo: ";
    cin >> id;

    Vehiculo* v = tablaVehiculos.buscar(id);

    if (v) {
        cout << "\nVehiculo encontrado:\n";
        cout << "ID: " << v->IdVehiculo << "\n";
        cout << "Tipo: " << v->Tipo << "\n";
        cout << "Placa: " << v->Placa << "\n";
        cout << "Origen: " << v->Origen << "\n";
        cout << "Destino: " << v->Destino << "\n";
        cout << "Hora entrada: " << v->horaEntrada << "\n";
    } else {
        cout << "ID no encontrado\n";
    }
}





int main(){
    int selec;

    do{
        cout << "\n--------------------------------------------------------------------------------------------------";
        cout << "\n\t\t\t ---> MENU <---"; Sleep(500);
        cout << "\n> [1] CargarRed."; 
        cout << "\t [2] GuardarRed.";
        cout << "\t [3] AltaNodo.";
        cout << "\t [4] AltaArista."; Sleep(500);
        cout << "\n> [5] BajaNodo.";
        cout << "\t\t [6] BajaArista.";
        cout << "\t [7] MostrarListaAdj.";
        cout << "\t [8] MostrarMatriz."; Sleep(500);
        cout << "\n> [9] Dijkstra.";
        cout << "\t\t [10] DFS.";
        cout << "\t\t [11] BFS."; Sleep(500);
        cout << "\n> [12] Alta Vehiculo.";
		cout << "\t [13] Baja Vehiculo.";
		cout << "\t [14] Buscar Vehiculo."; Sleep(500);
		cout << "\n> [15] InfoHash.";
        cout << "\t [0] Salir"; Sleep(500);
        cout << "\n\n\t Elige una opcion: ";
        cin >> selec;
        cout << endl;

        Sleep(100);

        switch(selec){
            case 1: leerArchivo();
            break;
            
            case 2: CargarArchivo();
            break;

            case 3: AltaNodo();
            break;

            case 4: AltaArista();
            break;

            case 5: BajaNodo();
            break;

            case 6: BajaArista();
            break;

            case 7: G.imprimirlistaAdyacencia();
            break;

            case 8: G.imprimir();
            break;

            case 9: EjecutarDijkstra();
            break;

            case 10: EjecutarDFS();
            break;

            case 11: EjecutarBFS();
            break;
            
            case 12: AltaVeh(); 
			break;
			
			case 13: BajaVeh(); 
			break;
			
			case 14: BuscarVeh(); 
			break;
			
			case 15: tablaVehiculos.infoHash();
    		break;

            case 0: cout << "\n\t Saliendo del programa...\n";
                break;
            default: cout << "\n\t Opcion invalida.\n";
                break;
        }
    }while(selec != 0);
    return 0;
}     