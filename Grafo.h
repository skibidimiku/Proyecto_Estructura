#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

class GrafoMatriz{
    //matriz booleana
    vector<vector<bool>> A;
    //matriz de pesos
    vector<vector<float>> pesos;

    vector<string> nombre;
    bool esDirigido;
public:
    GrafoMatriz(size_t n, bool dirigido = true, string nom="")
        : A(n,vector<bool>(n,false)),
        pesos(n,vector<float>(n,0)), 
        nombre(n, nom),
        esDirigido(dirigido){}

    size_t numVertices() const {return A.size();}
    
    void setNombre(size_t v, const string& nom){
        if(v >= numVertices()){
            cout<< "No se encontro el nodo" << endl;
            return;
        }

        nombre[v]=nom;
    }

    int obtenerPeso(size_t u, size_t v) {
        if(u >= numVertices() || v >= numVertices() || !A[u][v]) {
            return 0;
        }
        return pesos[u][v];
    }

    string getNombre(int i){ return nombre[i];}

    bool existeArista(size_t u, size_t v){
        if(u >= numVertices() || v >= numVertices()){
            return false;
        }
        return A[u][v];
    }

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

    void imprimirlistaAdyacencia() const {
        bool band=false;
        cout << "Lista de adyacencia\n";
        for (size_t i = 0; i < numVertices(); i++){
            for (size_t j = 0; j < numVertices(); j++){
                if(A[i][j]==true){
                    if(band==false){
                        cout << "(" << nombre[i] << "): [ " << nombre[j];
                        band=true;
                    }else if(band==true){
                        cout << ", " << nombre[j];
                    }
                }
            }
            if(band==false){
                cout << nombre[i] << " No conecta con nada." << endl;
            }else{
                cout << " ]" << endl;
                band=false;
            }
        }
    }




    //FUNCION PARA CAMBIAR DE TAMAÑO A LOS 2 VECTORES.
    void redimensionar(size_t nuevoN) {
        //formula para crear matriz nueva, con los parametros del tamaño nuevo que queremos
        //tamaño nuevoN x nuevoN y todo lo pone en "false" osea 0´s, crea una base para la cual trabajar
        vector<vector<bool>> nueva(nuevoN, vector<bool>(nuevoN, false));
        //misma cosa pero con pesos como se maneja con vectores
        vector<vector<float>> nuevaPesos(nuevoN, vector<float>(nuevoN, 0));
        vector<string> nuevoNom(nuevoN, "");


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
            nuevoNom[i]=nombre[i];
        }

