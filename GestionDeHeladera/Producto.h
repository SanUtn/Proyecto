#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED
# include<cstring>
# include<cstdlib>


class Producto{

    private:
        int idProducto;
        char nombreProducto[30];
        bool estadoProducto;


    public:
        //getters
        int getIdProducto(){return idProducto;}
        const char *getNombreProducto(){return nombreProducto;}
        bool getEstadoProducto(){return estadoProducto;}

        //setters
        void setIdProducto(int id){idProducto=id;}
        void setNombreProducto(const char *n){strcpy(nombreProducto, n);}
        void setEstadoProducto(bool e){estadoProducto=e;}

        //metodos
        void Cargar();
        void Mostrar();
        bool LeerDeDisco(int pos);
        bool GrabarEnDisco();
        bool ModificarArchivo(int pos);







};
















#endif // PRODUCTO_H_INCLUDED
