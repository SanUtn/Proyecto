#ifndef PLATILLO_H_INCLUDED
#define PLATILLO_H_INCLUDED
#include "Fecha.h"
#include "Producto.h"
#include "OrientacionAlimentaria.h"
# include<cstdlib>
# include<cstring>


    class Platillo{

        private:
            int idPlatillo;
            char nombrePlatillo [30];
            Fecha fechaRegistrado;
            int ingredientes[20];
            //Producto *ingredientes= new Producto[20];(ver como hacer un vector de Producto)
            OrientacionAlimentaria orientacionAlimentaria;
            bool estadoPlatillo;

        public:
            //getters
            int getIdPlatillo(){return idPlatillo;}
            const char *getNombrePlatillo(){return nombrePlatillo;}
            Fecha getFechaRegistrado(){return fechaRegistrado;}
            int *getIngredientes(){return ingredientes;}
            //Producto *getIngredientes(){return ingredientes;}
            OrientacionAlimentaria getOrientacionAlimentaria(){return orientacionAlimentaria;}
            bool getEstadoPlatillo(){return estadoPlatillo;}

            //setters
            void setIdPlatillo(int id){idPlatillo=id;}
            void setNombrePlatillo(const char *n){strcpy(nombrePlatillo,n);}
            void setFechaRegistrado(Fecha f){fechaRegistrado=f;}
            void setIngredientes(int in){
             for(int i=0; i<20;i++){
                ingredientes[i]=in;
             }
            }
            //void setIngredientes(const Producto *i){ingredientes=i;}
            void setOrientacionAlimentaria(OrientacionAlimentaria o){orientacionAlimentaria=o;}
            void setEstadoPlatillo(bool e){estadoPlatillo=e;}

            //metodos
            void Cargar();
            void Mostrar();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);









    };















#endif // PLATILLO_H_INCLUDED
