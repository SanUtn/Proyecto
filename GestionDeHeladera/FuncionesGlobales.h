#ifndef FUNCIONESGLOBALES_H_INCLUDED
#define FUNCIONESGLOBALES_H_INCLUDED
#include "ConsumoProducto.h"



 void menuConsumos(){
   int opc;
    while(true){
        system("cls");

        cout<<"MENU CONSUMOS"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. AGREGAR CONSUMO PRODUCTO "<<endl;
        cout<<"2. LISTAR CONSUMO PRODUCTO"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: "<<endl;
        cin>>opc;

        system("cls");

        switch(opc){
            case 1:   if(nuevoConsumoProducto()){
                            cout<<endl;
                            cout<<"CONSUMO AGREGADO";
                        }else {
                             cout<<endl;
                            cout<<"NO SE PUDO AGREGAR EL CONSUMO";
                        }
                break;
            case 2: listarConsumosPoductos();
                break;
            case 0: return;
                    break;
        }
        cout<<endl;
    }
  }

















#endif // FUNCIONESGLOBALES_H_INCLUDED
