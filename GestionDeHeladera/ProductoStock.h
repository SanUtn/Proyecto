#ifndef PRODUCTOSTOCK_H_INCLUDED
#define PRODUCTOSTOCK_H_INCLUDED
#include "Producto.h"

class ProductoStock
{

private:
    int idProducto;
    int stock;

public:
    //getters
    int getIdProducto(){return idProducto;}
    int getStock(){return stock;}

    //setters
    void setIdProducto(int id){idProducto=id;}
    void setStock(int s){stock=s;}

    //metodos
    string toString();
    bool LeerDeDisco(int pos);
    bool GrabarEnDisco();
    bool ModificarArchivo(int pos);

};

//funciones globales que no pertenecen a la clase.
int CantidadRegistrosStock();
void listarStocks();
bool nuevoStock();
ProductoStock cargarStock();
void menuStockProductos();
int EditarStock();


#endif // PRODUCTOSTOCK_H_INCLUDED
