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
        cout<<"El archivo no pudo abrirse"<<endl;
        return false;
    }
    fseek(p, pos*sizeof(ProductoStock),0);
    int escribio=fwrite(this, sizeof(ProductoStock),1,p);
    fclose(p);

    return escribio;
}

///Funciones globales
bool agregarProductoNuevoAlStock(int idProducto)
{
    ProductoStock aux;
    int cantidad;

     cantidad = consultarStock(idProducto);
            if(cantidad == 0)
            {
                aux.setIdProducto(idProducto);
                aux.setStock(1);
                aux.GrabarEnDisco();
                return true;
            }
    return false;
}


bool agregarProductoAlStock(int idProducto)
{
    ProductoStock aux;
    int cantStocks = CantidadRegistrosStock();

        for(int i=0; i<cantStocks; i++)
        {
            aux.LeerDeDisco(i);
            if(aux.getIdProducto()==idProducto)
            {
                aux.setStock(aux.getStock() + 1);
                aux.ModificarArchivo(i);
                return true;
            }
        }
        return false;
}

bool retirarProductoDelStock(int idProducto)
{
    ProductoStock aux;
    Producto reg;
    int cantStocks = CantidadRegistrosStock();
    int cantidad, posicion;

        for(int i=0; i<cantStocks; i++)
        {
            aux.LeerDeDisco(i);
            if(aux.getIdProducto()==idProducto)
            {
                cantidad = aux.getStock();
                posicion=buscarPosicionProducto(aux.getIdProducto());
                if(cantidad == 1 && posicion != -1)
                {
                    reg.setEstadoProducto(false);
                    reg.ModificarArchivo(posicion);
                    aux.setEstadoStock(false);
                    aux.ModificarArchivo(i);
                    return true;
                } else if(cantidad > 1)
                {
                    aux.setStock(cantidad - 1);
                    aux.ModificarArchivo(i);
                    return true;
                }
            }
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



int buscarPosicionProducto(int idP)
{
    Producto aux;
    int cantProductos = CantidadRegistrosProductos();

    for(int i=0; i<cantProductos; i++)
    {
        if(aux.LeerDeDisco(i))
        {
            if(aux.getIdProducto()==idP)
            {
               return i;
            }
        }
    }
    return -1;
}




///consulto en archivo de platillo si existe ese platillo, si existe, busco en productos por platillo sus ingredientes para ir agregando a stock, si no existe en stock el producto retorno true y si existe resto uno a stock de cada producto y retorno true y sino se pudo restar productos retorno false.
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


        if(pla.getIdPlatillo() == idplatillo && pla.getEstadoPlatillo() == true)
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
     int cont=0;
    int cantStocks = CantidadRegistrosStock();
    cout << "LISTADO DE STOCK DE PRODUCTOS" << endl;
    cout << "----------------------------------" << endl;
    for(int i=0; i<cantStocks; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoStock())
        {
            cout<<aux.toString()<<endl;
        } else {
          cont++;
        }
    }
    cout << "----------------------------------" << endl;
    cout << "Total: " << cantStocks - cont << " registros.";
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
