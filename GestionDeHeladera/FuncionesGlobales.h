#ifndef FUNCIONESGLOBALES_H_INCLUDED
#define FUNCIONESGLOBALES_H_INCLUDED
#include "ConsumoProducto.h"
#include "ConsumoPlatillo.h"
#include "OrientacionAlimentaria.h"
#include "Platillo.h"
#include "Producto.h"
#include "ProductoStock.h"
#include "RetiroProducto.h"
#include "ProductosxPlatillo.h"
#include "Receta.h"

void menuConsumos();
int CantidadProductosxPlatillo(int idplatillo);
string mostrarOrientacionAlimentaria(int id);
string mostrarNombreProducto(int id);
string mostrarNombrePlatillo(int id);
string mayuscula(string cadena);
Producto buscarProductoPorId(int id);
void eliminarStock(int idproducto);
void menuReportes();
void menuConsumosAnuales();
void menuConsumosMensuales();
void PlatillosAnual();
void ProductosAnual();
void PlatillosMensual();
void ProductosMensual();
void alertaStock();
RetiroProducto retirarProductoPorConsumo(int idplatillo);
void MenuSugerencias();
void  sugerenciaPorStock();
int buscarStockDeProducto(int idproducto);
void copiarProductos(Producto *vDinamico, int cantidad, int idplatillo);
void eliminarPlatillos(int idproducto);
void modificarVencimientoProducto(int idproducto, Fecha fecha);
void alertaSinStock();
void alertaDeProductosAVencer();
void alertaDeProductosVencidos();
void eliminarRecetasPorPlatillo(int idplatillo);
bool validarNumero();

#endif // FUNCIONESGLOBALES_H_INCLUDED
