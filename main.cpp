#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;


class GrafoMatriz{
    //matriz booleana
    vector<vector<bool>> A;
    //matriz de pesos
    vector<vector<int>> pesos;
    bool esDirigido;
public:
    GrafoMatriz(size_t n, bool dirigido = true)
        : A(n,vector<bool>(n,false)),
        pesos(n,vector<int>(n,0)),
        esDirigido(dirigido){}

    size_t numVertices() const {return A.size();}

    //agregar arista u -> v
    void agregarArista(size_t u, size_t v,int peso = 1){
        //validaciones basicas evitar accesos invalidos
        if(u >= numVertices() || v >= numVertices()){
            return;
        }
        A[u][v] = true;
        pesos[u][v] = peso;
        if(!esDirigido){
            A[v][u] = true;
            pesos[v][u] = peso;
        }
    }

    void eliminarArista(size_t u, size_t v){
        if(u >= numVertices() || v >= numVertices()){
            return;
        }
        A[u][v] = false;
        pesos[u][v] = 0;
        if(!esDirigido){
            A[v][u] = false;
            pesos[v][u] = 0;
        }
    }

    bool existeArista(size_t u, size_t v){
        if(u >= numVertices() || v >= numVertices()){
            return false;
        }
        return A[u][v];
    }

    void imprimir() const{
        cout << "Matriz de adyacencia ("
            << (esDirigido? "dirigido" : "no dirigido")
            << ")\n";
        for(size_t i = 0; i< numVertices(); ++i){
            for(size_t j = 0; j< numVertices(); ++j){
                cout << (A[i][j]? 1 : 0) << " ";
            }
            cout << endl;
        }
    }


    int obtenerPeso(size_t u, size_t v) {
    if(u >= numVertices() || v >= numVertices() || !A[u][v]) {
        return 0;
    }
    return pesos[u][v];
    }


    //FUNCION PARA CAMBIAR DE TAMAÑO A LOS 2 VECTORES.
    void redimensionar(size_t nuevoN) {


    //formula para crear matriz nueva, con los parametros del tamaño nuevo que queremos
    //tamaño nuevoN x nuevoN y todo lo pone en "false" osea 0´s, crea una base para la cual trabajar
    vector<vector<bool>> nueva(nuevoN, vector<bool>(nuevoN, false));
    //misma cosa pero con pesos como se maneja con vectores
    vector<vector<int>> nuevaPesos(nuevoN, vector<int>(nuevoN, 0));


    //guarda el tamaño nuevo de matrizes que tiene que copiar
    //por ejemplo, si quieres que el tamaño nuevo sea 5, y antes era 3, guarda ese "3"
    //para saber que copiar
    size_t minN = min(nuevoN, A.size());

    //recorre y copia los valores antiguos en la matriz
    for (size_t i = 0; i < minN; i++) {
        for (size_t j = 0; j < minN; j++) {
            nueva[i][j] = A[i][j];
            nuevaPesos[i][j] = pesos[i][j];
        }
    }

    //la matriz vieja es remplazada por la nueva que se acaba de trabajar
    A = nueva;
    pesos = nuevaPesos;
        }



        void dijkstra(size_t s,
                vector<int>& dist,
                vector<int>& parent)
    {
        const int INF = 1e9;
        size_t n = numVertices();
        dist.assign(n,INF);
        parent.assign(n,-1);

        if(s >= n) return;

        dist[s] = 0;

        using P = pair<int,size_t>; //(int,size_t)
        priority_queue<P,vector<P>,greater<P>> pq;

        pq.push({0,s});

        while(!pq.empty()){

            //AUTO NO FUNCIONA CON EL COMPILADOR, por eso se cambia y si se asignan tipos de variables
            P top = pq.top();
            pq.pop();
            int du = top.first;
            size_t u = top.second;

            if(du != dist[u]) continue;

        for(size_t v = 0; v < n; v++) {
            if(A[u][v]) {  // si existe arista
                int w = pesos[u][v];  // obtiene el peso
                if(dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = (int)u;
                    pq.push({dist[v], v});
                    }
                }
            }
        }
    }
}; 



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