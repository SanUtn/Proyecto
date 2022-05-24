#ifndef CONSUMOPLATILLO_H_INCLUDED
#define CONSUMOPLATILLO_H_INCLUDED
#include "Platillo.h"
#include "Fecha.h"
#include "OrientacionAlimentaria.h"

    class ConsumoPlatillo{

        private:
            Platillo idPlatillo;
            Fecha fechaConsumo;

        public:
            //getters
            Platillo getIdPlatillo(){return idPlatillo;}
            Fecha getFechaConsumo(){return fechaConsumo;}

            //setters
            void setIdPlatillo(Platillo id){idPlatillo=id;}
            void setFecha(Fecha f){fechaConsumo=f;}

             //metodos
            void Cargar();
            void Mostrar();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);








    };
















#endif // CONSUMOPLATILLO_H_INCLUDED
