#ifndef INGRESOPRODUCTO_H_INCLUDED
#define INGRESOPRODUCTO_H_INCLUDED
#include "Usuario.h"
#include "Producto.h"
#include "Fecha.h"

    class IngresoProducto{

        private:
            int idIngreso;
            Usuario DNI;
            Producto idProducto;
            Fecha fechaIngreso;

        public:
            //getters
            int getIdIngreso(){return idIngreso;}
            Usuario getDNI(){return DNI;}
            Producto getIdProducto(){return idProducto;}
            Fecha getFechaIngreso(){return fechaIngreso;}

            //setters
            void setIdIngreso(int id){idIngreso=id;}
            void setDNI(Usuario d){DNI=d;}
            void setIdProducto(Producto id){idProducto=id;}
            void setFechaIngreso(Fecha f){fechaIngreso=f;}

            //metodos
            void Cargar();
            void Mostrar();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);







    };















#endif // INGRESOPRODUCTO_H_INCLUDED
