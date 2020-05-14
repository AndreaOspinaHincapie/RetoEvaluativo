#ifndef MANEJOPELICULAS_H
#define MANEJOPELICULAS_H
#include"manejoarchivos.h"
#include<list>
#include"pelicula.h"
void ObtenerAsientos(map<string,map<string,vector<int>>>&DatosAsientos){
    /*
     Función que obtiene la información de AsientosDisponibles.txt y la retorna por referencia en un mapa con key string y value
     otro mapa con key string y value vector de enteros.
     AsientosDisponibles.txt tiene la siguiente estructura:
     ID:A|1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20|:B|1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20|\n;
     Ejemplo de sala con dos filas y una película ID.
    */
    string datos=LeerArchivo("AsientosDisponibles");
    string filaNombre="";
    vector<int>fila; //vector que almacena los asientos de la fila.
    map<string,vector<int>>Sala; //mapa que almacena estructura de una sala
    string ID="";
    unsigned long posPuntos=0, posSalto=0, posLin1=0, posLin2=0,inicial=0;
    //Procedimiento para obtener los datos:
    posSalto=datos.find('\n');
    posPuntos=datos.find(":",inicial);
    ID=datos.substr(inicial,posPuntos-inicial);
    posLin1=datos.find("|",posLin2+1);
    posLin2=datos.find("|",posLin1+1);
    while(posSalto!=string::npos){
        while(posLin1<posSalto){
            if(DatosAsientos.size()>=1 && Sala.size()<1){
              posPuntos=datos.find(":",posPuntos+1);
              ID=datos.substr(inicial,posPuntos-inicial);
              filaNombre=datos.substr(posPuntos+1,posLin1-posPuntos-1);
            }
            else{
              filaNombre=datos.substr(posPuntos+1,posLin1-posPuntos-1);
            }

            for(unsigned long i=posLin1+1;i<posLin2;i++){
                if((datos.at(i)!=',' && datos.at(i+1)==',' )||(datos.at(i)!=',' && datos.at(i+1)=='|') ) fila.push_back(datos.at(i)-'0');
                else if(datos.at(i)!=','&& datos.at(i+1)!=',' && datos.at(i+1)!='|'){
                    fila.push_back((datos.at(i)-'0')*10+(datos.at(i+1)-'0')); //Creando fila de asientos
                    i++;
                     }
            }
            Sala.emplace(filaNombre,fila); //Agregando información a mapa de cada sala
            fila.clear();
            posPuntos=datos.find(":",posLin2+1);
            posLin1=datos.find("|",posLin2+1);
            posLin2=datos.find("|",posLin1+1);
        }
        DatosAsientos.emplace(ID,Sala); //Añadiendo la sala actual al mapa de todas las salas del cine.
        inicial=posSalto+1;
        Sala.clear();
        posSalto=datos.find('\n',inicial);
    }

}

