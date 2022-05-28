#ifndef PRODUCTOSXPLATILLO_H_INCLUDED
#define PRODUCTOSXPLATILLO_H_INCLUDED
# include<cstdlib>
# include<cstring>
# include<string>
#include "Fecha.h"
#include "Producto.h"
using namespace std;

class ProductosxPlatillo{
    private:
    int IdPlatillo;
    int IdProducto;
    //int Cantidad;

    public:
        int getIdProducto();
        int getIdPlatillo();
        //int getCantidad(){return Cantidad;}
        void setIdProducto(int i);
        void setIdPlatillo(int i);
        //void setCantidad(int c){Cantidad = c;}

        //metodos
        bool LeerDeDisco(int pos);
        bool GrabarEnDisco();
};

//Funciones globales no pertenecientes a la clase
int CantidadRegistrosProductosxPlatillos();
ProductosxPlatillo cargarProductosxPlatillo(int idplatillo, int idproducto);
bool nuevoProductoxPlatillo(int idplatillo, int idproducto);
void listarProductosxPlatillo();
#endif // PRODUCTOSXPLATILLO_H_INCLUDED
