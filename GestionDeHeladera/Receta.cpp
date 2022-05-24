#include <iostream>
#include "Receta.h"

using namespace std;

    //falta agregar validacion de que no puede repetirse el id
    void Receta::Cargar(){
        cout<<"Ingrese el id de la receta: ";
        cin>>idReceta;
        idPlatillo.Cargar();//ver en vez de cargarlo de traer los datos de platillo
        cout<<"Ingrese la descripcion: ";
        cin>>descripcion;
        estadoReceta = true;
    }

    void Receta::Mostrar(){
        if (estadoReceta == true){
        cout<<"Id de la receta: ";
        cout<<idReceta;
        cout<<endl;
        idPlatillo.Mostrar();
        cout<<"Descripcion: ";
        cout<<descripcion;
        cout<<endl;
        }
    }


     bool Receta::LeerDeDisco(int pos){
        FILE *p;
        int leyo;
        p=fopen("Recetas.dat", "rb");
            if(p==NULL){
              cout<<"El archivo no pudo abrirse"<<endl;
              exit(1);
            }
        fseek(p, pos*sizeof(Receta),0);
        leyo=fread(this,sizeof(Receta),1,p);

        fclose(p);

        if(leyo){
            return true;
        }else{
        return false;
        }
    }

     bool Receta::GrabarEnDisco(){
        FILE *p;
        p=fopen("Recetas.dat", "ab");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        int escribio=fwrite(this, sizeof(Receta),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }



    //METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
    //HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
      bool Receta::ModificarArchivo(int pos){
        FILE *p;
        p=fopen("Recetas.dat", "rb+");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        fseek(p, pos*sizeof(Receta),0);
        int escribio=fwrite(this, sizeof(Receta),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }
