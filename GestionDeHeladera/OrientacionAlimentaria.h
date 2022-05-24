#ifndef ORIENTACIONALIMENTARIA_H_INCLUDED
#define ORIENTACIONALIMENTARIA_H_INCLUDED
# include<cstdlib>
# include<cstring>

    class OrientacionAlimentaria{

        private:
            int idOrientacionAlimentaria;
            char descripcion[30];
            bool estadoOrientacion;

        public:
            //getters
            int getIdOrientacionAlimentaria(){return idOrientacionAlimentaria;}
            const char *getDescripcion(){return descripcion;}
            bool getEstadoOrientacion(){return estadoOrientacion;}

            //setters
            void setIdOrientacionAlimentaria(int id){idOrientacionAlimentaria=id;}
            void setDescripcion(const char *d){strcpy(descripcion, d);}
            void setEstadoOrientacion(bool e){estadoOrientacion=e;}

            //metodos
            void Cargar();
            void Mostrar();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);


    };












#endif // ORIENTACIONALIMENTARIA_H_INCLUDED
