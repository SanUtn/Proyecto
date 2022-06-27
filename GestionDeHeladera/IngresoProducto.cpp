#include<cstdlib>
#include<cstring>
#include <iostream>
#include <iomanip>
#include "rlutil.h"
#include "IngresoProducto.h"
#include "ProductoStock.h"
#include "Usuario.h"
#include "FuncionesGlobales.h"

using namespace std;

string IngresoProducto::toString()
{
    string cadena;
    cadena= "Id Ingreso: " + to_string(idIngreso) + " " " " + " Dni del Usuario: " + to_string(dniUsuario) + " " " " + "Producto: " + to_string(idProducto) + " " " " + " Fecha ingreso: " + fechaIngreso.toString();
    return cadena;
}

bool IngresoProducto::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("IngresosProductos.dat", "rb");
    if(p==NULL)
    {
        return false;
    }
    fseek(p, pos*sizeof(IngresoProducto),0);
    leyo=fread(this,sizeof(IngresoProducto),1,p);

    fclose(p);

    return leyo;
}

bool IngresoProducto::GrabarEnDisco()
{
    FILE *p;
    p=fopen("IngresosProductos.dat", "ab");
    if(p==NULL)
    {
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    int escribio=fwrite(this, sizeof(IngresoProducto),1,p);
    fclose(p);

    return escribio;
}



//METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
//HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
bool IngresoProducto::ModificarArchivo(int pos)
{
    FILE *p;
    p=fopen("IngresosProductos.dat", "rb+");
    if(p==NULL)
    {
        return false;
    }
    fseek(p, pos*sizeof(IngresoProducto),0);
    int escribio=fwrite(this, sizeof(IngresoProducto),1,p);
    fclose(p);

    return escribio;
}



/// Funciones globales para gestionar Producto
bool ingresarProducto()
{
    IngresoProducto reg;
    reg = cargarProductoExistente();
    bool ok = reg.GrabarEnDisco();
    return ok;
}

int CantidadRegistrosProductosExistentes()
{
    FILE *p;
    p=fopen("IngresosProductos.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    size_t bytes;
    int cantidad;

    fseek(p, 0, SEEK_END);
    bytes=ftell(p);

    fclose(p);
    cantidad = bytes/sizeof(IngresoProducto);
    return cantidad;
}

IngresoProducto cargarProductoExistente()
{
    int id;
    int dniUsuario;
    int idProducto;
    int dia, mes, anio;

    id = CantidadRegistrosProductosExistentes()+1;

    cout << "Ingrese el dni del Usuario: ";
    cin >> dniUsuario;

    while(validarUsuarioExistente(dniUsuario) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "El usuario ingresado no existe en el sistema, ingrese otro DNI:  ";
        cin >> dniUsuario;
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    cout<<endl;
    listarProductos();
    cout<<endl;

    cout<<"Ingrese el id del Producto: ";
    cin>>idProducto;

    while(validarProductoExistenteID(idProducto) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "El ID de producto que ingreso no existe en el sistema, ingrese otro:  ";
        cin >> idProducto;
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    cout << "Ingrese el dia vencimiento: ";
    cin >> dia;
    cout << "Ingrese el mes vencimiento: ";
    cin >> mes;
    cout << "Ingrese el anio vencimiento: ";
    cin >> anio;

    Fecha fecha;
    Fecha fechaVencimiento(dia, mes, anio);

    IngresoProducto reg;
    reg.setIdIngreso(id);
    reg.setDniUsuario(dniUsuario);
    reg.setIdProducto(idProducto);
    reg.setFechaIngreso(fecha);
    //agrega al stock de productos el ingresado
    agregarProductoAlStock(idProducto);
    //modificamos el vencimiento del producto
    modificarVencimientoProducto(idProducto, fechaVencimiento);

    cout<<endl;
    cout<<endl;
    //system("pause");
    return reg;
}

//cuando se agrega un nuevo producto tambien se agrega el ingreso de ese producto con el dni del usuario que ingreso.
void agregarIngresoDesdeNuevoProducto(int idProducto, int dni, Fecha fecha)
{

    int id = CantidadRegistrosProductosExistentes()+1;

    IngresoProducto reg;
    reg.setIdIngreso(id);
    reg.setDniUsuario(dni);
    reg.setIdProducto(idProducto);
    reg.setFechaIngreso(fecha);

    reg.GrabarEnDisco();
}


void listarIngresosDeProductosExistentes()
{
    IngresoProducto aux;
    int cantProductos = CantidadRegistrosProductosExistentes();

    rlutil::setColor(rlutil::MAGENTA);
    cout<<endl;
    cout << left;
     cout << setw(16) << "\t";
    cout << "REGISTRO DE INGRESOS " << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-------------------------------------------------" << endl;

    cout << left;
    cout << "\t";
    cout << setw(10)  <<"Id";
    cout << setw(10) <<"Usuario";
    cout << setw(20) <<"Producto";
    cout << setw(20)  <<"Fecha" << endl;

    cout << "\t" << "-------------------------------------------------" << endl;

    for(int i=0; i<cantProductos; i++)
    {
        aux.LeerDeDisco(i);
            rlutil::setColor(rlutil::LIGHTCYAN);
            cout << left;
            cout << "\t";
            cout << setw(10) << aux.getIdIngreso();
            cout << setw(10) << aux.getDniUsuario();
            cout << setw(20) << mostrarNombreProducto(aux.getIdProducto());
            cout << setw(20) << aux.getFechaIngreso().toString() << endl;
    }
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-------------------------------------------------" << endl;
    cout << "\t" << "Total: " << cantProductos << " registros.";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
}


