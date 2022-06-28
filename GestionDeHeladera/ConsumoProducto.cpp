#include <iostream>
#include <iomanip>
#include "rlutil.h"
#include "ConsumoProducto.h"
#include "Producto.h"
#include "ProductoStock.h"
#include "RetiroProducto.h"
#include "FuncionesGlobales.h"

using namespace std;


string ConsumoProducto::toString()
{
    string cadena;
    cadena = "Id del Producto: " + to_string(idProducto) + " " " " + " Fecha consumo: " + fechaConsumo.toString();
    return cadena;
}

void ConsumoProducto::toList(){
            rlutil::setColor(rlutil::LIGHTCYAN);
            cout << left;
            cout << "\t";
            cout << setw(15)  << mostrarNombreProducto(getIdProducto());
            cout << setw(15) << getFechaConsumo().toString() << endl;
            rlutil::setColor(rlutil::BROWN);
}


bool ConsumoProducto::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("ConsumosProductos.dat", "rb");
    if(p==NULL)
    {
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    fseek(p, pos*sizeof(ConsumoProducto),0);
    leyo=fread(this,sizeof(ConsumoProducto),1,p);

    fclose(p);

    return leyo;
}

bool ConsumoProducto::GrabarEnDisco()
{
    FILE *p;
    p=fopen("ConsumosProductos.dat", "ab");
    if(p==NULL)
    {
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    int escribio=fwrite(this, sizeof(ConsumoProducto),1,p);
    fclose(p);

    return escribio;
}



//METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
//HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
bool ConsumoProducto::ModificarArchivo(int pos)
{
    FILE *p;
    p=fopen("ConsumosProductos.dat", "rb+");
    if(p==NULL)
    {
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    fseek(p, pos*sizeof(ConsumoProducto),0);
    int escribio=fwrite(this, sizeof(ConsumoProducto),1,p);
    fclose(p);

    return escribio;
}



/// Funciones globales para gestionar el consumo de un producto
bool nuevoConsumoProducto()
{
    ConsumoProducto reg;
    reg = cargarConsumoProducto();
    bool ok = reg.GrabarEnDisco();
    if(ok)
    {
        int producto= reg.getIdProducto();
        if(retirarProductoDelStockConsumoProducto(producto))
        {
            ok = retirarProducto(reg.getIdProducto());
        }
    }
    return ok;
}

int CantidadRegistrosConsumoProducto()
{
    FILE *p;
    p=fopen("ConsumosProductos.dat", "rb");
    if(p==NULL)
    {
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

ConsumoProducto cargarConsumoProducto()
{
    int id;
    Fecha fecha;

    listarProductos();

    cout << "Ingrese el id del Producto: ";
    cin >> id;
    cout<<endl;

    //validamos que exista ese producto
    while(buscarProducto(id) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "Producto inexistente, ingrese otro: ";
        cin >> id;
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    while(validarExistenciaDeProductosParaConsumo(id)== false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "Lo sentimos, no hay stock de ese producto o no existe, ingrese otro: ";
        cin >> id;
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    ConsumoProducto reg;
    reg.setIdProducto(id);
    reg.setFechaConsumo(fecha);
    cout<<endl;
    cout<<endl;
    //system("pause");
    return reg;
}


bool validarExistenciaDeProductosParaConsumo(int idproducto)
{
    bool bandera = true;

    if(buscarProducto(idproducto))
    {
        if(consultarStock(idproducto) == 0)
        {
            bandera = false;
        }
    }
    else
    {
        bandera = false;
    }
    return bandera;
}

void listarConsumosPoductos()
{
    ConsumoProducto aux;
    int cantConsumoProducto = CantidadRegistrosConsumoProducto();

    if(cantConsumoProducto != 0)
    {
        rlutil::setColor(rlutil::MAGENTA);
        cout<<endl;
        cout<<endl;
        cout << left;
        cout << setw(7) << "\t";
        cout << "CONSUMOS PRODUCTO" << endl;
        rlutil::setColor(rlutil::DARKGREY);
        cout << "\t" << "----------------------------" << endl;
        cout << left;
        cout << "\t";
        cout << setw(15)  << "PRODUCTO";
        cout << setw(15) << "FECHA CONSUMO" << endl;
        cout << "\t" << "----------------------------" << endl;
        for(int i=0; i<cantConsumoProducto; i++)
        {
            aux.LeerDeDisco(i);
            aux.toList();
        }

    }
    else
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "No hay consumos de productos registrados." << endl;
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
    system("pause");
}


