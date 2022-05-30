#ifndef INGRESOPRODUCTO_H_INCLUDED
#define INGRESOPRODUCTO_H_INCLUDED
#include "Fecha.h"

    class IngresoProducto{

        private:
            int idIngreso;
            int dniUsuario;
            int idProducto;
            Fecha fechaIngreso;

        public:
            //getters
            int getIdIngreso(){return idIngreso;}
            int getDniUsuario(){return dniUsuario;}
            int getIdProducto(){return idProducto;}
            Fecha getFechaIngreso(){return fechaIngreso;}

            //setters
            void setIdIngreso(int id){idIngreso=id;}
            void setDniUsuario(int d){dniUsuario=d;}
            void setIdProducto(int id){idProducto=id;}
            void setFechaIngreso(Fecha f){fechaIngreso=f;}

            //metodos
            string toString();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);

    };


    //Funciones que no pertenecen a la clase
    bool ingresarProducto();
    int CantidadRegistrosProductosExistentes();
    IngresoProducto cargarProductoExistente();
    void listarIngresosDeProductosExistentes();










#endif // INGRESOPRODUCTO_H_INCLUDED
