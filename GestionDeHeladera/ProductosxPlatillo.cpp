#include<iostream>
#include <iomanip>
# include "ProductosxPlatillo.h"
#include "FuncionesGlobales.h"

using namespace std;


int ProductosxPlatillo::getIdPlatillo()
{
    return IdPlatillo;
};
int ProductosxPlatillo::getIdProducto()
{
    return IdProducto;
};

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
        return false;
    }
    fseek(p, pos*sizeof(ProductosxPlatillo),0);
    leyo=fread(this,sizeof(ProductosxPlatillo),1,p);

    fclose(p);

   return leyo;
}

bool ProductosxPlatillo::GrabarEnDisco()
{
    FILE *p;
    p=fopen("ProductosxPlatillo.dat", "ab");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        return false;
    }
    int escribio=fwrite(this, sizeof(ProductosxPlatillo),1,p);
    fclose(p);

   return escribio;
}

//Funciones globales

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

//recibe desde platillo los datos, valida si ya existe ese producto para ese platillo
ProductosxPlatillo cargarProductosxPlatillo(int idplatillo, int idproducto)
{
        ProductosxPlatillo reg;
        reg.setIdPlatillo(idplatillo);

        while( validarProductoEnPlatillo(idplatillo, idproducto)){
            cout << "Producto ya incluido en este platillo, ingrese otro: ";
            cin >> idproducto;
        }

        reg.setIdProducto(idproducto);

        cout<<endl;
        cout<<endl;
        return reg;
}

bool validarProductoEnPlatillo(int idplatillo, int idproducto)
{
    ProductosxPlatillo aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if(aux.getIdPlatillo() == idplatillo && aux.getIdProducto() == idproducto)
        {
            return true;
        }
        pos++;
    }
    return false;
}




void listarProductosxPlatillo()
{
    ProductosxPlatillo aux;
    int cantProductosxPlatillo = CantidadRegistrosProductosxPlatillos();
    bool bandera = false;
    int idPlatillo;

    cout << "LISTADO DE PRODUCTOS x PLATILLO" << endl;
    cout << "----------------------------------" << endl;
    cout << left;
    cout << setw(20) << "PLATILLO ";
    cout << setw(20) << "PRODUCTO" << endl;
    cout<< "----------------------------------" << endl;
    for(int i=0; i<cantProductosxPlatillo; i++)
    {
        aux.LeerDeDisco(i);
        //si el platillo tiene el estado en true muestra los productos por platillo sino no.
        if(buscarPlatillo(aux.getIdPlatillo())){
                //para que muestre una sola vez el nombre, se hace lo de la bandera y lo de guardar el idPlatillo
                if(aux.getIdPlatillo() != idPlatillo){
                    bandera = false;
                }
               if(bandera == false){
                   cout<<endl;
        cout<< setw(20) << mostrarNombrePlatillo(aux.getIdPlatillo());
                    bandera = true;
                    idPlatillo = aux.getIdPlatillo();
               }
                if(idPlatillo == aux.getIdPlatillo()){
                cout<<mostrarNombreProducto(aux.getIdProducto())<<" " " ";
               }else{
                    bandera=false;
               }

        }
    }
    cout<<endl;
    cout<<endl;
}
