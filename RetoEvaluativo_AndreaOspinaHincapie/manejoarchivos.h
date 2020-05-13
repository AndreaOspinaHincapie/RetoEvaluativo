#ifndef MANEJOARCHIVOS_H
#define MANEJOARCHIVOS_H
#include<fstream>
#include<string>
#include<iostream>
using namespace std;
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
            Read.open("../RetoEvaluativo_AndreaOspinaHincapie/"+nombre+".txt");
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
                cout<<"Error al abrir archivo."<<endl;
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
        Write.open("../RetoEvaluativo_AndreaOspinaHincapie/"+nombre+".txt");
        //Asegurando que el archivo se abra correctamente:
        if(!Write.is_open()){
            throw '1';
        }
        //Escribiendo en el archivo:
        Write<<escribir;
        //Cerrando el archivo:
        Write.close();

    } catch (char c) {
        if(c=='1'){
            cout<<"Error al abrir archivo de escritura"<<endl;
        }

    }catch(exception ex){
        cout<<ex.what()<<endl;
    }

}
#endif // MANEJOARCHIVOS_H
