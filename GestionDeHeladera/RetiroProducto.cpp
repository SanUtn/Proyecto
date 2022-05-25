#include <iostream>
#include "RetiroProducto.h"

using namespace std;

    //falta agregar validacion de que no puede repetirse el id
    void RetiroProducto::Cargar(){
        cout<<"Ingrese el id: ";
        cin>>idRetiro;
        cout<<"DNI del Usuario: ";
        cin>>DNI;
        cout<<"Id del producto: ";
        cin>>idProducto;
        fechaRetiro.Cargar();
    }

    void RetiroProducto::Mostrar(){
        cout<<"Id del retiro: ";
        cout<<idRetiro;
        cout<<endl;
        cout<<"DNI del Usuario: ";
        cout<<DNI;
        cout<<endl;
        cout<<"Id del producto: ";
        cout<<idProducto;
        cout<<endl;
        fechaRetiro.toString();
    }


     bool RetiroProducto::LeerDeDisco(int pos){
        FILE *p;
        int leyo;
        p=fopen("RetirosProductos.dat", "rb");
            if(p==NULL){
              cout<<"El archivo no pudo abrirse"<<endl;
              exit(1);
            }
        fseek(p, pos*sizeof(RetiroProducto),0);
        leyo=fread(this,sizeof(RetiroProducto),1,p);

        fclose(p);

        if(leyo){
            return true;
        }else{
        return false;
        }
    }

     bool RetiroProducto::GrabarEnDisco(){
        FILE *p;
        p=fopen("RetirosProductos.dat", "ab");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        int escribio=fwrite(this, sizeof(RetiroProducto),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }



    //METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
    //HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
      bool RetiroProducto::ModificarArchivo(int pos){
        FILE *p;
        p=fopen("RetirosProductos.dat", "rb+");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        fseek(p, pos*sizeof(RetiroProducto),0);
        int escribio=fwrite(this, sizeof(RetiroProducto),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }
