#include <iostream>
#include "rlutil.h"
#include "ProductoStock.h"
#include "FuncionesGlobales.h"
#include "ProductoStock.h"
#include "ProductosxPlatillo.h"
#include <iomanip>
using namespace std;


string ProductoStock::toString()
{
    string cadena;
    cadena = "Producto: " + mostrarNombreProducto(getIdProducto()) + " " " " + " Stock: " + to_string(stock);
    return cadena;
}

void ProductoStock::toList()
{
    rlutil::setColor(rlutil::LIGHTCYAN);
    cout << left;
    cout << "\t";
    cout << setw(25) << mostrarNombreProducto(getIdProducto());
    cout << setw(20) << to_string(stock)<<endl;
    rlutil::setColor(rlutil::BROWN);
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
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
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
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    fseek(p, pos*sizeof(ProductoStock),0);
    int escribio=fwrite(this, sizeof(ProductoStock),1,p);
    fclose(p);

    return escribio;
}




///Funciones globales
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

bool agregarProductoNuevoAlStock(int idProducto)
{
    ProductoStock aux;
    int cantidad;

    cantidad = consultarStock(idProducto);
    if(cantidad == 0)
    {
        aux.setIdProducto(idProducto);
        aux.setStock(1);
        aux.setEstadoStock(true);
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
        if(aux.getIdProducto()==idProducto && aux.getEstadoStock()== true)
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
    int cantStocks = CantidadRegistrosStock();
    int cantidad, posicion;

    for(int i=0; i<cantStocks; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getIdProducto()==idProducto && aux.getEstadoStock() == true)
        {
            cantidad = aux.getStock();

            if(cantidad > 0)
            {
                aux.setStock(cantidad - 1);
                aux.ModificarArchivo(i);
                return true;
            }
            else
            {
                return false;
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
            if(aux.getIdProducto()==idP && aux.getEstadoStock()==true)
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




///consulta en archivo de platillo si existe ese platillo, si existe, busca en productos por platillo sus ingredientes y los carga en un vector para ir sacando de stock de productos cada uno.
bool retirarProductoDelStockDesdePlatillo(int idplatillo)
{
    Platillo pla;
    ProductoStock aux;
    bool bandera = false;

    int *vProductos;
    int cantReg = CantidadProductosxPlatillo(idplatillo);
    vProductos = new int [cantReg];

    int cantStocks = CantidadRegistrosStock();

    if(vProductos==NULL)
    {
        return false;
    }


    if(buscarPlatillo(idplatillo))
    {
        //lena el vector con los productos del platillo
        buscarProductosXPlatillo(idplatillo, vProductos, cantReg);

        for(int i=0; i<cantStocks; i++)
        {
            aux.LeerDeDisco(i);

            for(int j=0; j<cantReg; j++)
            {
                if(aux.getIdProducto()== vProductos[j])
                {

                    if(aux.getStock() > 0)
                    {
                        aux.setStock(aux.getStock() - 1);
                        aux.ModificarArchivo(i);
                        bandera = true;
                    }
                    else
                    {
                        bandera = false;
                        return bandera;
                    }
                }
            }
        }
    }
    delete vProductos;
    return bandera;
}

bool buscarPlatillo(int idP)
{
    Platillo aux;
    int cantPlatillos = CantidadRegistrosPlatillo();

    for(int i=0; i<cantPlatillos; i++)
    {
        if(aux.LeerDeDisco(i))
        {
            if(aux.getIdPlatillo()==idP && aux.getEstadoPlatillo()==true)
            {
                return true;
            }
        }
    }
    return false;
}

void buscarProductosXPlatillo(int idP, int *vProductos, int tam)
{
    ProductosxPlatillo aux;
    int pos = 0;
    bool bandera;
    ponerEnCeroElVector(vProductos,tam);

    for(int i=0; i<tam; i++)
    {
        bandera = false;
        while(aux.LeerDeDisco(pos) && bandera == false)
        {
            if(aux.getIdPlatillo()==idP)
            {
                vProductos[i] = aux.getIdProducto();
                bandera = true;
                //que sea diferente al ya guardado
            }
            pos++;
        }
    }

}

void ponerEnCeroElVector(int *vProductos, int tam)
{
    for(int i=0; i<tam; i++)
    {
        vProductos[i] = 0;
    }
}


bool retirarProductoDelStockConsumoProducto(int idproducto)
{
    ProductoStock aux;
    int cantStocks = CantidadRegistrosStock();
    int cantidad;
    bool bandera = false;

    if(buscarProducto(idproducto))
    {
        for(int i=0; i<cantStocks; i++)
        {
            aux.LeerDeDisco(i);
            if(aux.getIdProducto()== idproducto && aux.getEstadoStock() == true)
            {
                cantidad = aux.getStock();

                if(cantidad > 0)
                {
                    aux.setStock(cantidad - 1);
                    aux.ModificarArchivo(i);
                    bandera = true;
                }
                else
                {
                    bandera = false;
                    return bandera;
                }
            }

        }
    }
    return bandera;
}


bool buscarProducto(int idproducto)
{
    Producto aux;
    int cantProductos = CantidadRegistrosProductos();

    for(int i=0; i<cantProductos; i++)
    {
        if(aux.LeerDeDisco(i))
        {
            if(aux.getIdProducto() == idproducto && aux.getEstadoProducto()==true)
            {
                return true;
            }
        }
    }
    return false;
}

void listarStocks()
{
    ProductoStock aux;
    int cont=0;
    int cantStocks = CantidadRegistrosStock();

    rlutil::setColor(rlutil::MAGENTA);
    cout<<endl;
    cout<<endl;
    cout << left;
    cout << setw(8) << "\t";
    cout << "STOCK DE PRODUCTOS" << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "------------------------------" << endl;
    cout << left;
    cout << "\t";
    cout << setw(25) << "PRODUCTO";
    cout << setw(20) << "STOCK" << endl;
    cout << "\t" << "------------------------------" << endl;

    for(int i=0; i<cantStocks; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoStock())
        {
            aux.toList();
        }
        else
        {
            cont++;
        }
    }
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "------------------------------" << endl;
    cout << "\t" << "Total: " << cantStocks - cont << " registros.";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
}

void menuStockProductos()
{
    int opc;
    while(true)
    {
        system("cls");
        rlutil::locate(50, 5);
        rlutil::setColor(rlutil::CYAN);
        cout<<"MENU STOCK DE PRODUCTOS"<<endl;
        rlutil::locate(40, 6);
        cout<<"-----------------------------------------"<<endl;
        rlutil::setColor(rlutil::LIGHTCYAN);
        rlutil::locate(52,8);
        cout<<"1. LISTAR STOCK "<<endl;
        rlutil::locate(52,9);
        cout<<"---------------"<<endl;
        rlutil::locate(52,10);
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        rlutil::locate(52,13);
        rlutil::setColor(rlutil::DARKGREY);
        cout<<"OPCION: ";
        cin>>opc;

        rlutil::setColor(rlutil::BROWN);
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
