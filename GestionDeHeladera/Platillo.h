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
            int orientacionAlimentaria;
            int calorias;
            bool estadoPlatillo;

        public:
            //getters
            int getIdPlatillo(){return idPlatillo;}
            string getNombrePlatillo();
            Fecha getFechaRegistrado(){return fechaRegistrado;}
            int getOrientacionAlimentaria(){return orientacionAlimentaria;}
            int getCalorias(){return calorias;}
            bool getEstadoPlatillo(){return estadoPlatillo;}

            //setters
            void setIdPlatillo(int id){idPlatillo=id;}
            void setNombrePlatillo(string n){strcpy(nombrePlatillo,n.c_str());}
            void setFechaRegistrado(Fecha f){fechaRegistrado=f;}
            void setOrientacionalimentaria(int o){orientacionAlimentaria=o;}
            void setCalorias(int c){calorias=c;}
            void setEstadoPlatillo(bool e){estadoPlatillo=e;}

            //metodos
            string toString();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);
            void toList();

    };

    //Funciones globales que no pertenecen a la clase
    bool nuevoPlatillo();
    int CantidadRegistrosPlatillo();
    Platillo cargarPlatillo();
    void listarPlatillos();
    void menuPlatillo();
    int EliminarPlatillo();
    bool validarPlatilloExistente(string n);
    void menuBuscarPlatillo();
    void buscarPlatilloNombre();
    void busquedaPlatilloOrientacion();
    void EliminarPlatilloPorParametro(int idplatillo);

#endif // PLATILLO_H_INCLUDED
