#include <iostream>
#include "FuncionesGlobales.h"

using namespace std;

void menuConsumos()
{
    int opc;
    while(true)
    {
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

        cout<<"OPCION: ";
        cin>>opc;

        system("cls");

        switch(opc)
        {
        case 1:
            if(nuevoConsumoProducto())
            {
                cout<<endl;
                cout<<"CONSUMO AGREGADO";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO AGREGAR EL CONSUMO";
                cout<<endl;
                system("pause");
            }
            break;
        case 2:
            listarConsumosPoductos();
            break;
        case 3: menuSugerenciasPlatillos();
            break;
        case 4:
            listarConsumosPlatillo();
            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}


string mostrarOrientacionAlimentaria(int id)
{
    OrientacionAlimentaria aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if (aux.getIdOrientacionAlimentaria() == id)
        {
            return aux.getDescripcion();
        }
        pos++;
    }
}

string mostrarNombreProducto(int id)
{
    Producto aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if (aux.getIdProducto() == id)
        {
            return aux.getNombreProducto();
        }
        pos++;
    }
}

string mostrarNombrePlatillo(int id){
    Platillo aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if (aux.getIdPlatillo() == id)
        {
            return aux.getNombrePlatillo();
        }
        pos++;
    }
}

string mayuscula(string cadena) {
  for (int i = 0; i < cadena.length(); i++) cadena[i] = toupper(cadena[i]);
  return cadena;
}
