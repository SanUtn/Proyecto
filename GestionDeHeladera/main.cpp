#include <iostream>
#include "Usuario.h"

using namespace std;

int main(){

    int opc;

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
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: "<<endl;
        cin>>opc;

        system("cls");

        switch(opc){
            case 1: menuUsuario();
                break;
            case 2: //menuProducto();
                break;
            case 3: //menuPlatillo();
                break;
            case 4: //menuOrientacionAlimentaria();
                break;
            case 5: //menuStockProductos();
                break;
            case 6: //menuRecetas();
                break;
            case 0: return 0;
                    break;
        }
        cout<<endl;
        system("pause");
    }
        cout<<endl;
        system("pause");
	return 0;
}
