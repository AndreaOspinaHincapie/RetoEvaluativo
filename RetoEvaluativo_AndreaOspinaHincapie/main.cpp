#include <iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;
int MenuPrincipal();
void Administrador();
void Usuario();
string LeerArchivo(string nombre);
void EscribirEnArchivo(string escribir, string nombre);
void ObtenerUsuarios(string archivoLeido, map<string,string>& Usuarios);
bool Is_Registered(string nombre, string password,map<string,string>Usuarios);
void GuardarUsuarios(map<string,string>Usuarios);
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
void Administrador(){
     map<string,string>Usuarios;
     string passwordIng="",password="";
     cout<<"Ingrese la contrasena de administrador: "<<endl;
     cin.ignore();
     getline(cin,passwordIng);
     password=LeerArchivo("sudo");
     if(password==passwordIng+'\n'){
         //MenuAdmin
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
        Write<<escribir+'\n';
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
//Asegurarse que usuarios registrados por admin no tengan : en el nombre.
