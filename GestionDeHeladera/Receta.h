#ifndef RECETA_H_INCLUDED
#define RECETA_H_INCLUDED
#include "Platillo.h"
# include<cstdlib>
# include<cstring>
# include<string>
using namespace std;

    class Receta{

        private:
            int idReceta;
            int idPlatillo;
            char descripcion[300];
            bool estadoReceta;

        public:
            //getters
            int getIdReceta(){return idReceta;}
            int getIdPlatillo(){return idPlatillo;}
            string getDescripcion();
            bool getEstadoReceta(){return estadoReceta;}

            //setters
            void setIdReceta(int id){idReceta=id;}
            void setIdPlatillo(int id){idPlatillo=id;}
            void setDescripcion(string d){strcpy(descripcion,d.c_str());}
            void setEstadoReceta(bool e){estadoReceta=e;}

             //metodos
            string toString();
            bool LeerDeDisco(int pos);
            bool GrabarEnDisco();
            bool ModificarArchivo(int pos);

    };


    ///Funciones globales que no pertenecen a la clase
    bool nuevaReceta();
    int CantidadRegistrosReceta();
    Receta cargarReceta();
    void listarRecetas();
    void menuRecetas();
    int EliminarReceta();
    void cargarVectorConRecetas(Receta *vRecetas, int tam);
    void ponerEnCeroElVectorDeRecetas(Receta *vRecetas, int tam);
    void elegirReceta(int opc);
    void buscarReceta(int *vRecetas, int tam);
    bool validarExisteReceta(int idreceta);
    void buscarRecetaQueTegaStockDeProductos(Receta *vRecetas, int tam);
    bool controlarStockDeProductosPorPlatillos(int idPlatillo);
    void sugerenciaRecetas();
    void EliminarRecetaPorParametro(int idreceta);










#endif // RECETA_H_INCLUDED
