#ifndef ADMINISTRARUSUARIOS_H
#define ADMINISTRARUSUARIOS_H
#include<map>
#include"manejoarchivos.h"
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

          if(cont>0){
              if(Usuarios.count(nombre)==1) cout<<endl<<"el nombre de usuario de ya se encuentra en uso."<<endl;
              else cout<<"Nombre de usuario invalido"<<endl;
          }
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
#endif // ADMINISTRARUSUARIOS_H
