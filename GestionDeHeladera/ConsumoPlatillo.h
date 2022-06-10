#ifndef CONSUMOPLATILLO_H_INCLUDED
#define CONSUMOPLATILLO_H_INCLUDED
# include<cstring>
# include<cstdlib>
# include<string>
#include "Fecha.h"
using namespace std;

    class ConsumoPlatillo{

        private:
            int idPlatillo;
            Fecha fechaConsumo;

        public:
            //getters
            int getIdPlatillo(){return idPlatillo;}
            Fecha getFechaConsumo(){return fechaConsumo;}

            //setters
            void setIdPlatillo(int id){idPlatillo=id;}
            void setFechaConsumo(Fecha f){fechaConsumo=f;}

             //metodos
            string toString();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);

    };

 //Funciones globales que no pertenecen a la clase
    bool nuevoConsumoPlatillo();
    int CantidadRegistrosConsumoPlatillo();
    ConsumoPlatillo cargarConsumoPlatillo();
    bool validarExistenciaDeProductos(int idPlatillo);
    void listarConsumosPlatillo();















#endif // CONSUMOPLATILLO_H_INCLUDED
