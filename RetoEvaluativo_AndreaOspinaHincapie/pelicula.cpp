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
}

unsigned int Pelicula::getAsientosDisponibles() const
{
    return asientosDisponibles;
}

void Pelicula::setAsientosDisponibles(unsigned int value)
{
    asientosDisponibles = value;
}

Pelicula::Pelicula()
{

}

Pelicula::Pelicula(string _ID, string _nombre, string _genero, unsigned _duracion, unsigned _sala, string _hora, unsigned _asientos, unsigned _capMax, string _clasificacion)
{
    ID=_ID;
    nombre=_nombre;
    genero=_genero;
    duracionMin=_duracion;
    sala=_sala;
    Hora=_hora;
    asientosDisponibles=_asientos;
    capacidadMax=_capMax;
    clasificacion=_clasificacion;

}

