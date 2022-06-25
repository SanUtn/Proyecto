#include <iostream>
#include "rlutil.h"
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
        rlutil::locate(34, 4);
        rlutil::setColor(rlutil::LIGHTMAGENTA);
        cout<<"--------------------------------------------------"<<endl;
        rlutil::locate(52, 5);
        cout<<"MENU PRINCIPAL"<<endl;
        rlutil::locate(34, 6);
        cout<<"--------------------------------------------------"<<endl;
        rlutil::setColor(rlutil::GREEN);
        rlutil::locate(47, 8);
        cout<<"1. MENU USUARIO"<<endl;
        rlutil::locate(47, 9);
        cout<<"2. MENU PRODUCTO"<<endl;
        rlutil::locate(47, 10);
        cout<<"3. MENU PLATILLO"<<endl;
        rlutil::locate(47, 11);
        cout<<"4. MENU ORIENTACION ALIMENTARIA"<<endl;
        rlutil::locate(47, 12);
        cout<<"5. MENU STOCK DE PRODUCTOS"<<endl;
        rlutil::locate(47, 13);
        cout<<"6. MENU RECETAS"<<endl;
        rlutil::locate(47, 14);
        cout<<"7. MENU CONSUMOS"<<endl;
        rlutil::locate(47, 15);
        cout<<"8. MENU REPORTES"<<endl;
        rlutil::locate(47, 16);
        cout<<"-------------------------------"<<endl;
        rlutil::locate(47, 17);
        cout<<"0. SALIR"<<endl;
        rlutil::locate(47, 18);
        cout<<"-------------------------------"<<endl;
        cout<<endl;

        rlutil::locate(47, 20);
        rlutil::setColor(rlutil::LIGHTBLUE);
        cout<<"OPCION: ";
        cin>>opc;


        rlutil::setColor(rlutil::BROWN);
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
            case 8:
                menuReportes();
                break;
            case 0: rlutil::locate(35, 5);
                    rlutil::setColor(rlutil::RED);
                cout<<"Seguro que desea salir de la aplicacion? "<<endl;
                    rlutil::locate(48, 6);
                    cout<<"1 - SI " << endl;
                    rlutil::locate(48, 7);
                    cout<<"2 - NO " <<endl;
                    rlutil::locate(48, 9);
                    cout<<"Opcion: ";
                    cin>> validarSalida;

                    rlutil::setColor(rlutil::BROWN);
                    if(validarSalida==1){
                        return 0;
                    }
                    break;
        }
        cout<<endl;
    }
        cout<<endl;
        rlutil::locate(48, 12);
        system("pause");
        return 0;
}
