#include"reporteventas.h"
#include"manejoarchivos.h"
#include"administrarusuarios.h"
#include"manejopeliculas.h"
#include"ventaasientos.h"
using namespace std;
int MenuPrincipal();
int MenuAdmin();
void Administrador();
void Usuario();
//Nota1: algunas de las funciones implementadas usan funciones de contenedores implementadas a partir de C++11
/*
 Nota2. Sobre archivos:
 En el momento de la entrega, la contraseña de administrador guardada en sudo.txt era sudocont
 En Peliculas.txt se encuentran guardadas dos películas que ocupan el ID 1 y 2, y la sala 1 y 2.
 En AsientosDisponibles.txt se encuentran las estructuras de las salas de estas dos películas.
 En Usuarios.txt se encuentran registrados dos usuarios:
 1) Nombre: Ana123 Contraseña: luvi2
 2) Nombre: Andre1w Contraseña: lolo
 Y en ReporteVentas.txt se encuentran las ventas del día 14/5/2020
*/
int main()
{
    //Menú principal: Presentación de perfil usuario y perfil administrador
    int option=0;
    option=MenuPrincipal(); //Función que imprime menú principal
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
    cin.ignore();
    cout<<"--------------------------------------------------------------------------------"<<endl;
    while(cin.fail()){
        cin.clear();
        cin.ignore();
        cout<<"Opción no valida. Ingrese el numero o 0 para salir"<<endl;
        cin>>op;
        cin.ignore();
    }
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
    cout<<"5. Cambiar contrasena de administrador "<<endl;
    cout<<"Ingrese el numero de la opcion o 0 para salir"<<endl;
    cin>>op;
    cin.ignore();
    while(cin.fail()){
        cin.clear();
        cin.ignore();
        cout<<"Opción no valida. Ingrese el numero o 0 para salir"<<endl;
        cin>>op;
        cin.ignore();
    }
    cout<<"--------------------------------------------------------------------------------"<<endl;
    return op;
}
void Administrador(){
    /*
     Función para realizar las siguientes funcionalidades en el perfil administrador:
     -Registrar usuarios al servicio por suscripción de reserva de asientos.
     -Ingresar Películas.
     -Ofrecer asientos en taquilla para usuarios no inscritos al sistema.
     -Obtener reporte de ventas diario sobre asientos vendidos y dinero recaudado
     dividido por tipo de asiento.
     -Cambiar contraseña de administrador.
    */
     map<string,string>Usuarios;
     //Inicio de sesión de administrador:
     string passwordIng="",password="";
     cout<<"Ingrese la contrasena de administrador: "<<endl;
     getline(cin,passwordIng);
     password=Descodificar(4,LeerArchivo("sudo")); //Descodificando contraseña y verificando que es correcta
     if(password==passwordIng){
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
                 ReporteVentas();
                 break;
             case 5:
                 CambiarContAdmin();
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
}
void Usuario(){
    /*
     Función para implementar funcionalidades de usuario:
     1)Acceder con nombre de usuario y contraseña.
     2)Comprar asientos.
    */
    map<string,string>Usuarios;
    string user="",password="";
    string archivo=LeerArchivo("Usuarios");
    //Obtener información de base de datos de usuario.
    ObtenerUsuarios(Descodificar(4,archivo),Usuarios);
    //Inicio de sesión:
    cout<<"Inicio de sesion: "<<endl;
    cout<<"Nombre de usuario: ";
    getline(cin,user);
    cout<<endl<<"Contrasena:";
    getline(cin,password);
    if(Is_Registered(user,password,Usuarios)){
        //Comprar asiento si inicio de sesión fue exitoso.
        ComprarAsiento();
    }
    else{
        cout<<endl<<"Nombre de usuario o contrasena incorrectos."<<endl;
    }

}



