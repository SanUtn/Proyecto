#include <iostream>
#include "ConsumoPlatillo.h"

using namespace std;


    void ConsumoPlatillo::Cargar(){
      idPlatillo.Cargar();
      fechaConsumo.Cargar();
    }

    void ConsumoPlatillo::Mostrar(){
        idPlatillo.Mostrar();
        //fechaConsumo.Mostrar();
    }


     bool ConsumoPlatillo::LeerDeDisco(int pos){
        FILE *p;
        int leyo;
        p=fopen("ConsumosPlatillos.dat", "rb");
            if(p==NULL){
              cout<<"El archivo no pudo abrirse"<<endl;
              exit(1);
            }
        fseek(p, pos*sizeof(ConsumoPlatillo),0);
        leyo=fread(this,sizeof(ConsumoPlatillo),1,p);

        fclose(p);

        if(leyo){
            return true;
        }else{
        return false;
        }
    }

     bool ConsumoPlatillo::GrabarEnDisco(){
        FILE *p;
        p=fopen("ConsumosPlatillos.dat", "ab");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        int escribio=fwrite(this, sizeof(ConsumoPlatillo),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }



    //METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
    //HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
      bool ConsumoPlatillo::ModificarArchivo(int pos){
        FILE *p;
        p=fopen("ConsumosPlatillos.dat", "rb+");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        fseek(p, pos*sizeof(ConsumoPlatillo),0);
        int escribio=fwrite(this, sizeof(ConsumoPlatillo),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }
