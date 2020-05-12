#include <iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>
#include"pelicula.h"
using namespace std;
int MenuPrincipal();
int MenuAdmin();
void Administrador();
void Usuario();
string LeerArchivo(string nombre);
void EscribirEnArchivo(string escribir, string nombre);
void ObtenerUsuarios(string archivoLeido, map<string,string>& Usuarios);
bool Is_Registered(string nombre, string password,map<string,string>Usuarios);
void GuardarUsuarios(map<string,string>Usuarios);
void RegistrarUsuarios();
void ObtenerDatosPeliculas(list<Pelicula>&Peliculas);
void GuardarPeliculas(list<Pelicula>Peliculas);
void IngresarPeliculas();
bool IsInMovieDatabase(list<Pelicula>PeliculasCine, string ID, unsigned sala);
bool IsNumeric(string a);
void ObtenerAsientos(list<Pelicula>);
void ObtenerTiposAsientos(list<Pelicula>);
void GuardarAsientos();
void GuardarTiposAsientos();
string DesplegarFunciones(list<Pelicula>);
int TipoAsiento();
void ComprarAsiento();

template <class T>
 void Devuelta (T total, T pago) {
  T valor=pago-total; //Variable que contendrá el valor de dinero que se representará/falta por representar.
  T Denom[10]={50000,20000,10000,5000,2000,1000,500,200,100,50};
  cout<<"La devuelta es: "<<endl;
  for(int i=0; i<=9; i++){
      if(valor/Denom[i]!=0){
        cout<<Denom[i]<<": "<<valor/Denom[i]<<endl;
      }
      valor=valor%Denom[i];

         }
  //Valor faltante:
    cout<<"Falta: "<<valor;

}

int main()
{
    int option=0;
    option=MenuPrincipal();
    while(option!=0){
        switch (option) {
        case 1:
            Administrador();
            break;
        case 2:
            Usuario();
            break;
        default:
            cout<<"Opcion no disponible, ingrese otro numero"<<endl;
            break;
        }
        option=MenuPrincipal();
    }
    return 0;
}

//---------------------------------------Interfaz de usuario-----------------------------------------------------
int MenuPrincipal(){
    int op=0;
    cout<<"--------------------------------------------------------------------------------"<<endl;
    cout<<"Bienvenido a CineXolombia, seleccione una de las siguientes opciones:  "<<endl;
    cout<<"Menú de opciones: "<<endl;
    cout<<"1. Soy administrador. "<<endl;
    cout<<"2. Soy usuario. "<<endl;
    cout<<"Ingrese el numero de la opcion o 0 para salir"<<endl;
    cin>>op;
    cout<<"--------------------------------------------------------------------------------"<<endl;
    return op;
}
int MenuAdmin(){
    int op=0;
    cout<<"--------------------------------------------------------------------------------"<<endl;
    cout<<"Bienvenido, seleccione una de las siguientes opciones:  "<<endl;
    cout<<"Menú de opciones: "<<endl;
    cout<<"1. Registrar Usuarios "<<endl;
    cout<<"2. Ingresar peliculas "<<endl;
    cout<<"3. Ofertar asientos "<<endl;
    cout<<"4. Reporte diario de ventas "<<endl;
    cout<<"Ingrese el numero de la opcion o 0 para salir"<<endl;
    cin>>op;
    cout<<"--------------------------------------------------------------------------------"<<endl;
    return op;
}
void Administrador(){
     map<string,string>Usuarios;
     string passwordIng="",password="";
     cout<<"Ingrese la contrasena de administrador: "<<endl;
     cin.ignore();
     getline(cin,passwordIng);
     password=LeerArchivo("sudo");
     if(password==passwordIng+'\n'){
         int option=0;
         option=MenuAdmin();
         while(option!=0){
             switch (option) {
             case 1:
                 RegistrarUsuarios();
                 break;
             case 2:
                 IngresarPeliculas();
                 break;
             case 3:
                 //Ofertar asientos
                 break;
             case 4:
                 //Reporte diario de ventas
                 break;
             default:
                 cout<<"Opcion no disponible, ingrese otro numero"<<endl;
                 break;
             }
             option=MenuAdmin();
         }
     }
     else
       cout<<"Contrasena equivocada."<<endl;
     //GuardarUsuarios(Usuarios);


}
void Usuario(){
    map<string,string>Usuarios;
    string user="",password="";
    string archivo=LeerArchivo("Usuarios");
    ObtenerUsuarios(archivo,Usuarios);
    cout<<"Inicio de sesion: "<<endl;
    cout<<"Nombre de usuario: ";
    cin.ignore();
    getline(cin,user);
    cout<<endl<<"Contrasena:";
    getline(cin,password);
    if(Is_Registered(user,password,Usuarios)){
        //Menu User.
    }
    else{
        cout<<endl<<"Nombre de usuario o contrasena incorrectos."<<endl;
    }
    //Guardar Usuarios
    //Revisar donde puede ser invocar función de guardar.

}
//--------------------------------------Lectura y escritura de archivos---------------------------------------
string LeerArchivo(string nombre){
    /*
     Función que recibe el nombre de un archivo a leer(.txt) y retorna una string con su contenido con saltos de linea
     al finalizar cada linea del archivo.
    */
    ifstream Read;
    string archivo="";
    string aux="";
             try{
            //Asegurando que el archivo .txt se lea correctamente:
            Read.open(nombre+".txt");
            if(!Read.is_open()){
                throw '1';
            }
            //Leyendo linea por linea:
            getline(Read,archivo);
            while(Read.good()){
                    getline(Read,aux);
                    archivo=archivo+'\n'+aux;

            }
            //Cerrando archivo:
            Read.close();
        }
        catch(char c){
            if(c=='1'){
                cout<<"Error al abrir archivo ingresado."<<endl;
            }
        }
        catch(exception ex){
            cout<<ex.what()<<endl;
        }
      return archivo;
     }

