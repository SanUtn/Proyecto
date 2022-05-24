#ifndef PRODUCTOSTOCK_H_INCLUDED
#define PRODUCTOSTOCK_H_INCLUDED
#include "Producto.h"

    class ProductoStock{

        private:
            Producto idProducto;
            int stock;

        public:
            //getters
            Producto getIdProducto(){return idProducto;}
            int getStock(){return stock;}

            //setters
            void setIdProducto(Producto id){idProducto=id;}
            void setStock(int s){stock=s;}


            //metodos
            void Cargar();
            void Mostrar();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);



    };














#endif // PRODUCTOSTOCK_H_INCLUDED
