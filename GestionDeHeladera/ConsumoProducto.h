#ifndef CONSUMOPRODUCTO_H_INCLUDED
#define CONSUMOPRODUCTO_H_INCLUDED
#include "Producto.h"
#include "Fecha.h"

    class ConsumoProducto{

        private:
            Producto idProducto;
            Fecha fechaConsumo;

        public:
            //getters
            Producto getIdProducto(){return idProducto;}
            Fecha getFechaConsumo(){return fechaConsumo;}

            //setters
            void setIdProducto(Producto id){idProducto=id;}
            void setFechaConsumo(Fecha f){fechaConsumo=f;}

            //metodos
            void Cargar();
            void Mostrar();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);








    };
















#endif // CONSUMOPRODUCTO_H_INCLUDED
