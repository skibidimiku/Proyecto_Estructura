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