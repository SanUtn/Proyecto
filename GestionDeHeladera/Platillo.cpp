#include <iostream>
#include "Platillo.h"

using namespace std;

    //falta agregar validacion de que no puede repetirse el id
    void Platillo::Cargar(){
        int ingrediente;
        cout<<"Ingrese el id del platillo: ";
        cin>>idPlatillo;
        cout<<"Ingrese el nombre del platillo: ";
        cin>>nombrePlatillo;
        fechaRegistrado.Cargar();
        //ingredientes.Cargar();
        cout<<"Ingrese ingrediente: ";
        cin>>ingrediente;
        setIngredientes(ingrediente);
        cout<<"Ingrese el nombre del platillo: ";
        cin>>nombrePlatillo;
        orientacionAlimentaria.Cargar();
        estadoPlatillo = true;
    }

    void Platillo::Mostrar(){
        if (estadoPlatillo == true){
        cout<<"Id del platillo: ";
        cout<<idPlatillo;
        cout<<endl;
        cout<<"Nombre del Platillo: ";
        cout<<nombrePlatillo;
        cout<<endl;
        fechaRegistrado.toString();
        //ingredientes.Mostrar();
        cout<<"Ingredientes: ";
         for(int i=0; i<20;i++){
              cout<<ingredientes[i]<<endl;
             }
        orientacionAlimentaria.Mostrar();
        }
    }


     bool Platillo::LeerDeDisco(int pos){
        FILE *p;
        int leyo;
        p=fopen("Platillos.dat", "rb");
            if(p==NULL){
              cout<<"El archivo no pudo abrirse"<<endl;
              exit(1);
            }
        fseek(p, pos*sizeof(Platillo),0);
        leyo=fread(this,sizeof(Platillo),1,p);

        fclose(p);

        if(leyo){
            return true;
        }else{
        return false;
        }
    }

     bool Platillo::GrabarEnDisco(){
        FILE *p;
        p=fopen("Platillos.dat", "ab");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        int escribio=fwrite(this, sizeof(Platillo),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }



    //METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
    //HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
      bool Platillo::ModificarArchivo(int pos){
        FILE *p;
        p=fopen("Platillos.dat", "rb+");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        fseek(p, pos*sizeof(Platillo),0);
        int escribio=fwrite(this, sizeof(Platillo),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }
