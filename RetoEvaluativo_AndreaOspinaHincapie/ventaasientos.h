#ifndef VENTAASIENTOS_H
#define VENTAASIENTOS_H
#include"manejoarchivos.h"
#include"pelicula.h"
#include"pago.h"
#include<list>
#include<manejopeliculas.h>
#include<iomanip>
#include<reporteventas.h>
string DesplegarFunciones(list<Pelicula>Peliculas){
    list<Pelicula>::iterator it;
    string ID="";
    unsigned sala=0,cont=0;
    cout<<"Peliculas: "<<endl;
    cout<<setw(5)<<left<<"ID"<<setw(15)<<left<<"Nombre"<<setw(10)<<left<<"Genero"<<setw(15)<<left<<"Duracion(min)"<<setw(10)<<left<<"Sala/Hora"<<setw(10)<<left<<"Asientos"<<setw(15)<<right<<"Clasificacion"<<endl;
    for(it=Peliculas.begin();it!=Peliculas.end();it++){
        if((*it).getAsientosDisponibles()!=0){
        cout<<setw(5)<<left<<(*it).getID()<<setw(15)<<left<<(*it).getNombre()<<setw(10)<<left<<(*it).getGenero()<<setw(15)<<left<<(*it).getDuracionMin()<<setw(10)<<left<<to_string((*it).getSala())+"/"+(*it).getHora()<<setw(10)<<left<<to_string((*it).getAsientosDisponibles())+'/'+to_string((*it).getCapacidadMax())<<setw(15)<<right<<(*it).getClasificacion()<<endl;
        }
     }
    cout<<"--------------------------------------------------------------------------------"<<endl;
    do{
        if(cont>0) cout<<"ID/sala no validos"<<endl;
        cout<<"Ingrese el ID de la funcion que desea ver: "<<endl;
        getline(cin,ID);
        cout<<"Ingrese la sala de la funcion que desea ver: "<<endl;
        cin>>sala;
        cin.ignore();
        cont++;
    }while(!IsInMovieDatabase(Peliculas,ID,sala));
    return ID;
}
int TipoAsiento(){
    int option=0;
    cout<<"Seleccione el tipo de asiento: "<<endl;
    cout<<" ---------------------------"<<endl;
    cout<<"|    Tipo      |    Costo   |"<<endl;
    cout<<"|---------------------------|"<<endl;
    cout<<"|  1.General   |    $8500   |"<<endl;
    cout<<"|---------------------------|"<<endl;
    cout<<"|2.Preferencial|    $9500   |"<<endl;
    cout<<"|---------------------------|"<<endl;
    cout<<"| 3.VibroSound |    $10500  |"<<endl;
    cout<<" ---------------------------"<<endl;
    do{
        cout<<"Tipo: ";
        cin>>option;
        cin.ignore();
    }while(option!=1 && option!=2 && option!=3);
    return option;
};
void AsientosDisponibles(string ID, int tipo, string &fila, int &asiento, list<Pelicula>Peliculas){
   Pelicula Ver;
   list<Pelicula>::iterator it;
   for(it=Peliculas.begin();it!=Peliculas.end();it++){
       if((*it).getID()==ID){
           Ver=(*it);
           break;
       }
   }
   if(tipo==1){
      vector<string>general;
      vector<int>asientos;
      vector<string>::iterator it;
      vector<int>::iterator it2;
      general=Ver.getGeneral();
      cout<<"------------------------Pantalla-------------------------"<<endl;
      for(it=general.begin();it!=general.end();it++){
          asientos=Ver.getAsientos().at((*it));
          cout<<(*it)<<": ";
          for(it2=asientos.begin();it2!=asientos.end();it2++){
              if((*it2)!=0) cout<<(*it2)<<" ";
              else cout<<"X ";
          }
          cout<<endl;
      }
   }
   else if(tipo==2){
       vector<string>preferencial;
       vector<int>asientos;
       vector<string>::iterator it;
       vector<int>::iterator it2;
       preferencial=Ver.getPreferencial();
       cout<<"------------------------Pantalla-------------------------"<<endl;
       cout<<"------------------------General--------------------------"<<endl;
           asientos=Ver.getAsientos().at((*it));
           cout<<(*it)<<": ";
           for(it2=asientos.begin();it2!=asientos.end();it2++){
               if((*it2)!=0) cout<<(*it2)<<" ";
               else cout<<"X ";
           }
           cout<<endl;
       }

   else{
       vector<string>vibro;
       vector<int>asientos;
       vector<string>::iterator it;
       vector<int>::iterator it2;
       vibro=Ver.getVibroSound();
       cout<<"------------------------Pantalla-------------------------"<<endl;
       cout<<"------------------------General--------------------------"<<endl;
       cout<<"----------------------Preferencial-----------------------"<<endl;
       for(it=vibro.begin();it!=vibro.end();it++){
           //asientos=Ver.getAsientos().at((*it));
           cout<<(*it)<<": ";
           for(it2=asientos.begin();it2!=asientos.end();it2++){
               if((*it2)!=0) cout<<(*it2)<<" ";
               else cout<<"X ";
           }
           cout<<endl;
       }
   }
   cout<<"---------------------------------------------------------"<<endl;
   do{
   cout<<"Seleccione la fila: "<<endl;
   getline(cin,fila);
   }while(!Ver.IsInGeneral(fila));
   do{
       do{
       cout<<"Seleccione el asiento: "<<endl;
       cin>>asiento;
       cin.ignore();
       }while(asiento>20 || asiento<0);
   }while(!Ver.Is_Available(fila,asiento));
   (*it).ComprarAsiento(fila,asiento);
   GuardarAsientos(Peliculas);
   GuardarPeliculas(Peliculas);
}

