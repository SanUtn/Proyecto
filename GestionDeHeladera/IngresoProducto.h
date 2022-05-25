#ifndef INGRESOPRODUCTO_H_INCLUDED
#define INGRESOPRODUCTO_H_INCLUDED
#include "Usuario.h"
#include "Producto.h"
#include "Fecha.h"

    class IngresoProducto{

        private:
            int idIngreso;
            int DNI;
            int idProducto;
            Fecha fechaIngreso;

        public:
            //getters
            int getIdIngreso(){return idIngreso;}
            int getDNI(){return DNI;}
            int getIdProducto(){return idProducto;}
            Fecha getFechaIngreso(){return fechaIngreso;}

            //setters
            void setIdIngreso(int id){idIngreso=id;}
            void setDNI(int d){DNI=d;}
            void setIdProducto(int id){idProducto=id;}
            void setFechaIngreso(Fecha f){fechaIngreso=f;}

            //metodos
            void Cargar();
            void Mostrar();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);

    };















#endif // INGRESOPRODUCTO_H_INCLUDED
