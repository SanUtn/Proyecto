#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include<cstdlib>
#include<cstring>
#include "OrientacionAlimentaria.h"

    class Usuario{

        private:
            int DNI;
            char nombre[30];
            char apellido[30];
            OrientacionAlimentaria idOrientacionAlimentaria;
            bool estadoUsuario;

        public:
            //getters
            int getDNI(){return DNI;}
            const char *getNombre(){return nombre;}
            const char *getApellido(){return apellido;}
            OrientacionAlimentaria getIdOrientacionAlimentaria(){return idOrientacionAlimentaria;}
            bool getEstadoUsuario(){return estadoUsuario;}

            //setters
            void setDNI(int d){DNI=d;}
            void setNombre(const char *n){strcpy(nombre, n);}
            void setApellido(const char *a){strcpy(apellido, a);}
            void setIdOrientacionAlimentaria(OrientacionAlimentaria id){idOrientacionAlimentaria=id;}
            void setEstadoUsuario(bool e){estadoUsuario=e;}

            //metodos
            void Cargar();
            void Mostrar();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);




    };

















#endif // USUARIO_H_INCLUDED
