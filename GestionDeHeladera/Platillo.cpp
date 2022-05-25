#include <iostream>
#include "Platillo.h"

using namespace std;

    string Platillo::getNombrePlatillo(){
        string nombrePlatillos;
        nombrePlatillos=nombrePlatillo;
        return nombrePlatillos;
    }

    string Platillo::getIngredientes(){
          string ingrediente;
          ingrediente=ingredientes;
          return ingrediente;
      }

    string Platillo::getNombreOrientacion(){
        string nombres;
        nombres=nombreOrientacion;
        return nombres;
    }

    //ver si se puede modificar por un vector dinamico que el usuario ingrese la cantidad de ingredientes.
    /*void Platillo::setIngredientes(int in){
             for(int i=0; i<20;i++){
                ingredientes[i]=in;
             }
            }*/

    string Platillo::toString(){
        string cadena;
        cadena = "Id Platillo: " + to_string(idPlatillo) + " " " " + " Nombre Platillo: " + nombrePlatillo + " " " " + fechaRegistrado.toString() + " " " " + " Ingredientes: " + ingredientes + " " " " + " Orientacion alimentaria: " + nombreOrientacion;
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



       /// Funciones globales para gestionar Platillos
    bool nuevoPlatillo(){
        Platillo reg;
        reg = cargarPlatillo();
        bool ok = reg.GrabarEnDisco();
        return ok;
    }

     int CantidadRegistrosPlatillo(){
        FILE *p;
        p=fopen("Platillos.dat", "rb");
            if(p==NULL){
              return 0;
            }
            size_t bytes;
            int cantidad;

            fseek(p, 0, SEEK_END);
            bytes=ftell(p);

            fclose(p);
         cantidad = bytes/sizeof(Platillo);
         return cantidad;
     }

    Platillo cargarPlatillo(){
        int id;
        string nombrePlatillo;
        int dia,mes, anio;
        string ingredientes;
        string nombreOrientacion;
        bool estado = true;

        id = CantidadRegistrosPlatillo()+1;
        Platillo reg;

        cout << "Ingrese el nombre del platillo: ";
        cin>>nombrePlatillo;
        //getline(cin, nombrePlatillo);
        //cin.ignore();
        //scanf("%s", nombrePlatillo);
        //ver como resolver que tome todas las letras con espacios

        cout<<"Ingrese el dia: ";
        cin>>dia;
        cout<<"Ingrese el mes: ";
        cin>>mes;
        cout<<"Ingrese el anio: ";
        cin>>anio;
        cout<<endl;
        listarProductos();
        cout<<endl;
        cout << "Ingrese el nombre del ingrendiente o 0 para no agregar mas: ";
        cin >> ingredientes;


        while(ingredientes != "0"){
            reg.setIngredientes(ingredientes);
            cout << "Ingrese el nombre del ingrendiente: ";
            cin>>ingredientes;
        }
        cout<<endl;
        listarOrientacionAlimentaria();
        cout<<endl;
        cout << "Ingrese el nombre de la orienteacion: ";
        cin >> nombreOrientacion;

        Fecha fecha(dia, mes, anio);
        reg.setIdPlatillo(id);
        reg.setNombrePlatillo(nombrePlatillo);
        reg.setFechaRegistrado(fecha);
        reg.setNombreOrientacion(nombreOrientacion);
        reg.setEstadoPlatillo(estado);
        cout<<endl;
        cout<<endl;
        system("pause");
        return reg;
    }


    void listarPlatillos(){
        Platillo aux;
        int cantPlatillos = CantidadRegistrosPlatillo();
    cout << "LISTADO DE PLATILLOS" << endl;
    cout << "----------------------------------" << endl;
        for(int i=0; i<cantPlatillos; i++){
            aux.LeerDeDisco(i);
            if(aux.getEstadoPlatillo()){
                cout<<aux.toString()<<endl;
            }
        }
        cout << "----------------------------------" << endl;
        cout << "Total: " << cantPlatillos << " platillos.";
        cout<<endl;
        cout<<endl;
        system("pause");
    }


  void menuPlatillo(){
   int opc;
    while(true){
        system("cls");

        cout<<"MENU PLATILLO"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. AGREGAR PLATILLO "<<endl;
        cout<<"2. LISTAR PLAILLOS "<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: "<<endl;
        cin>>opc;

        system("cls");

        switch(opc){
            case 1:   if(nuevoPlatillo()){
                            cout<<endl;
                            cout<<"PLATILLO AGREGADO";
                            cout<<endl;
                            system("pause");
                        }else {
                             cout<<endl;
                            cout<<"NO SE PUDO AGREGAR EL PLATILLO";
                            cout<<endl;
                            system("pause");
                        }
                break;
            case 2: listarPlatillos();
                break;
            case 0: return;
                    break;
        }
        cout<<endl;
    }
  }
