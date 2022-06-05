#include <iostream>
#include "ProductoStock.h"
#include "FuncionesGlobales.h"
#include "ProductoStock.h"
#include "ProductosxPlatillo.h"

using namespace std;


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
        return false;
    }
    fseek(p, pos*sizeof(ProductoStock),0);
    leyo=fread(this,sizeof(ProductoStock),1,p);

    fclose(p);

    return leyo;
}

bool ProductoStock::GrabarEnDisco()
{
    FILE *p;
    p=fopen("ProductosStock.dat", "ab");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        return false;
    }
    int escribio=fwrite(this, sizeof(ProductoStock),1,p);
    fclose(p);

    return escribio;
}

//METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
//HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
bool ProductoStock::ModificarArchivo(int pos)
{
    FILE *p;
    p=fopen("ProductosStock.dat", "rb+");
    if(p==NULL)
    {
        return false;
    }
    fseek(p, pos*sizeof(ProductoStock),0);
    int escribio=fwrite(this, sizeof(ProductoStock),1,p);
    fclose(p);

    return escribio;
}

//funciones globales


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

/*bool nuevoStock()
{
    ProductoStock reg;
    reg = cargarStock();
    bool ok = reg.GrabarEnDisco();
    return ok;
}

/*int EditarStock()
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
}*/



bool agregarProductoAlStock(int idProducto)
{
    Producto reg;
    ProductoStock aux;
    int pos=0, cantidad;

    while(reg.LeerDeDisco(pos)==1)
    {

        if(reg.getIdProducto() == idProducto && reg.getEstadoProducto()== true)
        {
            if(consultarStock(reg.getIdProducto())== 0)
            {
                aux.setIdProducto(idProducto);
                aux.setStock(2);//el que ya existe mas el del cliente.
                aux.GrabarEnDisco();
                return true;
            }
            else
            {
                cantidad=consultarStock(reg.getIdProducto());
                aux.setIdProducto(idProducto);
                aux.setStock(cantidad + 1);
                aux.ModificarArchivo(pos);
                return true;
            }
        }
        pos++;
    }
    return false;
}



int consultarStock(int idP)
{
    ProductoStock aux;
    int cantidad=0;
    int cantStocks = CantidadRegistrosStock();

    for(int i=0; i<cantStocks; i++)
    {
        if(aux.LeerDeDisco(i))
        {
            if(aux.getIdProducto()==idP)
            {
                cantidad = aux.getStock();
                return cantidad;
            }
        }
    }
    return cantidad;
}


bool retirarProductoDelStock(int idProducto)
{
    Producto reg;
    ProductoStock aux;
    int pos=0, cantidad, posStock;

    while(reg.LeerDeDisco(pos)==1)
    {

        if(reg.getIdProducto() == idProducto && reg.getEstadoProducto()== true)
        {
            cantidad = consultarStock(reg.getIdProducto());
            if(cantidad == 0)
            {
//si devuelve 0 es que existe el producto porque llego hasta aca pero no figura en stock, como no hay stock es que tengo un solo producto entonces lo elimino.
                reg.setEstadoProducto(false);
                reg.ModificarArchivo(pos);
                return true;
            }
            else
            {
                posStock = 0;
                while(aux.LeerDeDisco(posStock) == 1)
                {
                    if(aux.getIdProducto() == idProducto)
                    {
                        //aux.setIdProducto(idProducto);//se carga setid porque cuando no estaba rompia y traia basura en id.
                        aux.setStock(cantidad - 1);
                        aux.ModificarArchivo(posStock);
                    }
                    posStock++;
                }
            return true;
            }
        }
        pos++;
    }
    return false;
}

bool retirarProductoDelStockDesdePlatillo(int idplatillo)
{
    Platillo pla;
    ProductosxPlatillo pxp;
    ProductoStock psto;

    bool resto;

    int pos=0, cantidad, pos2, pos3;

    while(pla.LeerDeDisco(pos)==1)
    {
        pos2 = 0;


        if(pla.getIdPlatillo() == idplatillo)
        {
            while(pxp.LeerDeDisco(pos2) == 1)
            {
                        pos3 = 0;
                if(pxp.getIdPlatillo() == idplatillo)
                {
                    cantidad = consultarStock(pxp.getIdProducto());
                    if(cantidad == 0)
                    {
                        //reg.setEstadoProducto(false);
                        //reg.ModificarArchivo(pos);
                        resto = true;
                    }
                    else
                    {
                        while(psto.LeerDeDisco(pos3) == 1)
                        {
                            if(psto.getIdProducto() == pxp.getIdProducto())
                            {
                                psto.setIdProducto(psto.getIdProducto());//se carga setid porque cuando no estaba rompia y traia basura en id.
                                psto.setStock(cantidad - 1);
                                psto.ModificarArchivo(pos3);
                                resto =  true;
                            }
                            pos3++;
                        }
                    }
                }
                pos2++;
            }
        }
        pos++;
    }
    if(resto){
        return true;
    }
    return false;
}


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
    cout << "LISTADO DE STOCK DE PRODUCTOS" << endl;
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

void menuStockProductos()
{
    int opc;
    while(true)
    {
        system("cls");

        cout<<"MENU STOCK DE PRODUCTOS"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. LISTAR STOCK "<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: "<<endl;
        cin>>opc;

        system("cls");

        switch(opc)
        {

        case 1:
            listarStocks();
            system("pause");
            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}
