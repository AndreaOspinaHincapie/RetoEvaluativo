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
    /*
     Función que recibe la lista de películas e imprime en consola cada una de las características de estas.
     Retorna el ID de la película elegida por el usuario.
    */
    list<Pelicula>::iterator it;
    string ID="";
    unsigned sala=0,cont=0;
    cout<<"Peliculas: "<<endl;
    if(Peliculas.size()>0){
        //Si hay películas, se imprimen las funciones
        cout<<setw(5)<<left<<"ID"<<setw(15)<<left<<"Nombre"<<setw(10)<<left<<"Genero"<<setw(15)<<left<<"Duracion(min)"<<setw(10)<<left<<"Sala/Hora"<<setw(10)<<left<<"Asientos"<<setw(15)<<right<<"Clasificacion"<<endl;
        for(it=Peliculas.begin();it!=Peliculas.end();it++){
            if((*it).getAsientosDisponibles()!=0){
            cout<<setw(5)<<left<<(*it).getID()<<setw(15)<<left<<(*it).getNombre()<<setw(10)<<left<<(*it).getGenero()<<setw(15)<<left<<(*it).getDuracionMin()<<setw(10)<<left<<to_string((*it).getSala())+"/"+(*it).getHora()<<setw(10)<<left<<to_string((*it).getAsientosDisponibles())+'/'+to_string((*it).getCapacidadMax())<<setw(15)<<right<<(*it).getClasificacion()<<endl;
            }
         }
        cout<<"--------------------------------------------------------------------------------"<<endl;
        do{
            //Seleccionando ID y sala de la película que desea verse
            if(cont>0) cout<<"ID/sala no validos"<<endl;
            cout<<"Ingrese el ID de la funcion que desea ver: "<<endl;
            getline(cin,ID);
            cout<<"Ingrese la sala de la funcion que desea ver: "<<endl;
            cin>>sala;
            cin.ignore();
            cont++;
        }while(!IsInMovieDatabase(Peliculas,ID,sala));
    }
    else{ //Si no hay películas en la base de datos
        cout<<"Por el momento no hay funciones disponibles"<<endl;
    }
     return ID;
}
int TipoAsiento(){
    //Imprimiendo tabla con tipos de asientos disponibles.
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
int AsientosDisponibles(string ID, int tipo, string &fila, int &asiento, list<Pelicula>Peliculas){
    /*
     Función que recibe un ID, un tipo de asiento, la lista de películas y retorna por referencia
     la fila y asiento elegidos por el usuario tras imprimir asientos en consola.
     Para facilidad de lectura, sólo se muestran los asientos de cada categoría y su ubicación respecto a pantalla
     y otras categorías.
     Retorna 0 si no hay asientos disponibles y 1 en caso contrario.
    */
   Pelicula Ver;
   list<Pelicula>::iterator it;
   int cont=0, total=0;
   if(Peliculas.size()>0){
       for(it=Peliculas.begin();it!=Peliculas.end();it++){
           if((*it).getID()==ID){
               Ver=(*it);
               break;
           }
       }
       if(tipo==1){
           //Si se elige general
          vector<string>general;
          vector<int>asientos;
          vector<string>::iterator it;
          vector<int>::iterator it2;
          general=Ver.getGeneral();
          cont=0;
          total=0;
          cout<<"------------------------Pantalla-------------------------"<<endl;
          for(it=general.begin();it!=general.end();it++){
              asientos=Ver.getAsientos().at((*it));
              cout<<(*it)<<": ";
              for(it2=asientos.begin();it2!=asientos.end();it2++){
                  if((*it2)!=0) cout<<(*it2)<<" ";
                  else{
                      cout<<"X "; //Si asiento está ocupado
                      cont++;
                  }
                  total++;
              }
              cout<<endl;
          }
          cout<<"---------------------------------------------------------"<<endl;
         if(total!=cont){
          do{
           //Si no se han comprado todas las boletas
          cout<<"Seleccione la fila: "<<endl;
          getline(cin,fila);
          }while(!Ver.IsInGeneral(fila));
        }
         else{cout<<"Lo sentimos,los asientos se encuentran ocupados"<<endl;
         return 0;}
       }
       else if(tipo==2){
           //Si elige preferencial
           vector<string>preferencial;
           vector<int>asientos;
           vector<string>::iterator it;
           vector<int>::iterator it2;
           preferencial=Ver.getPreferencial();
           cout<<"------------------------Pantalla-------------------------"<<endl;
           cout<<"------------------------General--------------------------"<<endl;
           for(it=preferencial.begin();it!=preferencial.end();it++){
           asientos=Ver.getAsientos().at((*it));
           cout<<(*it)<<": ";
               for(it2=asientos.begin();it2!=asientos.end();it2++){
                   if((*it2)!=0)cout<<(*it2)<<" " ;
                   else {cout<<"X "; //Si asiento está ocupado
                   cont++;
                   }
                   total++;

           }
           cout<<endl;
         }
            cout<<"---------------------------------------------------------"<<endl;
            if(cont!=total){
                //Si no todos los asientos están ocupados
               do{
               cout<<"Seleccione la fila: "<<endl;
               getline(cin,fila);
               }while(!Ver.IsInPreferencial(fila));
            }
            else{
                cout<<"Lo sentimos, los asientos se encuentan ocupados"<<endl;
                return 0;
            }
       }

       else{
           //Si elige vibrosound
           vector<string>vibro;
           vector<int>asientos;
           vector<string>::iterator it;
           vector<int>::iterator it2;
           vibro=Ver.getVibroSound();
           cout<<"------------------------Pantalla-------------------------"<<endl;
           cout<<"------------------------General--------------------------"<<endl;
           cout<<"----------------------Preferencial-----------------------"<<endl;
           for(it=vibro.begin();it!=vibro.end();it++){
               asientos=Ver.getAsientos().at((*it));
               cout<<(*it)<<": ";
               for(it2=asientos.begin();it2!=asientos.end();it2++){
                   if((*it2)!=0) cout<<(*it2)<<" ";
                   else{
                       cout<<"X "; //Si asiento está ocupado
                       cont++;
                   }
                   total++;
               }
               cout<<endl;
           }
            cout<<"---------------------------------------------------------"<<endl;
           if(cont!=total){
               //Si no todos los asientos están ocupados
               do{
               cout<<"Seleccione la fila: "<<endl;
               getline(cin,fila);
               }while(!Ver.IsInVibro(fila));
            }
           else{cout<<"Lo sentimos, por el momento no hay asientos disponibles"<<endl; return 0;}
       }
       if(cont!=total){
           //Si no están ocupados todos los asientos
           do{
               do{
               cout<<"Seleccione el asiento: "<<endl;
               cin>>asiento;
               cin.ignore();
               }while(asiento>20 || asiento<0);
           }while(!Ver.Is_Available(fila,asiento));
           (*it).ComprarAsiento(fila,asiento);
           //Guardar datos de asientos y películas
           GuardarAsientos(Peliculas);
           GuardarPeliculas(Peliculas);
       }
       return 1;
    }
   else{
       cout<<"En el momento no hay funciones disponibles. "<<endl;
       return 0;
   }
}

void ComprarAsiento(){
    /*
     Función que implementa las funcionalidades de usuario y administrador de comprar asientos disponibles.
    */
    string ID="",fila="";
    int tipo=0, asiento=0;
    int pago=0;
    int cont=0;
    string fecha="", fechaActual="";
    fechaActual=ObtenerFechaActual(); //Obteniendo fecha actual para reporte de ventas
    int AGen=0,VenGen=0,APref=0,VenPref=0,AVibro=0,VenVibro=0;
    LeerVentas(fecha,AGen,VenGen,APref,VenPref,AVibro,VenVibro); //Leyendo datos de ventas
    if(fechaActual!=fecha){AGen=0;VenGen=0;APref=0;VenPref=0;AVibro=0;VenVibro=0;} //Si se ha cambiado de día
    list<Pelicula> Peliculas;
    ObtenerDatosPeliculas(Peliculas); //Obteniendo películas
    ID=DesplegarFunciones(Peliculas); //Imprimiendo funciones
    if(Peliculas.size()>0){
        //Si hay funciones
        tipo=TipoAsiento();
        int r=AsientosDisponibles(ID,tipo,fila,asiento,Peliculas);
        if(r){
            //Si el tipo elegido tiene asientos disponibles
        if(tipo==1){
               cout<<endl<<"Total: $8500"<<endl;
               do{
                   //Realizando pago y mostrando devuelta
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
                    //Realizando pago preferencial y mostrando devuelta
                    if(cont>0) cout<<"Pago no valido."<<endl;
                    cout<<"Ingrese su pago: "<<endl;
                    cin>>pago;
                    cin.ignore();
                    cont++;
                }while(pago<9500);
                Devuelta<int>(9500,pago);
                APref++;
                VenPref+=9500;
            }
            else{
                //Realizando pago vibrosound y mostrando devuelta
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
            GuardarVentas(AGen,VenGen,APref,VenPref,AVibro,VenVibro); //Actualizando ventas.
        }
    }
}

#endif // VENTAASIENTOS_H
