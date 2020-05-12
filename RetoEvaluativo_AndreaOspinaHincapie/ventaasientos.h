#ifndef VENTAASIENTOS_H
#define VENTAASIENTOS_H
#include"manejoarchivos.h"
#include"pelicula.h"
#include"pago.h"
#include<list>
#include<manejopeliculas.h>
void ObtenerAsientos(list<Pelicula>&Peliculas);
void ObtenerTiposAsientos(list<Pelicula>&Peliculas);
string DesplegarFunciones(list<Pelicula>Peliculas){
    list<Pelicula>::iterator it;
    string ID="";
    unsigned sala=0;
    cout<<"Peliculas: "<<endl;
    cout<<"  ID  |          Nombre          |   Genero   | Duracion(minutos) |  Sala/Hora  |Asientos Disponibles|Clasificacion"<<endl;
    for(it=Peliculas.begin();it!=Peliculas.end();it++){
       cout<<(*it).getID()<<"|"<<(*it).getNombre()<<"|"<<(*it).getGenero()<<"|"<<(*it).getDuracionMin()<<"|"<<(*it).getSala()<<"/"<<(*it).getHora()<<"|"<<(*it).getAsientosDisponibles()<<"|"<<(*it).getClasificacion()<<endl;
    }
    do{
        cout<<"Ingrese el ID de la funcion que desea ver: "<<endl;
        getline(cin,ID);
        cout<<"Ingrese la sala de la funcion que desea ver: "<<endl;
        cin>>sala;
        cin.ignore();
    }while(!IsInMovieDatabase(Peliculas,ID,sala));
    return ID;
}
int TipoAsiento(){
    int option=0;
    cout<<"Seleccione el tipo de asiento: "<<endl;
    cout<<"|    Tipo      |    Costo   |"<<endl;
    cout<<"|  1.General   |    $8500   |"<<endl;
    cout<<"|2.Preferencial|    $9500   |"<<endl;
    cout<<"| 3.VibroSound |    $10500  |"<<endl;
    do{
        cout<<"Tipo: ";
        cin>>option;
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
      cout<<"-------------------------------------Pantalla-----------------------------------"<<endl;
      for(it=general.begin();it!=general.end();it++){
          asientos=Ver.getAsientos().at((*it));
          cout<<(*it)<<": ";
          for(it2=asientos.begin();it2!=asientos.end();it2++){
              if((*it2)!=0) cout<<(*it2)<<" ";
              else cout<<"X ";
          }
          cout<<endl;
      }
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
   }
   else if(tipo==2){
       vector<string>preferencial;
       vector<int>asientos;
       vector<string>::iterator it;
       vector<int>::iterator it2;
       preferencial=Ver.getPreferencial();
       cout<<"-------------------------------------Pantalla-----------------------------------"<<endl;
       cout<<"-------------------------------------General------------------------------------"<<endl;
       for(it=preferencial.begin();it!=preferencial.end();it++){
           asientos=Ver.getAsientos().at((*it));
           cout<<(*it)<<": ";
           for(it2=asientos.begin();it2!=asientos.end();it2++){
               if((*it2)!=0) cout<<(*it2)<<" ";
               else cout<<"X ";
           }
           cout<<endl;
       }
       do{
       cout<<"Seleccione la fila: "<<endl;
       getline(cin,fila);
       }while(!Ver.IsInPreferencial(fila));
       do{
           do{
           cout<<"Seleccione el asiento: "<<endl;
           cin>>asiento;
           cin.ignore();
           }while(asiento>20 || asiento<0);
       }while(!Ver.Is_Available(fila,asiento));

   }
   else{
       vector<string>vibro;
       vector<int>asientos;
       vector<string>::iterator it;
       vector<int>::iterator it2;
       vibro=Ver.getVibroSound();
       cout<<"-------------------------------------Pantalla-----------------------------------"<<endl;
       cout<<"-------------------------------------General------------------------------------"<<endl;
       cout<<"-----------------------------------Preferencial---------------------------------"<<endl;
       for(it=vibro.begin();it!=vibro.end();it++){
           asientos=Ver.getAsientos().at((*it));
           cout<<(*it)<<": ";
           for(it2=asientos.begin();it2!=asientos.end();it2++){
               if((*it2)!=0) cout<<(*it2)<<" ";
               else cout<<"X ";
           }
           cout<<endl;
       }
       do{
       cout<<"Seleccione la fila: "<<endl;
       getline(cin,fila);
       }while(!Ver.IsInVibro(fila));
       do{
           do{
           cout<<"Seleccione el asiento: "<<endl;
           cin>>asiento;
           cin.ignore();
           }while(asiento>20 || asiento<0);
       }while(!Ver.Is_Available(fila,asiento));
   }
}

void ComprarAsiento();

#endif // VENTAASIENTOS_H
