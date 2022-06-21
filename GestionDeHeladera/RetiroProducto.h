#ifndef RETIROPRODUCTO_H_INCLUDED
#define RETIROPRODUCTO_H_INCLUDED

#include "Fecha.h"

    class RetiroProducto{

        private:
            int idRetiro;
            int dniUsuario;
            int idProducto;
            Fecha fechaRetiro;

        public:
            //getters
            int getIdRetiro(){return idRetiro;}
            int getDniUsuario(){return dniUsuario;}
            int getIdProducto(){return idProducto;}
            Fecha getFechaRetiro(){return fechaRetiro;}

            //setters
            void setIdRetiro(int id){idRetiro=id;}
            void setDniUsuario(int d){dniUsuario=d;}
            void setIdProducto(int id){idProducto=id;}
            void setFechaRetiro(Fecha f){fechaRetiro=f;}

            //metodos
            string toString();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);

    };


    //Funciones que no pertenecen a la clase
    bool retirarProducto();
    int CantidadRegistrosRetiroProductosExistentes();
    RetiroProducto retirarProductoExistente();
    void listarRetirosDeProductosExistentes();
    bool retirarProductoExistentePorConsumo(int idplatillo, int usuario);









#endif // RETIROPRODUCTO_H_INCLUDED
