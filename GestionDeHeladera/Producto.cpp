#include <iostream>
#include "Producto.h"

using namespace std;


string Producto::getNombreProducto()
{
    string nombreProductos;
    nombreProductos = nombreProducto;
    return nombreProductos;
}

string Producto::toString()
{
    string cadena;
    cadena = "Id del producto: " + to_string(idProducto) + " " " " + " Nombre del Producto: " + nombreProducto;
    return cadena;
}


bool Producto::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("Productos.dat", "rb");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        exit(1);
    }
    fseek(p, pos*sizeof(Producto),0);
    leyo=fread(this,sizeof(Producto),1,p);

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

bool Producto::GrabarEnDisco()
{
    FILE *p;
    p=fopen("Productos.dat", "ab");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        exit(1);
    }
    int escribio=fwrite(this, sizeof(Producto),1,p);
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
bool Producto::ModificarArchivo(int pos)
{
    FILE *p;
    p=fopen("Productos.dat", "rb+");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        exit(1);
    }
    fseek(p, pos*sizeof(Producto),0);
    int escribio=fwrite(this, sizeof(Producto),1,p);
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

/// Funciones globales para gestionar Producto
bool nuevoProducto()
{
    Producto reg;
    reg = cargarProducto();
    bool ok = reg.GrabarEnDisco();
    return ok;
}

int CantidadRegistrosProductos()
{
    FILE *p;
    p=fopen("Productos.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    size_t bytes;
    int cantidad;

    fseek(p, 0, SEEK_END);
    bytes=ftell(p);

    fclose(p);
    cantidad = bytes/sizeof(Producto);
    return cantidad;
}

Producto cargarProducto()
{
    int id;
    string nombre;
    bool estado = true;

    id = CantidadRegistrosProductos()+1;

    cout << "Ingrese el nombre del Producto: ";
    cin >> nombre;

    Producto reg;
    reg.setIdProducto(id);
    reg.setNombreProducto(nombre);
    reg.setEstadoProducto(estado);
    cout<<endl;
    cout<<endl;
    system("pause");
    return reg;
}


void listarProductos()
{
    Producto aux;
    int cantProductos = CantidadRegistrosProductos();
    cout << "LISTADO DE PRODUCTOS" << endl;
    cout << "----------------------------------" << endl;
    for(int i=0; i<cantProductos; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoProducto())
        {
            cout<<aux.toString()<<endl;
        }
    }
    cout << "----------------------------------" << endl;
    cout << "Total: " << cantProductos << " Productos.";
    cout<<endl;
    cout<<endl;
    //system("pause");
}


void menuProducto()
{
    int opc;
    while(true)
    {
        system("cls");

        cout<<"MENU PRODUCTO"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. AGREGAR PRODUCTO "<<endl;
        cout<<"2. LISTAR PRODUCTOS "<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: "<<endl;
        cin>>opc;

        system("cls");

        switch(opc)
        {
        case 1:
            if(nuevoProducto())
            {
                cout<<endl;
                cout<<"PRODUCTO AGREGADO";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO AGREGAR EL PRODUCTO";
                cout<<endl;
                system("pause");
            }
            break;
        case 2:
            listarProductos();
            system("pause");
            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}
