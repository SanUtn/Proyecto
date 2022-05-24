#include <iostream>
#include "OrientacionAlimentaria.h"


using namespace std;

//falta agregar validacion de que no puede repetirse el id
    void OrientacionAlimentaria::Cargar(){
        cout<<"Ingrese el id de la orientacion: ";
        cin>>idOrientacionAlimentaria;
        cout<<"Ingrese la descripcion: ";
        cin>>descripcion;
        estadoOrientacion = true;
    }

    void OrientacionAlimentaria::Mostrar(){
        if (estadoOrientacion == true){
        cout<<"Id de la orientacion: ";
        cout<<idOrientacionAlimentaria;
        cout<<endl;
        cout<<"Descripcion: ";
        cout<<descripcion;
        cout<<endl;
        }
    }


     bool OrientacionAlimentaria::LeerDeDisco(int pos){
        FILE *p;
        int leyo;
        p=fopen("OrientacionesAlimentarias.dat", "rb");
            if(p==NULL){
              cout<<"El archivo no pudo abrirse"<<endl;
              exit(1);
            }
        fseek(p, pos*sizeof(OrientacionAlimentaria),0);
        leyo=fread(this,sizeof(OrientacionAlimentaria),1,p);

        fclose(p);

        if(leyo){
            return true;
        }else{
        return false;
        }
    }

     bool OrientacionAlimentaria::GrabarEnDisco(){
        FILE *p;
        p=fopen("OrientacionesAlimentarias.dat", "ab");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        int escribio=fwrite(this, sizeof(OrientacionAlimentaria),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }



    //METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
    //HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
      bool OrientacionAlimentaria::ModificarArchivo(int pos){
        FILE *p;
        p=fopen("OrientacionesAlimentarias.dat", "rb+");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        fseek(p, pos*sizeof(OrientacionAlimentaria),0);
        int escribio=fwrite(this, sizeof(OrientacionAlimentaria),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }
