#ifndef PRODUCTOSTOCK_H_INCLUDED
#define PRODUCTOSTOCK_H_INCLUDED
#include "Producto.h"

class ProductoStock
{

private:
    int idProducto;
    int stock;
    bool estadoStock;

public:
    //getters
    int getIdProducto(){return idProducto;}
    int getStock(){return stock;}
    int getEstadoStock(){return estadoStock;}

    //setters
    void setIdProducto(int id){idProducto=id;}
    void setStock(int s){stock=s;}
    void setEstadoStock(int es){estadoStock=es;}

    //metodos
    string toString();
    bool LeerDeDisco(int pos);
    bool GrabarEnDisco();
    bool ModificarArchivo(int pos);
    void toList();

};

    //funciones globales que no pertenecen a la clase.
    bool agregarProductoNuevoAlStock(int idProducto);
    bool agregarProductoAlStock(int idProducto);
    int consultarStock(int idP);
    int buscarPosicionProducto(int idP);
    bool retirarProductoDelStock(int idProducto);
    int CantidadRegistrosStock();
    void listarStocks();
    void menuStockProductos();
    bool retirarProductoDelStockDesdePlatillo(int idplatillo);
    bool buscarPlatillo(int idP);
    void buscarProductosXPlatillo(int idP, int *vProductos, int tam);
    void ponerEnCeroElVector(int *vProductos, int tam);
    bool retirarProductoDelStockConsumoProducto(int idproducto);
    bool buscarProducto(int idproducto);




#endif // PRODUCTOSTOCK_H_INCLUDED
