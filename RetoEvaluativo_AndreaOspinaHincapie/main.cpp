#include"reporteventas.h"
#include"pelicula.h"
#include"manejoarchivos.h"
#include"administrarusuarios.h"
#include"manejopeliculas.h"
#include"ventaasientos.h"
using namespace std;
int MenuPrincipal();
int MenuAdmin();
void Administrador();
void Usuario();

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
                 ComprarAsiento();
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
        ComprarAsiento();
    }
    else{
        cout<<endl<<"Nombre de usuario o contrasena incorrectos."<<endl;
    }

}



