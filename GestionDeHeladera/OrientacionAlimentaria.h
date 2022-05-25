#ifndef ORIENTACIONALIMENTARIA_H_INCLUDED
#define ORIENTACIONALIMENTARIA_H_INCLUDED
# include<cstdlib>
# include<cstring>
# include<string>
# include<iostream>
using namespace std;

    class OrientacionAlimentaria{

        private:
            int idOrientacionAlimentaria;
            char descripcion[30];
            bool estadoOrientacion;

        public:
            //getters
            int getIdOrientacionAlimentaria(){return idOrientacionAlimentaria;}
            string getDescripcion();
            bool getEstadoOrientacion(){return estadoOrientacion;}

            //setters
            void setIdOrientacionAlimentaria(int id){idOrientacionAlimentaria=id;}
            void setDescripcion(string d){strcpy(descripcion,d.c_str());}
            void setEstadoOrientacion(bool e){estadoOrientacion=e;}

            //metodos
            string toString();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);

    };


    //Funciones globales que no pertenecen a la clase
    bool nuevaOrientacionAlimentaria();
    int CantidadRegistrosOA();
    OrientacionAlimentaria cargarOrientacionAlimentaria();
    void listarOrientacionAlimentaria();
    void menuOrientacionAlimentaria();









#endif // ORIENTACIONALIMENTARIA_H_INCLUDED
