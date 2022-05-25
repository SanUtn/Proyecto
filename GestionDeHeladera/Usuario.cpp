#include <iostream>
#include "Usuario.h"

using namespace std;


    string Usuario::getNombre(){
        string nombres;
        nombres = nombre;
        return nombres;
    }

    string Usuario::getApellido(){
        string apellidos;
        apellidos=apellido;
        return apellidos;
    }


    void Usuario::setNombre(string nombres){
        strcpy(nombre, nombres.c_str());
    }

    void Usuario::setApellido(string apellidos){
        strcpy(apellido, apellidos.c_str());
    }

   string Usuario::toString(){
        string cadena;
    cadena = " Id: " + to_string(id) + " " " " + " Nombre: " + nombre + " " " " + " Apellido: " + apellido + " " " " + " Orientacion Alimentaria: " + to_string(idOrientacionAlimentaria);
        return cadena;
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


    /// Funciones globales para gestionar Usuario
    bool nuevoUsuario(){
        Usuario reg;
        reg = cargarUsuario();
        bool ok = reg.GrabarEnDisco();
        return ok;
    }

     int CantidadRegistrosUsuario(){
        FILE *p;
        p=fopen("Usuarios.dat", "rb");
            if(p==NULL){
              return 0;
            }
            size_t bytes;
            int cantidad;

            fseek(p, 0, SEEK_END);
            bytes=ftell(p);

            fclose(p);
         cantidad = bytes/sizeof(Usuario);
         return cantidad;
     }

    Usuario cargarUsuario(){
        int id;
        int dni;
        string nombre;
        string apellido;
        int idOrientacionAlimentaria;
        bool estado = true;

        id = CantidadRegistrosUsuario()+1;

        cout << "Ingrese el DNI: ";
        cin >> dni;
        cout << "Ingrese el nombre: ";
        cin >> nombre;
        cout << "Ingrese el apellido: ";
        cin >> apellido;
        cout << "Ingrese la orientacion alimentaria: ";
        cin >> idOrientacionAlimentaria;

        Usuario reg;
        reg.setId(id);
        reg.setDNI(dni);
        reg.setNombre(nombre);
        reg.setApellido(apellido);
        reg.setIdOrientacionAlimentaria(idOrientacionAlimentaria);
        reg.setEstadoUsuario(estado);
        cout<<endl;
        cout<<endl;
        system("pause");
        return reg;
    }


    void listarUsuarios(){
        Usuario aux;
        int cantUsuarios = CantidadRegistrosUsuario();
    cout << "LISTADO DE USUARIOS" << endl;
    cout << "----------------------------------" << endl;
        for(int i=0; i<cantUsuarios; i++){
            aux.LeerDeDisco(i);
            if(aux.getEstadoUsuario()){
                cout<<aux.toString()<<endl;
            }
        }
        cout << "----------------------------------" << endl;
        cout << "Total: " << cantUsuarios << " Usuarios.";
        cout<<endl;
        cout<<endl;
        system("pause");
    }


  void menuUsuario(){
   int opc;
    while(true){
        system("cls");

        cout<<"MENU USUARIO"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. AGREGAR USUARIO "<<endl;
        cout<<"2. LISTAR USUARIOS "<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: "<<endl;
        cin>>opc;

        system("cls");

        switch(opc){
            case 1:   if(nuevoUsuario()){
                            cout<<endl;
                            cout<<"USUARIO AGREGADO";
                            cout<<endl;
                            system("pause");
                        }else {
                             cout<<endl;
                            cout<<"NO SE PUDO AGREGAR EL USUARIO";
                            cout<<endl;
                            system("pause");
                        }
                break;
            case 2: listarUsuarios();
                break;
            case 0: return;
                    break;
        }
        cout<<endl;
    }
  }
