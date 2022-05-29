#include <iostream>
#include "ProductoStock.h"
#include "FuncionesGlobales.h"

using namespace std;


void ProductoStock::Cargar()
{
    //idProducto.Cargar();
    cout<<"Ingrese el stock: ";
    cin>>stock;
}

string ProductoStock::toString()
{
    string cadena;
    cadena = "Producto: " + mostrarNombreProducto(getIdProducto()) + " " " " + " Stock: " + to_string(stock);
    return cadena;
}

bool ProductoStock::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("ProductosStock.dat", "rb");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        exit(1);
    }
    fseek(p, pos*sizeof(ProductoStock),0);
    leyo=fread(this,sizeof(ProductoStock),1,p);

    fclose(p);

    if(leyo)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ProductoStock::GrabarEnDisco()
{
    FILE *p;
    p=fopen("ProductosStock.dat", "ab");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        exit(1);
    }
    int escribio=fwrite(this, sizeof(ProductoStock),1,p);
    fclose(p);

    if(escribio)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
//HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
bool ProductoStock::ModificarArchivo(int pos)
{
    FILE *p;
    p=fopen("ProductosStock.dat", "rb+");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        exit(1);
    }
    fseek(p, pos*sizeof(ProductoStock),0);
    int escribio=fwrite(this, sizeof(ProductoStock),1,p);
    fclose(p);

    if(escribio)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//globales

int CantidadRegistrosStock()
{
    FILE *p;
    p=fopen("ProductosStock.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    size_t bytes;
    int cantidad;

    fseek(p, 0, SEEK_END);
    bytes=ftell(p);

    fclose(p);
    cantidad = bytes/sizeof(ProductoStock);
    return cantidad;
}

void listarStocks()
{
    ProductoStock aux;
    int cantStocks = CantidadRegistrosStock();
    cout << "LISTADO DE PRODUCTOS" << endl;
    cout << "----------------------------------" << endl;
    for(int i=0; i<cantStocks; i++)
    {
        aux.LeerDeDisco(i);
        cout<<aux.toString()<<endl;
    }
    cout << "----------------------------------" << endl;
    cout << "Total: " << cantStocks << " registros.";
    cout<<endl;
    cout<<endl;
}

bool nuevoStock()
{
    ProductoStock reg;
    reg = cargarStock();
    bool ok = reg.GrabarEnDisco();
    return ok;
}

ProductoStock cargarStock()
{
    int idproducto;
    int stock;

    listarProductos();
    cout << "Ingrese el nombre del Producto: ";
    cin >> idproducto;

    cout << "Ingrese el stock: ";
    cin >> stock;

    ProductoStock reg;
    reg.setIdProducto(idproducto);
    reg.setStock(stock);

    cout<<endl;
    cout<<endl;
    system("pause");
    return reg;
}

int EditarStock()
{
    ProductoStock aux;
    int pos=0, idproducto, stock;

    listarProductos();
    cout << "Ingrese el id del Producto: ";
    cin >> idproducto;

    cout << "Ingrese el stock: ";
    cin >> stock;

    while(aux.LeerDeDisco(pos)==1)
    {
        if(aux.getIdProducto() == idproducto)
        {
            aux.setStock(stock);
            aux.ModificarArchivo(pos);
            return pos;
        }
        pos++;
    }
    return -1;
}

void menuStockProductos()
{
    int opc;
    while(true)
    {
        system("cls");

        cout<<"MENU STOCK DE PRODUCTOS"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. AGREGAR STOCK "<<endl;
        cout<<"2. LISTAR STOCK "<<endl;
        cout<<"3. MODIFICAR STOCK"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: "<<endl;
        cin>>opc;

        system("cls");

        switch(opc)
        {
        case 1:
            if(nuevoStock())
            {
                cout<<endl;
                cout<<"STOCK AGREGADO";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO AGREGAR EL STOCK";
                cout<<endl;
                system("pause");
            }
            break;
        case 2:
            listarStocks();
            system("pause");
            break;
        case 3:

            if(EditarStock()!= -1)
            {
                cout<<endl;
                cout<<"STOCK ACTUALIZADO";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO ACTUALIZAR EL STOCK";
                cout<<endl;
                system("pause");
            }
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}
