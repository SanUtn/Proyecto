#ifndef RECETA_H_INCLUDED
#define RECETA_H_INCLUDED
#include "Platillo.h"
# include<cstdlib>
# include<cstring>


    class Receta{

        private:
            int idReceta;
            Platillo idPlatillo;
            char descripcion[30];
            bool estadoReceta;

        public:
            //getters
            int getIdReceta(){return idReceta;}
            Platillo getIdPlatillo(){return idPlatillo;}
            const char *getDescripcion(){return descripcion;}
            bool getEstadoReceta(){return estadoReceta;}

            //setters
            void setIdReceta(int id){idReceta=id;}
            void setIdPlatillo(Platillo id){idPlatillo=id;}
            void setDescripcion(const char *d){strcpy(descripcion,d);}
            void setEstadoReceta(const char *e){estadoReceta=e;}

             //metodos
            void Cargar();
            void Mostrar();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);











    };















#endif // RECETA_H_INCLUDED
