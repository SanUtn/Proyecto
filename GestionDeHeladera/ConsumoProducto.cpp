#include <iostream>
#include "ConsumoProducto.h"

using namespace std;


    void ConsumoProducto::Cargar(){
       idProducto.Cargar();
       fechaConsumo.Cargar();
    }

    void ConsumoProducto::Mostrar(){
       idProducto.Mostrar();
       fechaConsumo.Mostrar();
    }


     bool ConsumoProducto::LeerDeDisco(int pos){
        FILE *p;
        int leyo;
        p=fopen("ConsumosProductos.dat", "rb");
            if(p==NULL){
              cout<<"El archivo no pudo abrirse"<<endl;
              exit(1);
            }
        fseek(p, pos*sizeof(ConsumoProducto),0);
        leyo=fread(this,sizeof(ConsumoProducto),1,p);

        fclose(p);

        if(leyo){
            return true;
        }else{
        return false;
        }
    }

     bool ConsumoProducto::GrabarEnDisco(){
        FILE *p;
        p=fopen("ConsumosProductos.dat", "ab");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        int escribio=fwrite(this, sizeof(ConsumoProducto),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }



    //METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
    //HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
      bool ConsumoProducto::ModificarArchivo(int pos){
        FILE *p;
        p=fopen("ConsumosProductos.dat", "rb+");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        fseek(p, pos*sizeof(ConsumoProducto),0);
        int escribio=fwrite(this, sizeof(ConsumoProducto),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }
