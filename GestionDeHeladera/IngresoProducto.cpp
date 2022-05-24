#include<cstdlib>
#include<cstring>
#include <iostream>
#include "IngresoProducto.h"

using namespace std;

    //falta agregar validacion de que no puede repetirse el id
    void IngresoProducto::Cargar(){
        cout<<"Ingrese el id: ";
        cin>>idIngreso;
        DNI.Cargar();
        idProducto.Cargar();
        fechaIngreso.Cargar();
    }

    void IngresoProducto::Mostrar(){
        cout<<"Id del ingreso: ";
        cout<<idIngreso;
        cout<<endl;
        DNI.Mostrar();
        idProducto.Mostrar();
        fechaIngreso.Mostrar();
    }


     bool IngresoProducto::LeerDeDisco(int pos){
        FILE *p;
        int leyo;
        p=fopen("IngresosProductos.dat", "rb");
            if(p==NULL){
              cout<<"El archivo no pudo abrirse"<<endl;
              exit(1);
            }
        fseek(p, pos*sizeof(IngresoProducto),0);
        leyo=fread(this,sizeof(IngresoProducto),1,p);

        fclose(p);

        if(leyo){
            return true;
        }else{
        return false;
        }
    }

     bool IngresoProducto::GrabarEnDisco(){
        FILE *p;
        p=fopen("IngresosProductos.dat", "ab");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        int escribio=fwrite(this, sizeof(IngresoProducto),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }



    //METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
    //HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
      bool IngresoProducto::ModificarArchivo(int pos){
        FILE *p;
        p=fopen("IngresosProductos.dat", "rb+");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        fseek(p, pos*sizeof(IngresoProducto),0);
        int escribio=fwrite(this, sizeof(IngresoProducto),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }
