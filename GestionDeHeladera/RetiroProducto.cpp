#include <iostream>
#include <iomanip>
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
        cout<<"El archivo no pudo abrirse"<<endl;
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
bool retirarProducto()
{
    bool ok;
    RetiroProducto reg;
    reg = retirarProductoExistente();
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

RetiroProducto retirarProductoExistente()
{
    int id;
    int dniUsuario;
    int idProducto;
    int dia, mes, anio;

    id = CantidadRegistrosRetiroProductosExistentes()+1;

    cout << "Ingrese el dni del Usuario: ";//esto despues no iria porque lo tomaría de la sesión
    cin >> dniUsuario;

    while(validarUsuarioExistente(dniUsuario) == false)
    {
        cout << "El usuario ingresado no existe en el sistema, ingrese otro DNI:  ";//esto despues no iria porque lo tomaría de la sesión
        cin >> dniUsuario;
    }

    cout<<endl;
    listarProductos();
    cout<<endl;
    cout<<"Ingrese el id del Producto: ";
    cin>>idProducto;

    while(validarProductoExistenteID(idProducto) == false)
    {
        cout << "El ID de producto que ingreso no existe en el sistema, ingrese otro:  ";
        cin >> idProducto;
    }

    //ver si cargamos la fecha o tomamos la actual
    cout << "Ingrese el dia: ";
    cin >> dia;
    cout << "Ingrese el mes: ";
    cin >> mes;
    cout << "Ingrese el anio: ";
    cin >> anio;

    RetiroProducto reg;

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
        cout << "No hay stock del producto seleccionado" << endl;
        reg.setIdRetiro(-1);
    }

    cout<<endl;
    cout<<endl;
    return reg;
}

bool retirarProductoExistentePorConsumo(int idplatillo, int usuario)
{
    int id;
    int idProducto;
    int cantProductos = CantidadProductosxPlatillo(idplatillo);

    Producto *vDinamico;

    vDinamico = new Producto[cantProductos];

       if(vDinamico == NULL)
            {
                cout << "ERROR" <<endl;
                return false;
            }

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
    cout << left;
    cout << setw(5) << "\t";
    cout <<  "LISTADO DE PRODUCTOS RETIRADOS " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << left;
    cout << setw(4)  <<"Id";
    cout << setw(10) <<"Usuario";
    cout << setw(15) <<"Producto";
    cout << setw(15)  <<"Fecha" << endl;
    cout << "---------------------------------------------------" << endl;
    for(int i=0; i<cantProductos; i++)
    {
            aux.LeerDeDisco(i);
            cout << left;
            cout << setw(4) << to_string(aux.getIdRetiro());
            cout << setw(10) << to_string(aux.getDniUsuario());
            cout << setw(15) << mostrarNombreProducto(aux.getIdProducto());
            cout << setw(15) << aux.getFechaRetiro().toString() << endl;
    }
    cout << "---------------------------------------------------" << endl;
    cout << "Total: " << cantProductos << " registros.";
    cout<<endl;
    cout<<endl;
}