void EscribirEnArchivo(string escribir, string nombre){
    /*
     Función que recibe dos strings: el primero es el string que se escribirá en el archivo cuyo nombre es el segundo string
     ingresado (.txt).

    */
    ofstream Write;
    try {
        Write.open(nombre+".txt");
        //Asegurando que el archivo se abra correctamente:
        if(!Write.is_open()){
            throw '1';
        }
        //Escribiendo en el archivo:
        Write<<escribir;
        //Cerrando el archivo:
        Write.close();
        cout<<"Se ha escrito correctamente en el archivo "<<nombre+".txt"<<endl;


    } catch (char c) {
        if(c=='1'){
            cout<<"Error al abrir archivo de escritura"<<endl;
        }

    }catch(exception ex){
        cout<<ex.what()<<endl;
    }

}
//----------------------------------Validacion Usuarios----------------------------------------------------------------------
void ObtenerUsuarios(string archivoLeido, map<string,string>& Usuarios){
    unsigned long inicio=0, posSaltos=0, posPuntos=0;
    string nombre="", password="";
    posSaltos=archivoLeido.find('\n');
    while(posSaltos!=string::npos){
        posPuntos=archivoLeido.find(':',inicio);
        nombre=archivoLeido.substr(inicio,posPuntos-inicio);
        password=archivoLeido.substr(posPuntos+1,posSaltos-posPuntos-1);
        Usuarios.emplace(nombre,password);
        inicio=posSaltos+1;
        posSaltos=archivoLeido.find('\n',inicio);
    }

}
bool Is_Registered(string nombre, string password, map<string,string>Usuarios){
    map<string,string>::iterator it;
    it=Usuarios.find(nombre);
    if(it!=Usuarios.end() && (*it).second==password)
        return true;
    else
        return false;

}
void GuardarUsuarios(map<string,string>Usuarios){
    string escribir="";
    map<string,string>::iterator it;
    for(it=Usuarios.begin(); it!=Usuarios.end();it++){
        escribir=escribir+it->first+":"+it->second+'\n';
    }
    EscribirEnArchivo(escribir,"Usuarios");
}
void RegistrarUsuarios(){
    int numUsers=0,cont=0;
    string archivo=LeerArchivo("Usuarios");
    string nombre="", password="";
    map<string,string>Usuarios;
    ObtenerUsuarios(archivo,Usuarios);
    cout<<"Ingrese el numero de usuarios a registrar: "<<endl;
    cin>>numUsers;
    cin.ignore();
    for(int i=0;i<numUsers;i++){
        cont=0;
        do{

          if(cont>0) cout<<endl<<"Nombre de usuario invalido."<<endl;
          cout<<i+1<<".Ingrese el nombre de usuario (no debe contener dos puntos o comas): ";
          getline(cin,nombre);
          cont++;

        }while(Usuarios.count(nombre)==1 || nombre.find(":")!=string::npos || nombre.find(",")!=string::npos);
        cont=0;
        do{
        if(cont>0)cout<<"Contrasena invalida. no puede contener comas"<<endl;
        cout<<endl<<i+1<<".Ingrese la contrasena del usuario (no debe contener comas): ";
        getline(cin,password);
        cont++;
        }while(password.find(",")!=string::npos);
        Usuarios.emplace(nombre,password);

    }
    GuardarUsuarios(Usuarios);
}
//------------------------------------------Manejo base de datos de peliculas-----------------------------------
void ObtenerDatosPeliculas(list<Pelicula>&Peliculas){
    string Datos="";
    Datos=LeerArchivo("Peliculas");
    unsigned long posSalto=0, posComa=0, posComaAnt=0, inicial=0;
    posSalto=Datos.find('\n');
    while(posSalto!=string::npos){
        Pelicula PIngresar;
        posComa=Datos.find(",",inicial);
        PIngresar.setID(Datos.substr(inicial,posComa-inicial));
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        PIngresar.setNombre(Datos.substr(posComaAnt,posComa-posComaAnt));
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        PIngresar.setGenero(Datos.substr(posComaAnt,posComa-posComaAnt));
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        PIngresar.setDuracionMin(unsigned(stoi(Datos.substr(posComaAnt,posComa-posComaAnt))));
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        PIngresar.setSala(unsigned(stoi(Datos.substr(posComaAnt,posComa-posComaAnt))));
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        PIngresar.setHora(Datos.substr(posComaAnt,posComa-posComaAnt));
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        PIngresar.setAsientosDisponibles(unsigned(stoi(Datos.substr(posComaAnt,posComa-posComaAnt))));
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        PIngresar.setCapacidadMax(unsigned(stoi(Datos.substr(posComaAnt,posComa-posComaAnt))));
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        PIngresar.setClasificacion(Datos.substr(posComaAnt,posSalto-posComaAnt));
        Peliculas.push_back(PIngresar);
        inicial=posSalto+1;
        posSalto=Datos.find('\n',inicial);
    }

}
void GuardarPeliculas(list<Pelicula>Peliculas){
    list<Pelicula>::iterator it;
    string Guardar="";
    for(it=Peliculas.begin();it!=Peliculas.end();it++){
        Guardar=Guardar+(*it).getID()+","+(*it).getNombre()+","+(*it).getGenero()+","+to_string((*it).getDuracionMin())+","+to_string((*it).getSala())+","+(*it).getHora()+","+to_string((*it).getAsientosDisponibles())+","+to_string((*it).getCapacidadMax())+","+(*it).getClasificacion()+'\n';
    }
    EscribirEnArchivo(Guardar,"Peliculas");
};
void IngresarPeliculas(){
    list<Pelicula>PeliculasCine;
    string ID="", nombre="", genero="", hora="", clasificacion="";
    unsigned duracion=0,sala=0,capacidad=0,cont=0;
    ObtenerDatosPeliculas(PeliculasCine);
    int cantidad=0;
    cout<<"Cantidad de peliculas a ingresar: "<<endl;
    cin>>cantidad;
    cin.ignore();
    for(int i=0;i<cantidad;i++){
        cont=0;
        do{
            if(cont>0)cout<<endl<<"La sala/ID ya se encuentran ocupados "<<endl;
            cout<<i+1<<".Ingrese el ID de la pelicula (no debe contener comas): ";
            getline(cin,ID);
            cout<<endl<<i+1<<".Ingrese la sala de la pelicula: ";
            cin>>sala;
            cin.ignore();
            cont++;
          }
        while(IsInMovieDatabase(PeliculasCine,ID,sala)|| ID.find(",")!=string::npos);
        cont=0;
        do{
            if(cont>0) cout<<endl<<"Datos invalidos, no pueden contener comas"<<endl;
            cout<<endl<<i+1<<".Ingrese el nombre: ";
            getline(cin,nombre);
            cout<<endl<<i+1<<".Ingrese el genero: ";
            getline(cin,genero);
            cout<<endl<<i+1<<".Ingrese la clasificacion: ";
            getline(cin,clasificacion);
            cont++;
        }while(nombre.find(",")!=string::npos||genero.find(",")!=string::npos||clasificacion.find(",")!=string::npos);
        cont=0;
        int hora_=0, min=0;
        string horaMin="", horaA="", minA="";
        unsigned long posM=0, div=0;
        bool band=true;
        do{
            if(cont>0) cout<<endl<<"Hora invalida"<<endl;
            cout<<endl<<i+1<<".Ingrese la hora: ";
            getline(cin,hora);
            posM=hora.find("m");
            if(posM!=string::npos){
                div=hora.find(":");
                if(div!=string::npos){
                   horaA=hora.substr(0,div);
                   minA=hora.substr(div+1,posM-div-2);
                   if(IsNumeric(horaA)&& IsNumeric(minA)){
                       hora_=stoi(horaA);
                       min=stoi(minA);
                       band=false;
                   }

                }
                else{
                    horaMin=hora.substr(0,posM-1);
                    if(IsNumeric(horaMin)){
                        hora_=stoi(horaMin);
                        band=false;
                    }
                }
            }
            cont++;
         }while(band==true || hora_>12 || min>59);

       cout<<endl<<"Ingrese la duracion en minutos: ";
       cin>>duracion;
       cont=0;
       do{
       if(cont>0) cout<<"Capacidad maxima superior a 520 asientos"<<endl;
       cout<<endl<<"Ingrese la capacidad maxima(520 asientos maximo): ";
       cin>>capacidad;
       cin.ignore();
       cont++;
       }while(capacidad>520);
       Pelicula Ing(ID,nombre,genero,duracion,sala,hora,capacidad,clasificacion);
       PeliculasCine.push_back(Ing);

    }
    GuardarPeliculas(PeliculasCine);
}
bool IsInMovieDatabase(list<Pelicula>PeliculasCine, string ID, unsigned sala){
    list<Pelicula>::iterator it;
    for(it=PeliculasCine.begin();it!=PeliculasCine.end();it++){
        if((*it).getID()==ID || (*it).getSala()==sala)
            return true;
    }
    return false;

}
bool IsNumeric(string a){
    string::iterator it;
    for(it=a.begin();it!=a.end();it++){
        if((*it)>57 || (*it)<48)
            return false;
    }
    return true;
}
void GuardarAsientos(list<Pelicula>Peliculas){
    list<Pelicula>::iterator it;
    string guardar="";
    for(it=Peliculas.begin();it!=Peliculas.end();it++){
        map<string, vector<int>>::iterator it2;
        vector<int>::iterator it3;
        guardar=guardar+(*it).getID()+":";
        for(it2=(*it).getAsientos().begin();it2!=(*it).getAsientos().end();it2++){
            guardar=guardar+(*it2).first+",";
            for(it3=(*it2).second.begin();it3!=(*it2).second.end();it3++){
                guardar=guardar+to_string((*it3))+",";
              }
            guardar=guardar+";";
        }
        guardar=guardar+'\n';

    }
    EscribirEnArchivo(guardar,"AsientosDisponibles");
};
void GuardarTiposAsientos(list<Pelicula>Peliculas){
    list<Pelicula>::iterator it;
    vector<string>::iterator it2;
    string guardar="";
    for(it=Peliculas.begin();it!=Peliculas.end();it++){
        guardar=guardar+(*it).getID()+":";
        for(it2=(*it).getGeneral().begin();it2!=(*it).getGeneral().end();it2++){
            guardar=guardar+(*it2)+",";
        }
        guardar=guardar+";";
        for(it2=(*it).getPreferencial().begin();it2!=(*it).getPreferencial().end();it2++){
            guardar=guardar+(*it2)+",";
        }
        guardar=guardar+";";
        for(it2=(*it).getVibroSound().begin();it2!=(*it).getVibroSound().end();it2++){
            guardar=guardar+(*it2)+",";
        }
        guardar=guardar+'\n';
    }
    EscribirEnArchivo(guardar,"TiposAsientos");
}
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
void ReporteVentas();
void ObtenerAsientos(list<Pelicula>&Peliculas);
void ObtenerTiposAsientos(list<Pelicula>&Peliculas);
