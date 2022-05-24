#include <iostream>
#include "ProductoStock.h"

using namespace std;


    void ProductoStock::Cargar(){
        idProducto.Cargar();
        cout<<"Ingrese el stock: ";
        cin>>stock;
    }

    void ProductoStock::Mostrar(){
        idProducto.Mostrar();
        cout<<"Stock: ";
        cout<<stock;
        cout<<endl;
    }


     bool ProductoStock::LeerDeDisco(int pos){
        FILE *p;
        int leyo;
        p=fopen("ProductosStock.dat", "rb");
            if(p==NULL){
              cout<<"El archivo no pudo abrirse"<<endl;
              exit(1);
            }
        fseek(p, pos*sizeof(ProductoStock),0);
        leyo=fread(this,sizeof(ProductoStock),1,p);

        fclose(p);

        if(leyo){
            return true;
        }else{
        return false;
        }
    }

     bool ProductoStock::GrabarEnDisco(){
        FILE *p;
        p=fopen("ProductosStock.dat", "ab");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        int escribio=fwrite(this, sizeof(ProductoStock),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }



    //METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
    //HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
      bool ProductoStock::ModificarArchivo(int pos){
        FILE *p;
        p=fopen("ProductosStock.dat", "rb+");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        fseek(p, pos*sizeof(ProductoStock),0);
        int escribio=fwrite(this, sizeof(ProductoStock),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }
