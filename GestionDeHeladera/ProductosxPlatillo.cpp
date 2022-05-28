#include<iostream>
# include "ProductosxPlatillo.h"

using namespace std;


int ProductosxPlatillo::getIdPlatillo()
{
    return IdPlatillo;
};
int ProductosxPlatillo::getIdProducto()
{
    return IdProducto;
};
//int getCantidad(){return Cantidad;}
void ProductosxPlatillo::setIdProducto(int i)
{
        IdProducto = i;
};
void ProductosxPlatillo::setIdPlatillo(int i)
{
    IdPlatillo = i;
};

bool ProductosxPlatillo::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("ProductosxPlatillo.dat", "rb");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        exit(1);
    }
    fseek(p, pos*sizeof(ProductosxPlatillo),0);
    leyo=fread(this,sizeof(ProductosxPlatillo),1,p);

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

bool ProductosxPlatillo::GrabarEnDisco()
{
    FILE *p;
    p=fopen("ProductosxPlatillo.dat", "ab");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        exit(1);
    }
    int escribio=fwrite(this, sizeof(ProductosxPlatillo),1,p);
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

int CantidadRegistrosProductosxPlatillos()
{
    FILE *p;
    p=fopen("ProductosxPlatillo.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    size_t bytes;
    int cantidad;

    fseek(p, 0, SEEK_END);
    bytes=ftell(p);

    fclose(p);
    cantidad = bytes/sizeof(ProductosxPlatillo);
    return cantidad;
}

bool nuevoProductoxPlatillo(int idplatillo, int idproducto)
{
    ProductosxPlatillo reg;
    reg = cargarProductosxPlatillo(idplatillo, idproducto);
    bool ok = reg.GrabarEnDisco();
    return ok;
}

ProductosxPlatillo cargarProductosxPlatillo(int idplatillo, int idproducto)
{
        ProductosxPlatillo reg;
        reg.setIdPlatillo(idplatillo);
        reg.setIdProducto(idproducto);

        cout<<endl;
        cout<<endl;
        return reg;
}

void listarProductosxPlatillo()
{
    ProductosxPlatillo aux;
    int cantProductosxPlatillo = CantidadRegistrosProductosxPlatillos();
    cout << "LISTADO DE PRODUCTOS x PLATILLO" << endl;
    cout << "----------------------------------" << endl;
    for(int i=0; i<cantProductosxPlatillo; i++)
    {
        aux.LeerDeDisco(i);
        cout<<aux.getIdPlatillo()  << " " << aux.getIdProducto() <<endl;
    }
    cout << "----------------------------------" << endl;
    cout << "Total: " << cantProductosxPlatillo << " Productos.";
    cout<<endl;
    cout<<endl;
}
