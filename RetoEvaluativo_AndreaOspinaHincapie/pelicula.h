#ifndef PELICULA_H
#define PELICULA_H

#include<string>
#include<map>
#include<vector>
using namespace std;
class Pelicula
{
private:
    string ID="";
    string nombre="";
    string genero="";
    unsigned int duracionMin=0;
    unsigned int sala=0;
    string Hora="";
    string clasificacion="";
    unsigned int capacidadMax=0;
    unsigned int asientosDisponibles=0;
    map<string,vector<int>> Asientos;
    void setAsientos(const map<string, vector<int> > &value);




public:
    Pelicula();  
    Pelicula(string _ID,string _nombre, string _genero,unsigned _duracion,unsigned _sala, string _hora, unsigned _asientos, unsigned _capMax, string _clasificacion);
    map<string, vector<int> > getAsientos() const;
    string getID() const;
    void setID(const string &value);
    string getNombre() const;
    void setNombre(const string &value);
    string getGenero() const;
    void setGenero(const string &value);
    unsigned int getDuracionMin() const;
    void setDuracionMin(unsigned int value);
    unsigned int getSala() const;
    void setSala(unsigned int value);
    string getHora() const;
    void setHora(const string &value);
    string getClasificacion() const;
    void setClasificacion(const string &value);
    unsigned int getCapacidadMax() const;
    void setCapacidadMax(unsigned int value);
    unsigned int getAsientosDisponibles() const;
    void setAsientosDisponibles(unsigned int value);
};

#endif // PELICULA_H
