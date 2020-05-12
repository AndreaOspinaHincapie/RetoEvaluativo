#ifndef MANEJOPELICULAS_H
#define MANEJOPELICULAS_H
#include"manejoarchivos.h"
#include<list>
#include"pelicula.h"
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


#endif // MANEJOPELICULAS_H