void ComprarAsiento(){
    string ID="",fila="";
    int tipo=0, asiento=0;
    int pago=0;
    int cont=0;
    string fecha="", fechaActual="";
    fechaActual=ObtenerFechaActual();
    int AGen=0,VenGen=0,APref=0,VenPref=0,AVibro=0,VenVibro=0;
    LeerVentas(fecha,AGen,VenGen,APref,VenPref,AVibro,VenVibro);
    if(fechaActual!=fecha){AGen=0;VenGen=0;APref=0;VenPref=0;AVibro=0;VenVibro=0;}
    list<Pelicula> Peliculas;
    ObtenerDatosPeliculas(Peliculas);
    ID=DesplegarFunciones(Peliculas);
    tipo=TipoAsiento();
    AsientosDisponibles(ID,tipo,fila,asiento,Peliculas);
    if(tipo==1){
       cout<<endl<<"Total: $8500"<<endl;
       do{
           if(cont>0) cout<<"Pago no valido."<<endl;
           cout<<"Ingrese su pago: "<<endl;
           cin>>pago;
           cin.ignore();
           cont++;
       }while(pago<8500);
       Devuelta<int>(8500,pago);
       AGen++;
       VenGen+=8500;
    }
    else if(tipo==2){
        cout<<endl<<"Total: $9500"<<endl;
        do{
            if(cont>0) cout<<"Pago no valido."<<endl;
            cout<<"Ingrese su pago: "<<endl;
            cin>>pago;
            cin.ignore();
            cont++;
        }while(pago<9500);
        Devuelta<int>(9500,pago);
        APref++;
        VenGen+=9500;
    }
    else{
        cout<<endl<<"Total: $10500"<<endl;
        do{
            if(cont>0) cout<<"Pago no valido."<<endl;
            cout<<"Ingrese su pago: "<<endl;
            cin>>pago;
            cin.ignore();
            cont++;
        }while(pago<10500);
        Devuelta<int>(10500,pago);
        AVibro++;
        VenVibro+=10500;

    }
    GuardarVentas(AGen,VenGen,APref,VenPref,AVibro,VenVibro);

}

#endif // VENTAASIENTOS_H
