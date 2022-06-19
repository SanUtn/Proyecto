#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED
# include<cstring>
# include<cstdlib>
# include<string>
#include "Fecha.h"
using namespace std;

class Producto{

    private:
        int idProducto;
        char nombreProducto[30];
        Fecha fechaVencimiento;
        bool estadoProducto;

    public:
        //getters
        int getIdProducto(){return idProducto;}
        string getNombreProducto();
        Fecha getFechaVencimiento(){return fechaVencimiento;}
        bool getEstadoProducto(){return estadoProducto;}

        //setters
        void setIdProducto(int id){idProducto=id;}
        void setNombreProducto(string n){strcpy(nombreProducto, n.c_str());}
        void setFechaVencimiento(Fecha f){fechaVencimiento=f;}
        void setEstadoProducto(bool e){estadoProducto=e;}

        //metodos
        string toString();
        void toList();
        bool LeerDeDisco(int pos);
        bool GrabarEnDisco();
        bool ModificarArchivo(int pos);

        //operator para comparar fechas
        bool operator==(Fecha fecha);

};

    ///Funciones globales no pertenecientes a la clase
    bool nuevoProducto();
    int CantidadRegistrosProductos();
    Producto cargarProducto();
    void listarProductos();
    void menuProducto();
    int EliminarProducto();
    bool validarProductoExistente(string);
    bool validarProductoExistenteID(int id);
    void alertaDeProductosAVencer();
    void buscarProducto();













#endif // PRODUCTO_H_INCLUDED
