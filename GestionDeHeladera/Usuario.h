#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include<cstdlib>
#include<cstring>
#include <string>
#include "OrientacionAlimentaria.h"
using namespace std;

    class Usuario{

        private:
            int id;
            int DNI;
            char nombre[30];
            char apellido[30];
            int idOrientacionAlimentaria;
            bool estadoUsuario;

        public:
            //getters
            int getId(){return id;}
            int getDNI(){return DNI;}
            string getNombre();
            string getApellido();
            int getIdOrientacionAlimentaria(){return idOrientacionAlimentaria;}
            bool getEstadoUsuario(){return estadoUsuario;}

            //setters
            void setId(int i){id=i;}
            void setDNI(int d){DNI=d;}
            void setNombre(string nombres);
            void setApellido(string apellidos);
            void setIdOrientacionAlimentaria(int id){idOrientacionAlimentaria=id;}
            void setEstadoUsuario(bool e){estadoUsuario=e;}

            //metodos
            string toString();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);
            int buscarUsuario(int dni);
            bool EliminarUsuario();

    };

    //Funciones globales que no pertenecen a la clase
    bool nuevoUsuario();
    int CantidadRegistrosUsuario();
    Usuario cargarUsuario();
    void listarUsuarios();
    void menuUsuario();
    bool validarUsuarioExistente(int);

#endif // USUARIO_H_INCLUDED
