#include <iostream>
#include "OrientacionAlimentaria.h"


using namespace std;

     string OrientacionAlimentaria::getDescripcion(){
        string descripciones;
        descripciones = descripcion;
        return descripciones;
    }

    string OrientacionAlimentaria::toString(){
        string cadena;
        cadena = "Id Orientacion Alimentaria: " + to_string(idOrientacionAlimentaria) + " " " " + " Descripcion: " + descripcion;
        return cadena;
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


    /// Funciones globales para gestionar la Orientacion Alimentaria
    bool nuevaOrientacionAlimentaria(){
        OrientacionAlimentaria reg;
        reg = cargarOrientacionAlimentaria();
        bool ok = reg.GrabarEnDisco();
        return ok;
    }

     int CantidadRegistrosOA(){
        FILE *p;
        p=fopen("OrientacionesAlimentarias.dat", "rb");
            if(p==NULL){
              return 0;
            }
            size_t bytes;
            int cantidad;

            fseek(p, 0, SEEK_END);
            bytes=ftell(p);

            fclose(p);
         cantidad = bytes/sizeof(OrientacionAlimentaria);
         return cantidad;
     }

    OrientacionAlimentaria cargarOrientacionAlimentaria(){
        int id;
        string descripcion;
        bool estado = true;

        id = CantidadRegistrosOA()+1;

        cout << "Ingrese la descripcion: ";
        cin >> descripcion;

        OrientacionAlimentaria reg;
        reg.setIdOrientacionAlimentaria(id);
        reg.setDescripcion(descripcion);
        reg.setEstadoOrientacion(estado);
        cout<<endl;
        cout<<endl;
        system("pause");
        return reg;
    }


    void listarOrientacionAlimentaria(){
        OrientacionAlimentaria aux;
        int cont=0;
        int cantOA = CantidadRegistrosOA();
    cout << "LISTADO DE ORIENTACIONES ALIMENTARIAS" << endl;
    cout << "----------------------------------" << endl;
        for(int i=0; i<cantOA; i++){
            aux.LeerDeDisco(i);
            if(aux.getEstadoOrientacion()){
                cout<<aux.toString()<<endl;
            }else{
             cont++;
            }
        }
        cout << "----------------------------------" << endl;
        cout << "Total: " << cantOA - cont<< " orientaciones alimentarias.";
        cout<<endl;
        cout<<endl;
        system("pause");
    }

    int EliminarOrientacionAlimentaria(){
        OrientacionAlimentaria aux;
        int pos=0, idOrientacion;

        listarOrientacionAlimentaria();
        cout<<endl;

        cout<<"Ingrese el ID de la orientacion a eliminar: ";
        cin>>idOrientacion;

        while(aux.LeerDeDisco(pos)==1){
           if(aux.getIdOrientacionAlimentaria() == idOrientacion){
                aux.setEstadoOrientacion(false);
                aux.ModificarArchivo(pos);
                return pos;
           }
           pos++;
        }
        return -1;
     }

  void menuOrientacionAlimentaria(){
   int opc;
    while(true){
        system("cls");

        cout<<"MENU ORIENTACION ALIMENTARIA"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. AGREGAR ORIENTACION "<<endl;
        cout<<"2. ELIMINAR ORIENTACION" <<endl;
        cout<<"3. LISTAR ORIENTACIONES "<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: "<<endl;
        cin>>opc;

        system("cls");

        switch(opc){
            case 1:   if(nuevaOrientacionAlimentaria()){
                            cout<<endl;
                            cout<<"ORIENTACION AGREGADA";
                            cout<<endl;
                            system("pause");
                        }else {
                             cout<<endl;
                            cout<<"NO SE PUDO AGREGAR LA ORIENTACION";
                            cout<<endl;
                            system("pause");
                        }
                break;
            case 2:
                   if(EliminarOrientacionAlimentaria()!= -1){
                            cout<<endl;
                            cout<<"ORIENTACION ELIMINADA";
                            cout<<endl;
                            system("pause");
                        }else {
                             cout<<endl;
                            cout<<"NO SE PUDO ELIMINAR LA ORIENTACION";
                            cout<<endl;
                            system("pause");
                        }
                break;
            case 3: listarOrientacionAlimentaria();
                break;
            case 0: return;
                    break;
        }
        cout<<endl;
    }
  }
