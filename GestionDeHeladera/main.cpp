#include <iostream>
#include "Usuario.h"
#include "FuncionesGlobales.h"
#include "Producto.h"
#include "ConsumoProducto.h"
#include "Platillo.h"
#include "ConsumoPlatillo.h"
#include "Receta.h"
#include "ProductoStock.h"

using namespace std;

int main(){

    int opc;
    int validarSalida;

    while(true){
        system("cls");

        cout<<"MENU PRINCIPAL"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. MENU USUARIO"<<endl;
        cout<<"2. MENU PRODUCTO"<<endl;
        cout<<"3. MENU PLATILLO"<<endl;
        cout<<"4. MENU ORIENTACION ALIMENTARIA"<<endl;
        cout<<"5. MENU STOCK DE PRODUCTOS"<<endl;
        cout<<"6. MENU RECETAS"<<endl;
        cout<<"7. MENU CONSUMOS"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: "<<endl;
        cin>>opc;

        system("cls");

        switch(opc){
            case 1: menuUsuario();
                break;
            case 2: menuProducto();
                break;
            case 3: menuPlatillo();
                break;
            case 4: menuOrientacionAlimentaria();
                break;
            case 5:
                    menuStockProductos();
                break;
            case 6: menuRecetas();
                break;
            case 7: menuConsumos();
                break;
            case 0: cout<<"Seguro que desea salir de la aplicacion? "<<endl;
                    cout<<"1 - SI " << endl;
                    cout<<"2 - NO "<< endl;
                    cin>> validarSalida;

                    if(validarSalida==1){
                        return 0;
                    }
                    break;
        }
        cout<<endl;
    }
        cout<<endl;
        system("pause");
        return 0;
}
