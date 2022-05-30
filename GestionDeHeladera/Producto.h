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
        //int dniUsuario;
        //Fecha fechaIngreso;
        bool estadoProducto;


    public:
        //getters
        int getIdProducto(){return idProducto;}
        string getNombreProducto();
        //int getDniUsuario(){return dniUsuario;}
        //Fecha getFechaIngreso(){return fechaIngreso;}
        bool getEstadoProducto(){return estadoProducto;}

        //setters
        void setIdProducto(int id){idProducto=id;}
        void setNombreProducto(string n){strcpy(nombreProducto, n.c_str());}
        //void setDniUsuario(int d){dniUsuario=d;}
        //void setFechaIngreso(Fecha f){fechaIngreso=f;}
        void setEstadoProducto(bool e){estadoProducto=e;}

        //metodos
        string toString();
        bool LeerDeDisco(int pos);
        bool GrabarEnDisco();
        bool ModificarArchivo(int pos);

};

    //Funciones globales no pertenecientes a la clase
    bool nuevoProducto();
    int CantidadRegistrosProductos();
    Producto cargarProducto();
    void listarProductos();
    void menuProducto();
    int EliminarProducto();
    bool validarProductoExistente(string);












#endif // PRODUCTO_H_INCLUDED
