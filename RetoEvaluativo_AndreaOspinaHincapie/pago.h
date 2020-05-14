#ifndef PAGO_H
#define PAGO_H
#include<iostream>
using namespace std;
template <class T>
 void Devuelta (T total, T pago) {
    /*
     Plantilla para implementar función que permite devolver una cantidad de dinero con la menor cantidad de billetes y
     monedas posibles de denominaciones almacenadas en Denom.
    */
  T valor=pago-total; //Variable que contendrá el valor de dinero que se representará/falta por representar.
  T Denom[10]={50000,20000,10000,5000,2000,1000,500,200,100,50};
  cout<<"La devuelta en efectivo es: "<<endl;
  for(int i=0; i<=9; i++){
      if(valor/Denom[i]!=0){
        cout<<Denom[i]<<" COP"<<": "<<valor/Denom[i]<<endl;
      }
      valor=valor%Denom[i];

         }
  //Valor faltante:
    cout<<"Falta: "<<valor<<endl;

}

#endif // PAGO_H
