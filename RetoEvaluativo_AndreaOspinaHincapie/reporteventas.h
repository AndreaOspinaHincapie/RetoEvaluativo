#ifndef REPORTEVENTAS_H
#define REPORTEVENTAS_H
#include<ctime>
#include"manejoarchivos.h"
#include<iomanip>
string ObtenerFechaActual(){
    /*
     Función que obtiene la fecha actual usando la librería ctime.
     Retorna un string con la forma: dia/mes/año
    */
    string fecha="";
    time_t now;
    now=time(nullptr); //Se obtienen los segundos desde Enero 1 de 1970.
    tm *tm_local=localtime(&now); //Se crea un puntero a la estructura tm de la librería
    //Se crea la fecha usando los siguientes elementos de la estructura tm:
    //tm_day (dia del mes: de 1 a 31)
    //tm_mon (mes del año: de 0 a 11)
    //tm_mon (años que han pasado desde 1900)
    fecha=to_string(tm_local->tm_mday)+'/'+to_string(1+tm_local->tm_mon)+'/'+to_string(1900+tm_local->tm_year);
    return fecha;
}
void GuardarVentas(int AGen,int VenGen,int APref,int VenPref,int AVibro, int VenVibro ){
  string fecha=ObtenerFechaActual();
  string escribir=fecha+":"+to_string(AGen)+","+to_string(VenGen)+","+to_string(APref)+","+to_string(VenPref)+","+to_string(AVibro)+","+to_string(VenVibro)+'\n';
  EscribirEnArchivo(escribir,"ReporteVentas");
}
void LeerVentas(string &fecha,int &AGen,int &VenGen,int &APref,int &VenPref,int &AVibro, int &VenVibro ){
    string datos=LeerArchivo("ReporteVentas");
    unsigned long posSaltoLinea=0,posPuntos=0,posComa1=0,posComa2=0;
    posSaltoLinea=datos.find('\n');
    if(posSaltoLinea!=string::npos){
        posPuntos=datos.find(":");
        fecha=datos.substr(0,posPuntos);
        posComa1=datos.find(',');
        posComa2=datos.find(',',posComa1+1);
        AGen=stoi(datos.substr(posPuntos+1,posComa1-posPuntos-1));
        VenGen=stoi(datos.substr(posComa1+1,posComa2-posComa1-1));
        posComa1=posComa2;
        posComa2=datos.find(',',posComa1+1);
        APref=stoi(datos.substr(posComa1+1,posComa2-posComa1-1));
        posComa1=posComa2;
        posComa2=datos.find(',',posComa1+1);
        VenPref=stoi(datos.substr(posComa1+1,posComa2-posComa1-1));
        posComa1=posComa2;
        posComa2=datos.find(',',posComa1+1);
        AVibro=stoi(datos.substr(posComa1+1,posComa2-posComa1-1));
        posComa1=posComa2;
        VenVibro=stoi(datos.substr(posComa1+1,posSaltoLinea-posComa1-1));
    }

}
void ReporteVentas(){
    string fecha="", fechaActual="";
    fechaActual=ObtenerFechaActual();
    int AGen=0,VenGen=0,APref=0,VenPref=0,AVibro=0,VenVibro=0;
    LeerVentas(fecha,AGen,VenGen,APref,VenPref,AVibro,VenVibro);
    if(fecha!=fechaActual){
        cout<<"El día de hoy "<<fechaActual<< " no se han vendido asientos"<<endl;
    }
    else{
        cout<<"Ventas del dia de hoy: "<<endl;
        cout<<fechaActual<<endl;
        cout<<setw(15)<<left<<"Tipo de Asiento"<<setw(20)<<right<<"Asientos vendidos"<<setw(5)<<setw(15)<<right<<"Recaudado"<<endl;
        cout<<setw(15)<<left<<"General"<<setw(5)<<setw(20)<<right<<AGen<<setw(5)<<setw(15)<<right<<to_string(VenGen)+" COP"<<endl;
        cout<<setw(15)<<left<<"Preferencial"<<setw(5)<<setw(20)<<right<<APref<<setw(5)<<setw(15)<<right<<to_string(VenPref)+" COP"<<endl;
        cout<<setw(15)<<left<<"Vibrosound"<<setw(5)<<setw(20)<<right<<AVibro<<setw(5)<<setw(15)<<right<<to_string(VenVibro)+" COP"<<endl;
        cout<<"Total Recaudadado: "<<VenGen+VenPref+VenVibro<<" COP"<<endl;
    }
}


#endif // REPORTEVENTAS_H
