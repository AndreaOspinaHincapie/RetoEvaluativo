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
    int Filas=0;
    string Hora="";
    string clasificacion="";
    unsigned int capacidadMax=0;
    unsigned int asientosDisponibles=0;
    map<string,vector<int>> Asientos;
    void setAsientosInicial();
    vector<string>Preferencial;
    vector<string>general;
    vector<string>vibroSound;
    void TiposAsientosInicial();


public:
    Pelicula();  
    Pelicula(string _ID,string _nombre, string _genero,unsigned _duracion,unsigned _sala, string _hora, unsigned _capMax, string _clasificacion);
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
    void setAsientos(const map<string, vector<int> > &value);
    map<string, vector<int> > getAsientos() const;
    vector<string> getPreferencial() const;
    void setPreferencial(const vector<string> &value);
    vector<string> getGeneral() const;
    void setGeneral(const vector<string> &value);
    vector<string> getVibroSound() const;
    bool Is_Available(string fila,int asiento);
    bool IsInGeneral(string fila);
    bool IsInPreferencial(string fila);
    bool IsInVibro(string fila);
    void ComprarAsiento(string fila, int numero);

};

#endif // PELICULA_H
