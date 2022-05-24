#include <iostream>
#include "Producto.h"

using namespace std;

    //falta agregar validacion de que no puede repetirse el id
    void Producto::Cargar(){
        cout<<"Ingrese el id del producto: ";
        cin>>idProducto;
        cout<<"Ingrese el nombre del producto: ";
        cin>>nombreProducto;
        estadoProducto = true;
    }

    void Producto::Mostrar(){
        if (estadoProducto == true){
        cout<<"Id del producto: ";
        cout<<idProducto;
        cout<<endl;
        cout<<"Nombre del Producto: ";
        cout<<nombreProducto;
        cout<<endl;
        }
    }


     bool Producto::LeerDeDisco(int pos){
        FILE *p;
        int leyo;
        p=fopen("Productos.dat", "rb");
            if(p==NULL){
              cout<<"El archivo no pudo abrirse"<<endl;
              exit(1);
            }
        fseek(p, pos*sizeof(Producto),0);
        leyo=fread(this,sizeof(Producto),1,p);

        fclose(p);

        if(leyo){
            return true;
        }else{
        return false;
        }
    }

     bool Producto::GrabarEnDisco(){
        FILE *p;
        p=fopen("Productos.dat", "ab");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        int escribio=fwrite(this, sizeof(Producto),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }



    //METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
    //HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
      bool Producto::ModificarArchivo(int pos){
        FILE *p;
        p=fopen("Productos.dat", "rb+");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        fseek(p, pos*sizeof(Producto),0);
        int escribio=fwrite(this, sizeof(Producto),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }
