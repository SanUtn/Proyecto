#ifndef CONSUMOPRODUCTO_H_INCLUDED
#define CONSUMOPRODUCTO_H_INCLUDED
# include<cstring>
# include<cstdlib>
# include<string>
#include "Fecha.h"
using namespace std;

    class ConsumoProducto{

        private:
            int idProducto;
            Fecha fechaConsumo;

        public:
            //getters
            int getIdProducto(){return idProducto;}
            Fecha getFechaConsumo(){return fechaConsumo;}

            //setters
            void setIdProducto(int id){idProducto=id;}
            void setFechaConsumo(Fecha f){fechaConsumo=f;}

            //metodos
            string toString();
            void toList();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);

    };



    ///Funciones globales que no pertenecen a la clase
    bool nuevoConsumoProducto();
    int CantidadRegistrosConsumoProducto();
    ConsumoProducto cargarConsumoProducto();
    void listarConsumosPoductos();
    bool validarExistenciaDeProductosParaConsumo(int idproducto);













#endif // CONSUMOPRODUCTO_H_INCLUDED
