#include <iostream>
#include "ConsumoProducto.h"
#include "Producto.h"
#include "ProductoStock.h"

using namespace std;


    string ConsumoProducto::toString(){
        string cadena;
        cadena = "Id del Producto: " + to_string(idProducto) + " " " " + " Fecha consumo: " + fechaConsumo.toString();
        return cadena;
    }


     bool ConsumoProducto::LeerDeDisco(int pos){
        FILE *p;
        int leyo;
        p=fopen("ConsumosProductos.dat", "rb");
            if(p==NULL){
              cout<<"El archivo no pudo abrirse"<<endl;
              return false;
            }
        fseek(p, pos*sizeof(ConsumoProducto),0);
        leyo=fread(this,sizeof(ConsumoProducto),1,p);

        fclose(p);

        return leyo;
    }

     bool ConsumoProducto::GrabarEnDisco(){
        FILE *p;
        p=fopen("ConsumosProductos.dat", "ab");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          return false;
        }
        int escribio=fwrite(this, sizeof(ConsumoProducto),1,p);
        fclose(p);

        return escribio;
     }



    //METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
    //HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
      bool ConsumoProducto::ModificarArchivo(int pos){
        FILE *p;
        p=fopen("ConsumosProductos.dat", "rb+");
        if(p==NULL){
          cout<<"El archivo no pudo abrirse"<<endl;
          return false;
        }
        fseek(p, pos*sizeof(ConsumoProducto),0);
        int escribio=fwrite(this, sizeof(ConsumoProducto),1,p);
        fclose(p);

        return escribio;
     }



    /// Funciones globales para gestionar el consumo de un producto
    bool nuevoConsumoProducto(){
        ConsumoProducto reg;
        reg = cargarConsumoProducto();
        bool ok = reg.GrabarEnDisco();
        if(ok){
            int producto= reg.getIdProducto();
            ok = retirarProductoDelStockConsumoProducto(producto);
        }
        return ok;
    }

     int CantidadRegistrosConsumoProducto(){
        FILE *p;
        p=fopen("ConsumosProductos.dat", "rb");
            if(p==NULL){
              return 0;
            }
            size_t bytes;
            int cantidad;

            fseek(p, 0, SEEK_END);
            bytes=ftell(p);

            fclose(p);
         cantidad = bytes/sizeof(ConsumoProducto);
         return cantidad;
     }

    ConsumoProducto cargarConsumoProducto(){
        int id;
        Fecha fecha;

        listarProductos();

        cout << "Ingrese el id del Producto: ";
        cin >> id;
        cout<<endl;

        //validamos que exista ese producto
        while(buscarProducto(id) == false)
        {
        cout << "Producto inexistente, ingrese otro: ";
        cin >> id;
        cout<<endl;
        }

        while(validarExistenciaDeProductosParaConsumo(id)== false)
        {
        cout << "Lo sentimos, no hay stock de ese producto o no existe, ingrese otro: ";
        cin >> id;
        cout<<endl;
        }

        ConsumoProducto reg;
        reg.setIdProducto(id);
        reg.setFechaConsumo(fecha);
        cout<<endl;
        cout<<endl;
        system("pause");
        return reg;
    }


    bool validarExistenciaDeProductosParaConsumo(int idproducto)
    {
        bool bandera = true;

        if(buscarProducto(idproducto))
        {
            cout<<"Esto tiene bandera"<<bandera<<endl;
            if(consultarStock(idproducto) == 0)
            {
                bandera = false;
                cout<<"Esto tiene bandera"<<bandera<<endl;
            }
        } else {
         bandera = false;
        }
        cout<<"Esto tiene bandera"<<bandera<<endl;
      return bandera;
    }

    void listarConsumosPoductos(){
        ConsumoProducto aux;
        int cantConsumoProducto = CantidadRegistrosConsumoProducto();
    cout << "LISTADO DE CONSUMOS PRODUCTOS" << endl;
    cout << "----------------------------------" << endl;
        for(int i=0; i<cantConsumoProducto; i++){
            aux.LeerDeDisco(i);
            cout<<aux.toString()<<endl;
        }
        cout<<endl;
        cout<<endl;
        system("pause");
    }