void ObtenerDatosPeliculas(list<Pelicula>&Peliculas){
    /*
       Función que obtiene los datos de Peliculas.txt y los asigna al Objeto película con el
       constructor que no recibe parámetros para Inicializar la estructura de las salas según los datos
       leidos de AsientosDisponibles.txt.
       Retorna por referencia la lista de objetos Pelicula.
    */
    string Datos="";
    map<string,map<string,vector<int>>>DatosAsientos;
    ObtenerAsientos(DatosAsientos);
    Datos=LeerArchivo("Peliculas");
    unsigned long posSalto=0, posComa=0, posComaAnt=0, inicial=0;
    posSalto=Datos.find('\n');
    while(posSalto!=string::npos){
        Pelicula PIngresar;
        posComa=Datos.find(",",inicial);
        //Obteniendo ID
        PIngresar.setID(Datos.substr(inicial,posComa-inicial));
        //Obteniendo estructura de sala con ID leída
        PIngresar.setAsientos(DatosAsientos[PIngresar.getID()]);
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        //Obteniendo nombre de película
        PIngresar.setNombre(Datos.substr(posComaAnt,posComa-posComaAnt));
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        //Obteniendo género de película
        PIngresar.setGenero(Datos.substr(posComaAnt,posComa-posComaAnt));
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        //Obteniendo duración de la película
        PIngresar.setDuracionMin(unsigned(stoi(Datos.substr(posComaAnt,posComa-posComaAnt))));
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        //Obteniendo sala de película.
        PIngresar.setSala(unsigned(stoi(Datos.substr(posComaAnt,posComa-posComaAnt))));
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        //Obteniendo hora de película
        PIngresar.setHora(Datos.substr(posComaAnt,posComa-posComaAnt));
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        //Obteniendo cantidad de asientos disponibles
        PIngresar.setAsientosDisponibles(unsigned(stoi(Datos.substr(posComaAnt,posComa-posComaAnt))));
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        //Obteniendo capacidad máxima
        PIngresar.setCapacidadMax(unsigned(stoi(Datos.substr(posComaAnt,posComa-posComaAnt))));
        //Obteniendo tipos de asientos a partir de cantidad de filas:
        PIngresar.TiposAsientosInicial();
        posComaAnt=posComa+1;
        posComa=Datos.find(",",posComaAnt);
        //Obteniendo clasificación de la película
        PIngresar.setClasificacion(Datos.substr(posComaAnt,posSalto-posComaAnt));
        Peliculas.push_back(PIngresar); //Añadiendo a lista de películas
        inicial=posSalto+1;
        posSalto=Datos.find('\n',inicial);
    }

}
void GuardarPeliculas(list<Pelicula>Peliculas){
    /*
     Función que recibe lista de películas y las almacena en Peliculas.txt
     según el formato:
     ID,nombre,género,duración(minutos),sala,hora,Asientos Disponibles, capacidad máxima,clasificación\n
    */
    list<Pelicula>::iterator it;
    string Guardar="";
    for(it=Peliculas.begin();it!=Peliculas.end();it++){
        Guardar=Guardar+(*it).getID()+","+(*it).getNombre()+","+(*it).getGenero()+","+to_string((*it).getDuracionMin())+","+to_string((*it).getSala())+","+(*it).getHora()+","+to_string((*it).getAsientosDisponibles())+","+to_string((*it).getCapacidadMax())+","+(*it).getClasificacion()+'\n';
    }
    EscribirEnArchivo(Guardar,"Peliculas");
}
bool IsInMovieDatabase(list<Pelicula>PeliculasCine, string ID, unsigned sala){
    /*
     Función que recibe la lista de películas, una ID y una sala y verifica que se encuentre en la lista de películas.
     Retorna true si la encuentra y falso en caso contrario.
    */
    list<Pelicula>::iterator it;
    for(it=PeliculasCine.begin();it!=PeliculasCine.end();it++){
        if((*it).getID()==ID && (*it).getSala()==sala)
            return true;
    }
    return false;

}
bool IsNumeric(string a){
    /*
     Función que recibe un string y retorna true si todos sus caracteres son numéricos, de lo
     contrario retorna false.
    */
    string::iterator it;
    for(it=a.begin();it!=a.end();it++){
        if((*it)>57 || (*it)<48)
            return false;
    }
    return true;
}
void GuardarAsientos(list<Pelicula>Peliculas){
    /*
     Función que recibe la lista de Películas y guarda la estructura de asientos de cada Película en AsientosDisponibles.txt
     según  la siguiente estructura:
     ID:A|1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20|:B|1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20|\n;
     Ejemplo de sala con dos filas y una película ID.

    */
    list<Pelicula>::iterator it;
    map<string,vector<int>>::iterator it2;
    string guardar="";
    for(it=Peliculas.begin();it!=Peliculas.end();it++){
        //Recorriendo lista
        guardar=guardar+(*it).getID()+":";
        map<string,vector<int>>Asientos;
        Asientos=(*it).getAsientos();
        for(it2=Asientos.begin();it2!=Asientos.end();it2++){
            //Recorriendo mapa de asientos de cada película
            guardar=guardar+(*it2).first+"|";
            vector<int>aPfila;
            aPfila=(*it2).second;
            unsigned long size=aPfila.size();
            for(unsigned long i=0;i<size;i++){
                if(i!=size-1) guardar=guardar+to_string(aPfila.at(i))+",";
                else guardar=guardar+to_string(aPfila.at(i))+"|:";
            }
        }
        guardar=guardar+'\n';

    }
    EscribirEnArchivo(guardar,"AsientosDisponibles");
}

void IngresarPeliculas(){
    /*
     Función que implementa la funcionalidad de ingresar películas del perfil administrador
    */
    list<Pelicula>PeliculasCine; //Lista de películas del cine
    string ID="", nombre="", genero="", hora="", clasificacion="";
    unsigned duracion=0,sala=0,capacidad=0,cont=0;
    ObtenerDatosPeliculas(PeliculasCine); //obteniendo películas de la base de datos
    int cantidad=0;
    cout<<"Cantidad de peliculas a ingresar: "<<endl;
    cin>>cantidad;
    cin.ignore();
    for(int i=0;i<cantidad;i++){
        cout<<"Ejemplos de ingreso de hora: 12pm, 7:30am,7pm"<<endl;
        cont=0;
        do{
            //Ingreso de sala y ID
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
            //Ingreso de nombre, genero y clasificación
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
            //Ingreso de hora:
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

        //Ingresando duracio en minutos de la pelicula.
           cout<<endl<<"Ingrese la duracion en minutos: ";
           cin>>duracion;
           cin.ignore();
           while(cin.fail()){
               cin.clear();
               cin.ignore();
               cout<<"Duración no válida. Ingrese solo enteros positivos"<<endl;
               cin>>duracion;
           }
       cont=0;
       do{
           //Obteniendo capacidad maxima.
       if(cont>0) cout<<"Capacidad maxima superior a 520 asientos y minimo 60 asientos"<<endl;
       cout<<endl<<"Ingrese la capacidad maxima(520 asientos maximo y 60 minimo): ";
       cin>>capacidad;
       cin.ignore();
       cont++;
       }while(capacidad>520 || capacidad<60);
       Pelicula Ing(ID,nombre,genero,duracion,sala,hora,capacidad,clasificacion); //Constructor que recibe parámetros para primer
       //ingreso de película y crear estructura de sala
       PeliculasCine.push_back(Ing);  //Guardando película en lista de películas

    }
    GuardarPeliculas(PeliculasCine); //Guardando información de películas
    GuardarAsientos(PeliculasCine); //Guardando información de estructura de las salas.
}


#endif // MANEJOPELICULAS_H
