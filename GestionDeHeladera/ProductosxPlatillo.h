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

    public:
        //getters
        int getIdProducto();
        int getIdPlatillo();

        //setters
        void setIdProducto(int i);
        void setIdPlatillo(int i);


        //metodos
        bool LeerDeDisco(int pos);
        bool GrabarEnDisco();
};


///Funciones globales no pertenecientes a la clase
int CantidadRegistrosProductosxPlatillos();
ProductosxPlatillo cargarProductosxPlatillo(int idplatillo, int idproducto);
bool nuevoProductoxPlatillo(int idplatillo, int idproducto);
void listarProductosxPlatillo();
bool validarProductoEnPlatillo(int idplatillo, int idproducto);
int CantidadProductosxPlatillo(int idplatillo);


#endif // PRODUCTOSXPLATILLO_H_INCLUDED
