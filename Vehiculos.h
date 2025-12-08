#include<bits/stdc++.h>
#include<iostream>
#include<string.h>
#include<fstream>

using namespace std;

struct Vehiculo {
    string IdVehiculo;
    string Tipo;
    string Placa;
    string Origen;
    string Destino;
    string horaEntrada;

    Vehiculo(const string& i,
             const string& t,
             const string& p,
             const string& o,
             const string& d,
             const string& h)
        : IdVehiculo(i), Tipo(t), Placa(p), Origen(o), Destino(d), horaEntrada(h) {}
};

class VehiculoClase{
    private:
        vector<list<Vehiculo>> Tabla;
        size_t capacidad;

        size_t HashIdvehiculo(const string& IdVehiculo) {
            unsigned long h = 0;
            for(char c : IdVehiculo){
                h = h * 131 + (unsigned)c;
            }
        return h % capacidad;
        }

    public:
        VehiculoClase(size_t cap = 101)
        : Tabla(cap), capacidad(cap){}

        void insertarVehiculo(const Vehiculo& vehiculo) {
            size_t idx = HashIdvehiculo(vehiculo.IdVehiculo);
            for(auto& lb : Tabla[idx]){
                if(lb.IdVehiculo == vehiculo.IdVehiculo){
                    lb = vehiculo; //actualiza 
                    return;
                }
            }
            Tabla[idx].push_back(vehiculo);
        }

        Vehiculo* buscar(const string& Id){
            size_t idx = HashIdvehiculo(Id);
            for(auto& lb: Tabla[idx]){
                if(lb.IdVehiculo == Id){
                    return &lb;
                }
            }
            return nullptr;
        }

        bool eliminar(const string& id){
            size_t idx = HashIdvehiculo(id);
            for(auto it = Tabla[idx].begin(); it != Tabla[idx].end(); ++it){
                if(it->IdVehiculo == id){
                    Tabla[idx].erase(it);
                    return true;
                }
            }
            return false;
        }

        size_t totalVehiculo()const{
            size_t total = 0;
            for(const auto& bucket : Tabla){
                total += bucket.size();
            }
            return total;
        }

        /*void imprimirDebug() const{
            for(size_t i=0; i < capacidad; ++i){
                cout << "Bucket " << i << ": ";
                for(const auto& lb : Tabla[i]){
                    cout << "{" << lb.IdVehiculo << ", " << lb.Tipo << ", " << lb.Placa << ", "
                         << lb.Origen << ", " << lb.Destino << ", " << lb.horaEntrada << "} -> "; 
                }
                cout << "\n";
            }
        }*/
		void infoHash() const {
        cout << "\n---- INFORMACION DE LA TABLA HASH ----\n";

        cout << "Capacidad (numero de buckets): " << capacidad << "\n";
        size_t total = totalVehiculo();
        cout << "Total de vehiculos almacenados: " << total << "\n";

        double loadFactor = (double)total / capacidad;
        cout << fixed << setprecision(3);
        cout << "Factor de carga: " << loadFactor << "\n";

        cout << "\nDistribucion (vehiculos por bucket):\n";
        for (size_t i = 0; i < capacidad; ++i) {
            cout << "Bucket " << i << ": " << Tabla[i].size() << " vehiculos\n";
        }

        cout << "----------------------------------------\n\n";
    }

};