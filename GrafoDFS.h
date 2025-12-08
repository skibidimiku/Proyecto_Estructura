#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

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

