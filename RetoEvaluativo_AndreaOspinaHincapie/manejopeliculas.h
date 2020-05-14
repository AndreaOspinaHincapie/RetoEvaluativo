#ifndef MANEJOPELICULAS_H
#define MANEJOPELICULAS_H
#include"manejoarchivos.h"
#include<list>
#include"pelicula.h"
void ObtenerAsientos(map<string,map<string,vector<int>>>&DatosAsientos){
    string datos=LeerArchivo("AsientosDisponibles");
    string filaNombre="";
    vector<int>fila;
    map<string,vector<int>>Sala;
    string ID="";
    unsigned long posPuntos=0, posSalto=0, posLin1=0, posLin2=0,inicial=0;
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
                    fila.push_back((datos.at(i)-'0')*10+(datos.at(i+1)-'0'));
                    i++;
                     }
            }
            Sala.emplace(filaNombre,fila);
            fila.clear();
            posPuntos=datos.find(":",posLin2+1);
            posLin1=datos.find("|",posLin2+1);
            posLin2=datos.find("|",posLin1+1);
        }
        DatosAsientos.emplace(ID,Sala);
        inicial=posSalto+1;
        Sala.clear();
        posSalto=datos.find('\n',inicial);
    }

}

void ObtenerDatosPeliculas(list<Pelicula>&Peliculas){
    string Datos="";
    map<string,map<string,vector<int>>>DatosAsientos;
    ObtenerAsientos(DatosAsientos);
    Datos=LeerArchivo("Peliculas");
    unsigned long posSalto=0, posComa=0, posComaAnt=0, inicial=0;
    posSalto=Datos.find('\n');
    while(posSalto!=string::npos){
        Pelicula PIngresar;
        posComa=Datos.find(",",inicial);
        PIngresar.setID(Datos.substr(inicial,posComa-inicial));
        PIngresar.setAsientos(DatosAsientos[PIngresar.getID()]);
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
        PIngresar.TiposAsientosInicial();
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
}
bool IsInMovieDatabase(list<Pelicula>PeliculasCine, string ID, unsigned sala){
    list<Pelicula>::iterator it;
    for(it=PeliculasCine.begin();it!=PeliculasCine.end();it++){
        if((*it).getID()==ID && (*it).getSala()==sala)
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
    map<string,vector<int>>::iterator it2;
    string guardar="";
    for(it=Peliculas.begin();it!=Peliculas.end();it++){
        guardar=guardar+(*it).getID()+":";
        map<string,vector<int>>Asientos;
        Asientos=(*it).getAsientos();
        for(it2=Asientos.begin();it2!=Asientos.end();it2++){
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
    list<Pelicula>PeliculasCine;
    string ID="", nombre="", genero="", hora="", clasificacion="";
    unsigned duracion=0,sala=0,capacidad=0,cont=0;
    ObtenerDatosPeliculas(PeliculasCine);
    int cantidad=0;
    cout<<"Cantidad de peliculas a ingresar: "<<endl;
    cin>>cantidad;
    cin.ignore();
    for(int i=0;i<cantidad;i++){
        cout<<"Ejemplos de ingreso de hora: 12pm, 7:30am,7pm"<<endl;
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
       cin.ignore();
       cont=0;
       do{
       if(cont>0) cout<<"Capacidad maxima superior a 520 asientos y minimo 60 asientos"<<endl;
       cout<<endl<<"Ingrese la capacidad maxima(520 asientos maximo y 60 minimo): ";
       cin>>capacidad;
       cin.ignore();
       cont++;
       }while(capacidad>520 || capacidad<60);
       Pelicula Ing(ID,nombre,genero,duracion,sala,hora,capacidad,clasificacion);
       PeliculasCine.push_back(Ing);

    }
    GuardarPeliculas(PeliculasCine);
    GuardarAsientos(PeliculasCine);
}


#endif // MANEJOPELICULAS_H
