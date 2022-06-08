#include <iostream>
#include "ConsumoPlatillo.h"
#include "Platillo.h"
#include "ProductoStock.h"
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

    cout << "Ingrese el id del Producto: ";
    cin >> id;
    cout<<endl;

    ConsumoPlatillo reg;
    Fecha actual;
    reg.setIdPlatillo(id);
    reg.setFechaConsumo(actual);
    cout<<endl;
    cout<<endl;
    system("pause");
    return reg;
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


