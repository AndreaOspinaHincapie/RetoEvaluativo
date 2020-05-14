#ifndef ADMINISTRARUSUARIOS_H
#define ADMINISTRARUSUARIOS_H
#include<map>
#include"manejoarchivos.h"
string BinToString(string Decoded){
    /*
     Función que recibe un string de numeros binarios y lo convierte a su correspondiente string de caracteres.
     Retorna el string convertido
    */
    unsigned int size=unsigned(Decoded.length());
    string result="";
    //Encontrando cantidad de grupos de bytes que forman un caracter:
    unsigned times=size/8, bas=1,lower=0,upper=7, num=0;
    //lower y upper serán los extremos inferior y superior de bits que forman el caracter que se va a obtener.
    for(unsigned int j=1; j<=times;j++){
        bas=1;
        num=0;
        for(unsigned int i=upper;i>lower;i--){
            //Cada caracter se multiplica por 2^potencia según su posición y empezando desde upper hasta lower-
            //potencia empieza en cero. Para esto se usa la variable bas, la cual adquiere el valor del resultado de
            //2^potencia en cada caso. (por tanto tiene valores: 1,2,4,8,16...)
            num=num+(unsigned(Decoded[i]-'0')*bas);
            bas=bas*2;
        }
        //Actualizando límites de lower y upper:
        lower=upper+1;
        upper=upper+8;
        //Convirtiendo el numero a su caracter correspondiente en el código ASCII y concatenandolo a la cadena a retornar:
        result=result+char(num);
    }
    return result;

}
int IntToBin(int num){
    /*
     Función que recibe un número entero en base 10 y lo convierte a binario. Retorna el número binario (tipo entero).
    */
    int residuo=0, mult=1, numBin=0;
    while(num>0){
        residuo=num%2;
        numBin=numBin+residuo*mult;
        num=num/2;
        mult=mult*10;
    }
    return numBin;
}
string StringAbin(string archivo){
    /*
    Función que recibe un string y retorna un string de números binarios.
    Cada caracter del string será convertido a un número binario de 8 bits.
*/
    //Obteniendo tamaño del string:
    unsigned int size= unsigned(archivo.length());
    int codASCII=0, bin=0;
    string Uncoded="";
    for(unsigned int i=0;i<size;i++){
       string binstr="";
       string Eightbytes="";
       //Obteniendo caracter i del string ingresado:
       codASCII=archivo[i];
       //Pasando caracter a entero binario:
       bin=IntToBin(codASCII);
       //Pasando entero binario a string:
       binstr=to_string(bin);
       //Obteniendo tamañano de string binario:
       int sizeind=int(binstr.length());
       //Agregando ceros si binario tiene menos de 8 bits:
       if(sizeind<8){
           for(int j=0; j<(8-sizeind);j++){
               Eightbytes=Eightbytes+"0";
           }
       }
       //Añadiendo caracter en binario a string de retorno:
       Uncoded=Uncoded+ Eightbytes+binstr;

    }
    return Uncoded;
}
string Metodo2Codif(string Uncoded, unsigned n){
    /*
     Función que recibe un string de numeros binarios y un entero n y codifica el string con el segundo método de cofificación,
     el cual consiste en dividir el string en grupos de n bits y desplazar cada bit un espacio a la derecha, de manera que el
     último bit del grupo pase a la posición del primero.
     Al finalizar retorna un string de números binarios codificado.
    */
    unsigned size=unsigned(Uncoded.length());
    string Coded="";
    //Si size%n==0
    unsigned groups=size/n; //Número de grupos de n bits que se pueden formar con el string ingresado.
    if(size%n!=0)
        groups++;
    unsigned lower=0, upper=n-1; //variables que almacenan la primera y última posición del substring de n bits que se está codificando

    for(unsigned int k=1; k<groups+1;k++){
            Coded=Coded+Uncoded[unsigned(upper)];
            for(unsigned int i=lower+1; i<=upper; i++){
                Coded=Coded+Uncoded[i-1];
            }
            lower=upper+1;
            upper=upper+n;

    }
    return Coded;

}

string DecodifMetodo2(string Coded, unsigned n){
    /*
     Función que recibe un string de números binarios codificados y un entero n y retorna el string descodificado con el método
     dos y semilla n.
     Para descodificar se recorre el string Coded en grupos de n bits y cada bit se corre una posición a la izquierda,
     de manera que el bit en primera posición pase a la última.
     Al finalizar se retorna un string con la información descodificada.
    */
    unsigned size=unsigned(Coded.length());
    string Decoded="";
    unsigned int groups=0; //Almacena cantidad de grupos que se pueden formar del string ingresado que tengan n bits.
    //Si size%n==0
        groups=size/n;
        if(size%n!=0){
            groups++;
        }

    unsigned int lower=0, upper=n-1; //Primera y última posición de cada grupo.
    for(unsigned int k=1; k<=groups;k++){
        string last="";
        last=Coded[lower];
        for(unsigned int i=lower+1; i<=upper; i++){
            Decoded=Decoded+Coded[i];
        }
        Decoded=Decoded+last;
        lower=upper+1;
        upper=upper+n;
    }
    return Decoded;


}
string Codificar(unsigned n, string archivo){
    /*
    Función que recibe el numero n y el string a codificar.
    Retorna un string de numeros binarios codificado.
*/
        string Codif="";
        //Codificando con el segundo método:
        Codif=Metodo2Codif(archivo,n);

          return Codif;

}
string Descodificar(unsigned n, string Coded){
    //Función que recibe un entero n, un metodo y un string de números binarios codificados.
        string Decodif="";
        //Descodificando con el método 2 y pasando el número binario a string:
        Decodif=BinToString(DecodifMetodo2(Coded,n));
        return Decodif ;
}

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
    EscribirEnArchivo(Codificar(4,StringAbin(escribir)),"Usuarios");
}
void RegistrarUsuarios(){
    int numUsers=0,cont=0;
    string archivo=LeerArchivo("Usuarios");
    string nombre="", password="";
    map<string,string>Usuarios;
    ObtenerUsuarios(Descodificar(4,archivo),Usuarios);
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
void CambiarContAdmin(){
    string newPass="", OldPass="", Descodif="";
    cout<<"Cambiar contrasena de administrador: "<<endl;
    cout<<"Ingrese la contrasena actual: "<<endl;
    getline(cin,OldPass);
    Descodif=Descodificar(4,LeerArchivo("sudo"));
    if(OldPass==Descodif){
        cout<<"Ingrese la contrasena nueva: "<<endl;
        getline(cin,newPass);
        EscribirEnArchivo(Codificar(4,StringAbin(newPass)),"sudo");
        cout<<"Se ha modificado la contrasena de administrador"<<endl;
    }
    else{
        cout<<"Contrasena equivocada"<<endl;
    }
}
#endif // ADMINISTRARUSUARIOS_H
