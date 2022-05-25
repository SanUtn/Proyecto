#ifndef RETIROPRODUCTO_H_INCLUDED
#define RETIROPRODUCTO_H_INCLUDED

#include "Usuario.h"
#include "Producto.h"
#include "Fecha.h"

    class RetiroProducto{

        private:
            int idRetiro;
            int DNI;
            int idProducto;
            Fecha fechaRetiro;

        public:
            //getters
            int getIdRetiro(){return idRetiro;}
            int getDNI(){return DNI;}
            int getIdProducto(){return idProducto;}
            Fecha getFechaRetiro(){return fechaRetiro;}

            //setters
            void setIdRetiro(int id){idRetiro=id;}
            void setDNI(int d){DNI=d;}
            void setIdProducto(int id){idProducto=id;}
            void setFechaRetiro(Fecha f){fechaRetiro=f;}

            //metodos
            void Cargar();
            void Mostrar();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);







    };











#endif // RETIROPRODUCTO_H_INCLUDED
