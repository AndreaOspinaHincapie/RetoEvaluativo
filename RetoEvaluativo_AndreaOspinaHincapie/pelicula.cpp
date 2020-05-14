#include "pelicula.h"
string Pelicula::getID() const
{
    return ID;
}

void Pelicula::setID(const string &value)
{
    ID = value;
}

string Pelicula::getNombre() const
{
    return nombre;
}

void Pelicula::setNombre(const string &value)
{
    nombre = value;
}

string Pelicula::getGenero() const
{
    return genero;
}

void Pelicula::setGenero(const string &value)
{
    genero = value;
}

unsigned int Pelicula::getDuracionMin() const
{
    return duracionMin;
}

void Pelicula::setDuracionMin(unsigned int value)
{
    duracionMin = value;
}

unsigned int Pelicula::getSala() const
{
    return sala;
}

void Pelicula::setSala(unsigned int value)
{
    sala = value;
}

string Pelicula::getHora() const
{
    return Hora;
}

void Pelicula::setHora(const string &value)
{
    Hora = value;
}

string Pelicula::getClasificacion() const
{
    return clasificacion;
}

void Pelicula::setClasificacion(const string &value)
{
    clasificacion = value;
}

unsigned int Pelicula::getCapacidadMax() const
{
    return capacidadMax;
}

void Pelicula::setCapacidadMax(unsigned int value)
{
    capacidadMax = value;
    if(capacidadMax%20==0) Filas=capacidadMax/20;
    else Filas=(capacidadMax/20)+1;
}

unsigned int Pelicula::getAsientosDisponibles() const
{
    return asientosDisponibles;
}

void Pelicula::setAsientosDisponibles(unsigned int value)
{
    asientosDisponibles = value;
}

void Pelicula::setAsientos(const map<string, vector<int> > &value)
{
    Asientos = value;
}

map<string, vector<int> > Pelicula::getAsientos() const
{
    return Asientos;
}

void Pelicula::setAsientosInicial()
{
    /*
     Creando estructura de sala según capacidad maxima ingresada.
     Una sala tendrá 20 asientos por fila, por lo que la cantidad de filas
     se obtiene a través de la división.
     Si la capacidad máxima no es divisible por 20, se agregará una fila vibrosound
     con los asientos faltantes.
     La estructura se almacena en un mapa cuyas keys son los nombres de cada fila
     y los values son vectores de enteros con el número del asiento.
    */
    string nombreF="";
    if(capacidadMax%20==0){
        Filas=capacidadMax/20;
        for(int i=0;i<Filas;i++){
            vector<int>AsientosFila;
            nombreF=char(65+i);
            for(int j=1;j<=20;j++){
                AsientosFila.push_back(j);
            }
            Asientos.emplace(nombreF,AsientosFila);
        }
    }
    else{
        Filas=(capacidadMax/20)+1;
        int ultimaF=capacidadMax%20;
        for(int i=0; i<Filas;i++){
            vector<int>AsientosFila;
            nombreF=char(65+i);
            if(i<Filas-1){
            for(int j=1;j<=20;j++){
                AsientosFila.push_back(j);
            }
            Asientos.emplace(nombreF,AsientosFila);
        }
        else{
                for(int i=1;i<=ultimaF;i++){
                 AsientosFila.push_back(i);
                }
                Asientos.emplace(nombreF,AsientosFila);
            }

        }

    }

}

vector<string> Pelicula::getVibroSound() const
{
    return vibroSound;
}

bool Pelicula::Is_Available(string fila,int asiento)
{
    /*
    Función que revisa si asiento en determinada fila está disponible.
    */
    if(Asientos.at(fila).at(unsigned(asiento-1))==0) return false;
    else return true;
}

bool Pelicula::IsInGeneral(string fila)
{
    //Función que revisa si fila se encuentra en la lista de filas de asientos generales
    for(unsigned i=0;i<general.size();i++){
        if(fila==general.at(i)) return true;
    }
    return false;
}

bool Pelicula::IsInPreferencial(string fila)
{
    //Función que revisa si fila se encuentra en la lista de filas de asientos preferenciales
    for(unsigned i=0;i<Preferencial.size();i++){
        if(fila==Preferencial.at(i)) return true;
    }
    return false;
}

bool Pelicula::IsInVibro(string fila)
{
  //Función que revisa si fila se encuentra en la lista de filas de asientos vibrosound
    for(unsigned i=0;i<vibroSound.size();i++){
        if(fila==vibroSound.at(i)) return true;
    }
    return false;
}

vector<string> Pelicula::getGeneral() const
{
    return general;
}

void Pelicula::setGeneral(const vector<string> &value)
{
    general = value;
}

vector<string> Pelicula::getPreferencial() const
{
    return Preferencial;
}

void Pelicula::setPreferencial(const vector<string> &value)
{
    Preferencial = value;
}

void Pelicula::TiposAsientosInicial()
{
    /*
     Función que establece filas generales, preferenciales y vibrosound.
     Se divide la cantidad de filas entre los tres tipos de manera que si
     la cantidad de filas no es divisible entre tres, el tipo de asientos con mayor
     cantidad de filas será el tipo general.
    */
    int filasGeneral=(Filas/3)+(Filas%3), filasPreferencial=(Filas/3)+filasGeneral;
    string fila="";
    for(int i=0;i<Filas;i++){
        fila=char(65+i);
        if(i<filasGeneral) general.push_back(fila);
        else if(i>=filasGeneral && i<filasPreferencial) Preferencial.push_back(fila);
        else vibroSound.push_back(fila);
    }
}

void Pelicula::ComprarAsiento(string fila, int numero)
{
    //Función para comprar asiento. Se cambia valor de asiento a cero y se resta uno
    //a los asientosDisponibles.
    Asientos[fila].at(unsigned(numero-1))=0;
    asientosDisponibles--;
}
Pelicula::Pelicula()
{

}

Pelicula::Pelicula(string _ID, string _nombre, string _genero, unsigned _duracion, unsigned _sala, string _hora,  unsigned _capMax, string _clasificacion)
{
    //Constructor al que se le asignan inicialmente valores a los atributos.
    ID=_ID;
    nombre=_nombre;
    genero=_genero;
    duracionMin=_duracion;
    sala=_sala;
    Hora=_hora;
    capacidadMax=_capMax;
    asientosDisponibles=_capMax;
    clasificacion=_clasificacion;
    setAsientosInicial();
    TiposAsientosInicial();
}

