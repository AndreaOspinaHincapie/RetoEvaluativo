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
bool Is_Registered(string nombre, string password);
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
    cout<<"Bienvenido a CineXolombia, selecciones una de las siguientes opciones:  "<<endl;
    cout<<"Menú de opciones: "<<endl;
    cout<<"1. Soy administrador. "<<endl;
    cout<<"2. Soy usuario. "<<endl;
    cout<<"Ingrese el numero de la opcion o 0 para salir"<<endl;
    cin>>op;
    cout<<"--------------------------------------------------------------------------------"<<endl;
    return op;
}
void Administrador(){

}
void Usuario(){

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
void ObtenerUsuarios(string archivoLeido, map<string,string>& Usuarios);
bool Is_Registered(string nombre, string password);
void GuardarUsuarios(map<string,string>Usuarios);
