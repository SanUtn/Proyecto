#ifndef FUNCIONESGLOBALES_H_INCLUDED
#define FUNCIONESGLOBALES_H_INCLUDED
#include "ConsumoProducto.h"
#include "ConsumoPlatillo.h"


 void menuConsumos(){
   int opc;
    while(true){
        system("cls");

        cout<<"MENU CONSUMOS"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. AGREGAR CONSUMO PRODUCTO "<<endl;
        cout<<"2. LISTAR CONSUMO PRODUCTOS"<<endl;
        cout<<"3. AGREGAR CONSUMO PLATILLO "<<endl;
        cout<<"4. LISTAR CONSUMO PLATILLOS"<<endl;
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
                            cout<<endl;
                            system("pause");
                        }else {
                             cout<<endl;
                            cout<<"NO SE PUDO AGREGAR EL CONSUMO";
                            cout<<endl;
                            system("pause");
                        }
                break;
            case 2: listarConsumosPoductos();
                break;
            case 3:   if(nuevoConsumoPlatillo()){
                            cout<<endl;
                            cout<<"CONSUMO AGREGADO";
                            cout<<endl;
                            system("pause");
                        }else {
                             cout<<endl;
                            cout<<"NO SE PUDO AGREGAR EL CONSUMO";
                            cout<<endl;
                            system("pause");
                        }
                break;
            case 4: listarConsumosPlatillo();
                break;
            case 0: return;
                    break;
        }
        cout<<endl;
    }
  }

   /*void mostrarOrientacionAlimentaria(){
        OrientacionAlimentaria aux;
        int cantOA = CantidadRegistrosOA();
    cout << "LISTADO DE ORIENTACION ALIMENTARIA" << endl;
    cout << "----------------------------------" << endl;
        for(int i=0; i<cantOA; i++){
            aux.LeerDeDisco(i);
            if(aux.getEstadoOrientacion()){
                cout<<aux.toString()<<endl;
            }
        }
        cout<<endl;
        cout<<endl;
        //system("pause");
    }*/













#endif // FUNCIONESGLOBALES_H_INCLUDED
