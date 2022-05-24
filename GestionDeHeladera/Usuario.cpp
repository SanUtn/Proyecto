#include <iostream>
#include "Usuario.h"

using namespace std;


    //falta agregar validacion de que no puede repetirse el dni
    void Usuario::Cargar(){
        cout<<"Ingrese el DNI: ";
        cin>>DNI;
        cout<<"Ingrese el nombre: ";
        cin>>nombre;
        cout<<"Ingrese el apellido: ";
        cin>>apellido;
        idOrientacionAlimentaria.Cargar();
        estadoUsuario = true;
    }

    void Usuario::Mostrar(){
        if (estadoUsuario == true){
        cout<<"DNI: ";
        cout<<DNI;
        cout<<endl;
        cout<<"Nombre: ";
        cout<<nombre;
        cout<<endl;
        cout<<"Apellido: ";
        cout<<apellido;
        cout<<endl;
        idOrientacionAlimentaria.Mostrar();
        }
    }


     bool Usuario::LeerDeDisco(int pos){
        FILE *p;
        int leyo;
        p=fopen("Usuarios.dat", "rb");
            if(p==NULL){
              cout<<"El archivo no pudo abrirse"<<endl;
              exit(1);
            }
        fseek(p, pos*sizeof(Usuario),0);
        leyo=fread(this,sizeof(Usuario),1,p);

        fclose(p);

        if(leyo){
            return true;
        }else{
        return false;
        }
    }

     bool Usuario::GrabarEnDisco(){
        FILE *p;
        p=fopen("Usuarios.dat", "ab");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        int escribio=fwrite(this, sizeof(Usuario),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }



    //METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
    //HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
      bool Usuario::ModificarArchivo(int pos){
        FILE *p;
        p=fopen("Usuarios.dat", "rb+");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          exit(1);
        }
        fseek(p, pos*sizeof(Usuario),0);
        int escribio=fwrite(this, sizeof(Usuario),1,p);
        fclose(p);

        if(escribio){
            return true;
        }else{
        return false;
        }
     }
