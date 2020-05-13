#ifndef REPORTEVENTAS_H
#define REPORTEVENTAS_H
#include<ctime>
#include"manejoarchivos.h"

string ObtenerFechaActual(){
    /*
     Función que obtiene la fecha actual usando la librería ctime.
     Retorna un string con la forma: dia/mes/año
    */
    string fecha="";
    time_t now=time(nullptr); //Se obtienen los segundos desde Enero 1 de 1970.
    tm *time=localtime(&now); //Se crea un puntero a la estructura tm de la librería
    //Se crea la fecha usando los siguientes elementos de la estructura tm:
    //tm_day (dia del mes: de 1 a 31)
    //tm_mon (mes del año: de 0 a 11)
    //tm_mon (años que han pasado desde 1900)
    fecha=to_string(time->tm_mday)+'/'+to_string(1+time->tm_mon)+'/'+to_string(1900+time->tm_year);
    return fecha;
}
void GuardarVentas(int AGen,int VenGen,int APref,int VenPref,int AVibro, int VenVibro ){
  string fecha=ObtenerFechaActual();
  string escribir=fecha+":"+to_string(AGen)+","+to_string(VenGen)+","+to_string(APref)+","+to_string(VenPref)+","+to_string(AVibro)+","+to_string(VenVibro)+'\n';
  EscribirEnArchivo(escribir,"ReporteVentas");
}
void LeerVentas(string &fecha,int &AGen,int &VenGen,int &APref,int &VenPref,int &AVibro, int &VenVibro ){
    //Leer archivo ReporteVentas.txt
}
void ReporteVentas(){

}


#endif // REPORTEVENTAS_H
