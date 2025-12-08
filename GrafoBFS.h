#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

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
