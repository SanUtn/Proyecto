#include <iostream>
#include "ConsumoPlatillo.h"
#include "Platillo.h"
using namespace std;

    string ConsumoPlatillo::toString(){
        string cadena;
        cadena = "Id del Platillo: " + to_string(idPlatillo) + " " " " + " Fecha consumo: " + fechaConsumo.toString();
        return cadena;
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


     /// Funciones globales para gestionar el consumo de un platillo
    bool nuevoConsumoPlatillo(){
        ConsumoPlatillo reg;
        reg = cargarConsumoPlatillo();
        bool ok = reg.GrabarEnDisco();
        return ok;
    }

     int CantidadRegistrosConsumoPlatillo(){
        FILE *p;
        p=fopen("ConsumoPlatillos.dat", "rb");
            if(p==NULL){
              return 0;
            }
            size_t bytes;
            int cantidad;

            fseek(p, 0, SEEK_END);
            bytes=ftell(p);

            fclose(p);
         cantidad = bytes/sizeof(ConsumoPlatillo);
         return cantidad;
     }

    ConsumoPlatillo cargarConsumoPlatillo(){
        int id;
        Fecha fecha;

        listarPlatillos();

        cout << "Ingrese el id del Producto: ";
        cin >> id;
        cout<<endl;

        ConsumoPlatillo reg;
        reg.setIdPlatillo(id);
        reg.setFechaConsumo(fecha);
        cout<<endl;
        cout<<endl;
        system("pause");
        return reg;
    }


    void listarConsumosPlatillo(){
        ConsumoPlatillo aux;
        int cantConsumoPlatillo = CantidadRegistrosConsumoPlatillo();
    cout << "LISTADO DE CONSUMOS PLATILLOS" << endl;
    cout << "----------------------------------" << endl;
        for(int i=0; i<cantConsumoPlatillo; i++){
            aux.LeerDeDisco(i);
            cout<<aux.toString()<<endl;
        }
        cout<<endl;
        cout<<endl;
        system("pause");
    }


