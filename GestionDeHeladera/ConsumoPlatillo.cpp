#include <iostream>
#include "ConsumoPlatillo.h"
#include "Platillo.h"
#include "ProductoStock.h"
#include "ProductosxPlatillo.h"
#include "FuncionesGlobales.h"
using namespace std;

string ConsumoPlatillo::toString()
{
    string cadena;
    cadena = "Platillo: " + mostrarNombrePlatillo(idPlatillo) + " " " " + " Fecha consumo: " + getFechaConsumo().toString();
    return cadena;
}


bool ConsumoPlatillo::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("ConsumosPlatillos.dat", "rb");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        return false;
    }
    fseek(p, pos*sizeof(ConsumoPlatillo),0);
    leyo=fread(this,sizeof(ConsumoPlatillo),1,p);

    fclose(p);

  return leyo;
}

bool ConsumoPlatillo::GrabarEnDisco()
{
    FILE *p;
    p=fopen("ConsumosPlatillos.dat", "ab");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
       return false;
    }
    int escribio=fwrite(this, sizeof(ConsumoPlatillo),1,p);
    fclose(p);

    return escribio;
}



//METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
//HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
bool ConsumoPlatillo::ModificarArchivo(int pos)
{
    FILE *p;
    p=fopen("ConsumosPlatillos.dat", "rb+");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
       return false;
    }
    fseek(p, pos*sizeof(ConsumoPlatillo),0);
    int escribio=fwrite(this, sizeof(ConsumoPlatillo),1,p);
    fclose(p);

    return escribio;
}


/// Funciones globales para gestionar el consumo de un platillo
bool nuevoConsumoPlatillo()
{
    ConsumoPlatillo reg;
    reg = cargarConsumoPlatillo();
    bool ok = reg.GrabarEnDisco();
    if(ok){
        int platillo= reg.getIdPlatillo();
        ok = retirarProductoDelStockDesdePlatillo(platillo);
      }
    return ok;
}

int CantidadRegistrosConsumoPlatillo()
{
    FILE *p;
    p=fopen("ConsumosPlatillos.dat", "rb");
    if(p==NULL)
    {
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

ConsumoPlatillo cargarConsumoPlatillo()
{
    int id;

    listarPlatillos();

    cout << "Ingrese el id del Platillo: ";
    cin >> id;
    cout<<endl;

    //validamos que exista ese platillo
    while(buscarPlatillo(id) == false){
       cout << "Platillo inexistente, ingrese otro: ";
       cin >> id;
       cout<<endl;
    }

    while(validarExistenciaDeProductos(id)== false){
        cout << "Lo sentimos, no hay stock de productos para cosumir ese platillo o no existe, ingrese otro: ";
        cin >> id;
        cout<<endl;
    }

    ConsumoPlatillo reg;
    Fecha actual;
    reg.setIdPlatillo(id);
    reg.setFechaConsumo(actual);
    cout<<endl;
    cout<<endl;
    system("pause");
    return reg;
}

bool validarExistenciaDeProductos(int idPlatillo)
{
    bool bandera = true;
    int *vProductos;
    int cantReg = CantidadRegistrosProductosxPlatillos();
    vProductos = new int [cantReg];
     if(vProductos==NULL){return false;}

    if(buscarPlatillo(idPlatillo))
    {
     //llamamos a la funcion para que cargue todos los productos de ese platillo
     buscarProductosXPlatillo(idPlatillo,vProductos,cantReg);

      for(int i=0; i<cantReg; i++)
      {
        //porque algunas posiciones del vector estan vacias, solo va a buscar las que tengan id de productos.

        if(vProductos[i]>0)
        {

            if(consultarStock(vProductos[i]) == 0)
            {
                bandera = false;
            }
        }
      }
    } else {
     bandera = false;
    }
      delete vProductos;
      return bandera;
}

void listarConsumosPlatillo()
{
    ConsumoPlatillo aux;
    int cantConsumoPlatillo = CantidadRegistrosConsumoPlatillo();
    cout << "LISTADO DE CONSUMOS PLATILLOS" << endl;
    cout << "----------------------------------" << endl;
    for(int i=0; i<cantConsumoPlatillo; i++)
    {
        aux.LeerDeDisco(i);
        cout<<aux.toString()<<endl;
    }
    cout<<endl;
    cout<<endl;
    system("pause");
}


