#ifndef FUNCIONESGLOBALES_H_INCLUDED
#define FUNCIONESGLOBALES_H_INCLUDED
#include "ConsumoProducto.h"
#include "ConsumoPlatillo.h"
#include "OrientacionAlimentaria.h"
#include "Platillo.h"
#include "Producto.h"
#include "ProductoStock.h"


void menuConsumos();
string mostrarOrientacionAlimentaria(int id);
string mostrarNombreProducto(int id);
string mostrarNombrePlatillo(int id);
string mayuscula(string cadena);
Producto buscarProductoPorId(int id);
void eliminarStock(int idproducto);






#endif // FUNCIONESGLOBALES_H_INCLUDED