        //la matriz vieja es remplazada por la nueva que se acaba de trabajar
        A = nueva;
        pesos = nuevaPesos;
        nombre = nuevoNom;
    }

        
    void eliminarNo(size_t idNo){ //Este metodo es basicamente una copia de redimensionar
        if(idNo >= numVertices()) return;

        size_t nuevoN = numVertices() - 1;

        if(nuevoN == 0){ //Si queda vacia se limpia todo se ciera este proceso
            A.clear();
            pesos.clear();
            nombre.clear();
            return;
        }

        vector<vector<bool>> nueva(nuevoN, vector<bool>(nuevoN, false));
        vector<vector<float>> nuevaPesos(nuevoN, vector<float>(nuevoN, 0));
        vector<string> nuevoNom(nuevoN, "");

        size_t iaux=0;
        for (size_t i = 0; i < numVertices() ; i++){
            if(i == idNo) continue; //Al consegir el valor a borrar se salta este ciclo y asi las varibles                       
            size_t jaux=0;          // auxiliares se queden 1 valor atras y asi sirva para remplazar los otros datos
            for(size_t j = 0; j < numVertices() ; j++){
                if(j == idNo) continue;
                nueva[iaux][jaux]= A[i][j];
                nuevaPesos[iaux][jaux] = pesos[i][j];
                jaux++;
            }
            nuevoNom[iaux] = nombre[i];
            iaux++; 
        }
        
        A = nueva;
        pesos = nuevaPesos;
        nombre = nuevoNom;
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





class GrafoBFS {
private:
    GrafoMatriz& grafo;        // referencia al grafo (matriz de adyacencia)
    vector<int> distancia;     // distancia (niveles) desde la(s) fuente(s)
    vector<int> padre;         // padre en el BFS (árbol)
    vector<int> ordenVisita;   // orden en que se visitan (se sacan de la cola)

public:
    // Constructor: inicializa vectores según número de vértices del grafo
    GrafoBFS(GrafoMatriz& g)
        : grafo(g),
          distancia(g.numVertices(), -1),
          padre(g.numVertices(), -1) {}

    // Ejecuta BFS desde un nodo fuente (marca distancias y padres)
    void bfsDesde(int fuente) {
        int n = (int)grafo.numVertices();
        distancia.assign(n, -1);
        padre.assign(n, -1);
        ordenVisita.clear();

        queue<int> q;
        distancia[fuente] = 0;
        q.push(fuente);

        while(!q.empty()) {
            int u = q.front(); q.pop();
            ordenVisita.push_back(u);

            // recorremos todos los nodos y comprobamos si hay arista u->v
            for(size_t v = 0; v < grafo.numVertices(); ++v) {
                // si existe arista y v aún no fue visitado
                if(grafo.existeArista(u, v) && distancia[(int)v] == -1) {
                    distancia[(int)v] = distancia[u] + 1;
                    padre[(int)v] = u;
                    q.push((int)v);
                }
            }
        }
    }

    // Ejecuta BFS sobre todo el grafo (maneja componentes desconectados)
    void ejecutar() {
        int n = (int)grafo.numVertices();
        distancia.assign(n, -1);
        padre.assign(n, -1);
        ordenVisita.clear();

        for(int s = 0; s < n; ++s) {
            if(distancia[s] != -1) continue; // ya visitado en otra componente
            queue<int> q;
            distancia[s] = 0;
            q.push(s);

            while(!q.empty()) {
                int u = q.front(); q.pop();
                ordenVisita.push_back(u);

                for(size_t v = 0; v < grafo.numVertices(); ++v) {
                    if(grafo.existeArista(u, v) && distancia[(int)v] == -1) {
                        distancia[(int)v] = distancia[u] + 1;
                        padre[(int)v] = u;
                        q.push((int)v);
                    }
                }
            }
        }
    }

    // Devuelve la distancia calculada (o -1 si inalcanzable)
    const vector<int>& getDistancias() const { return distancia; }
    const vector<int>& getPadres() const { return padre; }
    const vector<int>& getOrdenVisita() const { return ordenVisita; }

    // Imprime resultados básicos de BFS
    void imprimirResultados() const {
        cout << "\nBFS - Orden de visita: ";
        for(size_t i = 0; i < ordenVisita.size(); ++i) {
            if(i) cout << ", ";
            cout << ordenVisita[i];
        }
        cout << "\nDistancias:\n";
        for(size_t i = 0; i < distancia.size(); ++i) {
            cout << i << ": ";
            if(distancia[i] == -1) cout << "Inf";
            else cout << distancia[i];
            cout << "\n";
        }
    }
};




class GrafoDFS {
private:
    GrafoMatriz& grafo;         // referencia al grafo sobre el que trabajamos

    // Vectores de estado usados por el DFS:
    vector<bool> visitado;      // si un nodo fue visitado (negro/visitado)
    vector<bool> enRecursion;   // marcador "gris" para detectar ciclos
    vector<int> tiempoEntrada;  // tiempo de entrada (tin)
    vector<int> tiempoSalida;   // tiempo de salida (tout)
    vector<int> padre;          // padre en el árbol DFS (-1 si ninguno)

    int timer;                  // contador de tiempo global (tin/tout)
    bool hayCiclo;              // true si se detectó un ciclo
    vector<int> ordenVisita;    // orden en que se visitaron (preorden)

    
    void dfsRec(int u) {
        visitado[u] = true;
        enRecursion[u] = true;            // gris: en pila de llamadas
        tiempoEntrada[u] = timer++;       // registrar tin
        ordenVisita.push_back(u);         // guardar preorden

        for(size_t v = 0; v < grafo.numVertices(); ++v) {
            if(grafo.existeArista(u, v)) {
                if(!visitado[v]) {
                    padre[v] = u;          // fijar padre en el árbol DFS
                    dfsRec(v);
                } else if(enRecursion[v]) {
                    // Si v está en recursión, u->v es arista de retroceso
                    hayCiclo = true;
                }
            }
        }

        tiempoSalida[u] = timer++;        // registrar tout
        enRecursion[u] = false;           // u sale de la pila (negro)
    }

public:
    GrafoDFS(GrafoMatriz& g)
        : grafo(g),
          visitado(g.numVertices(), false),
          enRecursion(g.numVertices(), false),
          tiempoEntrada(g.numVertices(), -1),
          tiempoSalida(g.numVertices(), -1),
          padre(g.numVertices(), -1),
          timer(0),
          hayCiclo(false) {
    }

    void ejecutar() {
        visitado.assign(grafo.numVertices(), false);
        enRecursion.assign(grafo.numVertices(), false);
        tiempoEntrada.assign(grafo.numVertices(), -1);
        tiempoSalida.assign(grafo.numVertices(), -1);
        padre.assign(grafo.numVertices(), -1);
        ordenVisita.clear();
        timer = 0;
        hayCiclo = false;

        for(size_t u = 0; u < grafo.numVertices(); ++u) {
            if(!visitado[u]) {
                dfsRec(u);
            }
        }
    }

    void ejecutarDesde(int nodo) {
        if(nodo < 0 || nodo >= (int)grafo.numVertices()) {
            cout << "Nodo invalido\n";
            return;
        }

        visitado.assign(grafo.numVertices(), false);
        enRecursion.assign(grafo.numVertices(), false);
        tiempoEntrada.assign(grafo.numVertices(), -1);
        tiempoSalida.assign(grafo.numVertices(), -1);
        padre.assign(grafo.numVertices(), -1);
        ordenVisita.clear();
        timer = 0;
        hayCiclo = false;

        dfsRec(nodo);
    }

    // Indica si se detectó un ciclo durante la última ejecución
    bool tienesCiclo() const { return hayCiclo; }
    
    const vector<int>& getOrdenVisita() const { return ordenVisita; }
    
    const vector<int>& getTiemposEntrada() const { return tiempoEntrada; }
    
    const vector<int>& getTiemposSalida() const { return tiempoSalida; }
    
    const vector<int>& getPadres() const { return padre; }

    void imprimirResultados() const {
        cout << "\n========== RESULTADOS DFS ==========" << "\n";
        cout << "Orden de visita: ";
        for(int v : ordenVisita) {
            cout << v << " ";
        }
        cout << "\n\n";

        cout << "Tiempos de entrada/salida:\n";
        for(size_t u = 0; u < grafo.numVertices(); ++u) {
            cout << "Nodo " << u << ": entrada=" << tiempoEntrada[u]
                 << ", salida=" << tiempoSalida[u];
            if(padre[u] != -1) {
                cout << ", padre=" << padre[u];
            }
            cout << "\n";
        }

        cout << "\n¿Hay ciclo? " << (hayCiclo ? "SI" : "NO") << "\n";
        cout << "====================================\n\n";
    }

    bool existeCamino(int origen, int destino) {
        if(origen < 0 || origen >= (int)grafo.numVertices() ||
           destino < 0 || destino >= (int)grafo.numVertices()) {
            return false;
        }

        vector<bool> visitados(grafo.numVertices(), false);
        return existeCaminoRec(origen, destino, visitados);
    }

private:
    // Auxiliar recursiva para `existeCamino`
    bool existeCaminoRec(int u, int destino, vector<bool>& visitados) {
        if(u == destino) return true;
        
        visitados[u] = true;
        for(size_t v = 0; v < grafo.numVertices(); ++v) {
            if(grafo.existeArista(u, v) && !visitados[v]) {
                if(existeCaminoRec(v, destino, visitados)) {
                    return true;
                }
            }
        }
        return false;
    }
};

