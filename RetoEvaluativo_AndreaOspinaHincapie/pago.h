#ifndef PAGO_H
#define PAGO_H
#include<iostream>
using namespace std;
template <class T>
 void Devuelta (T total, T pago) {
  T valor=pago-total; //Variable que contendrá el valor de dinero que se representará/falta por representar.
  T Denom[10]={50000,20000,10000,5000,2000,1000,500,200,100,50};
  cout<<"La devuelta es: "<<endl;
  for(int i=0; i<=9; i++){
      if(valor/Denom[i]!=0){
        cout<<Denom[i]<<": "<<valor/Denom[i]<<endl;
      }
      valor=valor%Denom[i];

         }
  //Valor faltante:
    cout<<"Falta: "<<valor<<endl;

}

#endif // PAGO_H
