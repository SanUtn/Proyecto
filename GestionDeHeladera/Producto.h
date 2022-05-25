#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED
# include<cstring>
# include<cstdlib>
# include<string>
using namespace std;

class Producto{

    private:
        int idProducto;
        char nombreProducto[30];
        bool estadoProducto;


    public:
        //getters
        int getIdProducto(){return idProducto;}
        string getNombreProducto();
        bool getEstadoProducto(){return estadoProducto;}

        //setters
        void setIdProducto(int id){idProducto=id;}
        void setNombreProducto(string n){strcpy(nombreProducto, n.c_str());}
        void setEstadoProducto(bool e){estadoProducto=e;}

        //metodos
        string toString();
        bool LeerDeDisco(int pos);
        bool GrabarEnDisco();
        bool ModificarArchivo(int pos);

};

    //Funciones globales no pertenecientes a la clase
    bool nuevoProducto();
    int CantidadRegistrosProductos();
    Producto cargarProducto();
    void listarProductos();
    void menuProducto();













#endif // PRODUCTO_H_INCLUDED
