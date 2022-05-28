#ifndef PLATILLO_H_INCLUDED
#define PLATILLO_H_INCLUDED
#include "Fecha.h"
#include "Producto.h"
#include "OrientacionAlimentaria.h"
# include<cstdlib>
# include<cstring>
# include<string>
using namespace std;


    class Platillo{

        private:
            int idPlatillo;
            char nombrePlatillo [30];
            Fecha fechaRegistrado;
            //char ingredientes[20];
            //char nombreOrientacion [30];
            int orientacionAlimentaria;
            bool estadoPlatillo;

        public:
            //getters
            int getIdPlatillo(){return idPlatillo;}
            string getNombrePlatillo();
            Fecha getFechaRegistrado(){return fechaRegistrado;}
            //string getIngredientes();
            //string getNombreOrientacion();
            int getOrientacionAlimentaria(){return orientacionAlimentaria;}
            bool getEstadoPlatillo(){return estadoPlatillo;}

            //setters
            void setIdPlatillo(int id){idPlatillo=id;}
            void setNombrePlatillo(string n){strcpy(nombrePlatillo,n.c_str());}
            void setFechaRegistrado(Fecha f){fechaRegistrado=f;}
            //void setIngredientes(string in){strcpy(ingredientes,in.c_str());}
            //void setNombreOrientacion(string o){strcpy(nombreOrientacion,o.c_str());}
            void setOrientacionalimentaria(int o){orientacionAlimentaria=o;}
            void setEstadoPlatillo(bool e){estadoPlatillo=e;}

            //metodos
            string toString();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);

    };

    //Funciones globales que no pertenecen a la clase
    bool nuevoPlatillo();
    int CantidadRegistrosPlatillo();
    Platillo cargarPlatillo();
    void listarPlatillos();
    void menuPlatillo();


#endif // PLATILLO_H_INCLUDED
