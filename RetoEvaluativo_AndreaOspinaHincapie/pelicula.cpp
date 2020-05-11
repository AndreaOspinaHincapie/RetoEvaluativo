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

string Pelicula::getDuracionMin() const
{
    return duracionMin;
}

void Pelicula::setDuracionMin(const string &value)
{
    duracionMin = value;
}

int Pelicula::getSala() const
{
    return sala;
}

void Pelicula::setSala(int value)
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

int Pelicula::getCapacidadMax() const
{
    return capacidadMax;
}

void Pelicula::setCapacidadMax(int value)
{
    capacidadMax = value;
}

int Pelicula::getAsientosDisponibles() const
{
    return asientosDisponibles;
}

void Pelicula::setAsientosDisponibles(int value)
{
    asientosDisponibles = value;
}

map<string, vector<int> > Pelicula::getAsientos() const
{
    return Asientos;
}

void Pelicula::setAsientos(const map<string, vector<int> > &value)
{
    Asientos = value;
}

Pelicula::Pelicula()
{

}
