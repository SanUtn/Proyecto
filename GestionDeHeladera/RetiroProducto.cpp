#include <iostream>
#include <iomanip>
#include "rlutil.h"
#include "RetiroProducto.h"
#include "Producto.h"
#include "ProductoStock.h"
#include "Usuario.h"
#include "FuncionesGlobales.h"

using namespace std;

string RetiroProducto::toString()
{
    string cadena;
    cadena= "Id Retiro: " + to_string(idRetiro) + " " " " + " Dni del Usuario: " + to_string(dniUsuario) + " " " " + " Id Producto: " + to_string(idProducto) + " " " " + " Fecha retiro: " + fechaRetiro.toString();
    return cadena;
}

bool RetiroProducto::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("RetirosProductos.dat", "rb");
    if(p==NULL)
    {
        return false;
    }
    fseek(p, pos*sizeof(RetiroProducto),0);
    leyo=fread(this,sizeof(RetiroProducto),1,p);

    fclose(p);

    return leyo;
}

bool RetiroProducto::GrabarEnDisco()
{
    FILE *p;
    p=fopen("RetirosProductos.dat", "ab");
    if(p==NULL)
    {
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    int escribio=fwrite(this, sizeof(RetiroProducto),1,p);
    fclose(p);

    return escribio;
}



//METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
//HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
bool RetiroProducto::ModificarArchivo(int pos)
{
    FILE *p;
    p=fopen("RetirosProductos.dat", "rb+");
    if(p==NULL)
    {
        return false;
    }
    fseek(p, pos*sizeof(RetiroProducto),0);
    int escribio=fwrite(this, sizeof(RetiroProducto),1,p);
    fclose(p);

    return escribio;
}


/// Funciones globales para gestionar Producto

//para retirar productos desde consumos
bool retirarProducto(int idproducto)
{
    bool ok;
    RetiroProducto reg;
    reg = retirarProductoExistente(idproducto);
    if(reg.getIdRetiro() != -1){
        ok= reg.GrabarEnDisco();
    }else{
        ok = false;
    }
    return ok;
}

//para retirar producto desde productos
bool retirarProductoManual()
{
    bool ok;
    RetiroProducto reg;
    reg = retirarProductoExistenteManual();
    if(reg.getIdRetiro() != -1){
        ok= reg.GrabarEnDisco();
    }else{
        ok = false;
    }
    return ok;
}


int CantidadRegistrosRetiroProductosExistentes()
{
    FILE *p;
    p=fopen("RetirosProductos.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    size_t bytes;
    int cantidad;

    fseek(p, 0, SEEK_END);
    bytes=ftell(p);

    fclose(p);
    cantidad = bytes/sizeof(RetiroProducto);
    return cantidad;
}

RetiroProducto retirarProductoExistenteManual()
{
    int id;
    int dniUsuario;
    int idProducto;
    int dia, mes, anio;

    id = CantidadRegistrosRetiroProductosExistentes()+1;

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

    cout << "Ingrese el dia: ";
    cin >> dia;
    cout << "Ingrese el mes: ";
    cin >> mes;
    cout << "Ingrese el anio: ";
    cin >> anio;

    RetiroProducto reg;

    //se encuentra en productos stock, da de baja 1 cantidad de ese producto.
    if(retirarProductoDelStock(idProducto))
    {
        Fecha fecha(dia, mes, anio);
        reg.setIdRetiro(id);
        reg.setDniUsuario(dniUsuario);
        reg.setIdProducto(idProducto);
        reg.setFechaRetiro(fecha);
    }
    else
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "No hay stock del producto seleccionado" << endl;
        reg.setIdRetiro(-1);
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    cout<<endl;
    cout<<endl;
    return reg;
}

RetiroProducto retirarProductoExistente(int idproducto)
{
    int id;
    int dniUsuario;

    id = CantidadRegistrosRetiroProductosExistentes()+1;

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

    while(validarProductoExistenteID(idproducto) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "El ID de producto que ingreso no existe en el sistema, ingrese otro:  ";
        cin >> idproducto;
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    RetiroProducto reg;

    Fecha fecha;
    reg.setIdRetiro(id);
    reg.setDniUsuario(dniUsuario);
    reg.setIdProducto(idproducto);
    reg.setFechaRetiro(fecha);

    cout<<endl;
    cout<<endl;
    return reg;
}

//cuando se consume un platillo se genera el retiro de cada producto.
bool retirarProductoExistentePorConsumo(int idplatillo, int usuario)
{
    int id;
    int idProducto;
    int cantProductos = CantidadProductosxPlatillo(idplatillo);

    Producto *vDinamico;

    vDinamico = new Producto[cantProductos];

       if(vDinamico == NULL)
            {
                rlutil::setColor(rlutil::RED);
                cout << "ERROR" <<endl;
                rlutil::setColor(rlutil::BROWN);
                return false;
            }

    //LLENA EL VECTOR CON LOS PRODUCTOS DE ESE PLATILLO
    copiarProductos(vDinamico,cantProductos, idplatillo);

    RetiroProducto reg;
    Fecha fecha;

    for(int i=0; i<cantProductos;i++){
        id = CantidadRegistrosRetiroProductosExistentes()+1;
        reg.setIdRetiro(id);
        reg.setDniUsuario(usuario);
        reg.setIdProducto(vDinamico[i].getIdProducto());
        reg.setFechaRetiro(fecha);
        if(reg.GrabarEnDisco() == false){
            return false;
        }
    }

    return true;
}


void listarRetirosDeProductosExistentes()
{
    RetiroProducto aux;
    int cantProductos = CantidadRegistrosRetiroProductosExistentes();

    rlutil::setColor(rlutil::MAGENTA);
    cout<<endl;
    cout << left;
     cout << setw(12) << "\t";
    cout <<  "LISTADO DE PRODUCTOS RETIRADOS " << endl;
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
            cout << setw(10) << to_string(aux.getIdRetiro());
            cout << setw(10) << to_string(aux.getDniUsuario());
            cout << setw(20) << mostrarNombreProducto(aux.getIdProducto());
            cout << setw(20) << aux.getFechaRetiro().toString() << endl;
    }
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-------------------------------------------------" << endl;
    cout << "\t" << "Total: " << cantProductos << " registros.";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
}


