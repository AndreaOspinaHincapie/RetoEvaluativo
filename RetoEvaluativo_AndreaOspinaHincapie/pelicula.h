#ifndef PELICULA_H
#define PELICULA_H

#include<string>
#include<map>
#include<vector>
using namespace std;
class Pelicula
{
private:
    string ID;
    string nombre;
    string genero;
    string duracionMin;
    int sala;
    string Hora;
    string clasificacion;
    int capacidadMax;
    int asientosDisponibles;
    map<string,vector<int>> Asientos;
    void setAsientos(const map<string, vector<int> > &value);




public:
    Pelicula();
    string getID() const;
    void setID(const string &value);
    string getNombre() const;
    void setNombre(const string &value);
    string getGenero() const;
    void setGenero(const string &value);
    string getDuracionMin() const;
    void setDuracionMin(const string &value);
    int getSala() const;
    void setSala(int value);
    string getHora() const;
    void setHora(const string &value);
    string getClasificacion() const;
    void setClasificacion(const string &value);
    int getCapacidadMax() const;
    void setCapacidadMax(int value);
    int getAsientosDisponibles() const;
    void setAsientosDisponibles(int value);
    map<string, vector<int> > getAsientos() const;
};

#endif // PELICULA_H
