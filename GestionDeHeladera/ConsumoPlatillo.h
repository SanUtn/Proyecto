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
            int usuario;
        public:
            //getters
            int getIdPlatillo(){return idPlatillo;}
            Fecha getFechaConsumo(){return fechaConsumo;}
            int getUsuario(){return usuario;}

            //setters
            void setIdPlatillo(int id){idPlatillo=id;}
            void setFechaConsumo(Fecha f){fechaConsumo=f;}
            void setUsuario(int u){usuario = u;}

             //metodos
            string toString();
            void toList();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);

    };

 //Funciones globales que no pertenecen a la clase
    bool nuevoConsumoPlatillo(int u);
    int CantidadRegistrosConsumoPlatillo();
    ConsumoPlatillo cargarConsumoPlatillo(int u);
    bool validarExistenciaDeProductos(int idPlatillo);
    void listarConsumosPlatillo();
    void menuSugerenciasPlatillos();
    int sugerenciasXOrientacion();
    int buscarOrientacion(int dni);
    void buscarPlatillosXOrientacion(int orientacion);
    int sugerenciasXCalorias();
    void buscarPlatillosXCalorias(int calorias);
    bool validarCalorias(int calorias);
















#endif // CONSUMOPLATILLO_H_INCLUDED
