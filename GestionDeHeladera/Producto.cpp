#include <iostream>
#include <iomanip>
#include "rlutil.h"
#include "Producto.h"
#include "ProductoStock.h"
#include "IngresoProducto.h"
#include "RetiroProducto.h"
#include "FuncionesGlobales.h"
#include "Usuario.h"

using namespace std;


string Producto::getNombreProducto()
{
    string nombreProductos;
    nombreProductos = nombreProducto;
    return nombreProductos;
}

string Producto::toString()
{
    string cadena;
    cadena = "Id: " + to_string(idProducto) + " " " " + " Nombre: " + nombreProducto  + " " " " + " Fecha vencimiento: " + fechaVencimiento.toString();;
    return cadena;
}

void Producto::toList()
{
    rlutil::setColor(rlutil::LIGHTCYAN);
    cout << left;
    cout << "\t";
    cout << setw(10) << getIdProducto();
    cout << setw(20) << getNombreProducto();
    cout << setw(20) << getFechaVencimiento().toString() << endl;
    rlutil::setColor(rlutil::BROWN);
}

bool Producto::operator == (Fecha fecha)
{
    if(fechaVencimiento.getDia()== fecha.getDia() && fechaVencimiento.getMes()== fecha.getMes() && fechaVencimiento.getAnio()== fecha.getAnio())
    {
        return true;
    }
    return false;
}

bool Producto::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("Productos.dat", "rb");
    if(p==NULL)
    {
        return false;
    }
    fseek(p, pos*sizeof(Producto),0);
    leyo=fread(this,sizeof(Producto),1,p);

    fclose(p);
    return leyo;
}

bool Producto::GrabarEnDisco()
{
    FILE *p;
    p=fopen("Productos.dat", "ab");
    if(p==NULL)
    {
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    int escribio=fwrite(this, sizeof(Producto),1,p);
    fclose(p);

    return escribio;
}



//METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
//HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
bool Producto::ModificarArchivo(int pos)
{
    FILE *p;
    p=fopen("Productos.dat", "rb+");
    if(p==NULL)
    {
        return false;
    }
    fseek(p, pos*sizeof(Producto),0);
    int escribio=fwrite(this, sizeof(Producto),1,p);
    fclose(p);

    return escribio;
}

/// Funciones globales para gestionar Producto
bool nuevoProducto()
{
    Producto reg;
    reg = cargarProducto();
    bool ok = reg.GrabarEnDisco();
    return ok;
}

int CantidadRegistrosProductos()
{
    FILE *p;
    p=fopen("Productos.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    size_t bytes;
    int cantidad;

    fseek(p, 0, SEEK_END);
    bytes=ftell(p);

    fclose(p);
    cantidad = bytes/sizeof(Producto);
    return cantidad;
}

Producto cargarProducto()
{
    int id;
    string nombre;
    int dia, mes, anio, dniUsuario;
    bool estado = true;

    id = CantidadRegistrosProductos()+1;

    cout << "Ingrese el dni del Usuario: ";
    cin >> dniUsuario;

    while(validarNumero())
    {
        cin >> dniUsuario;
    }

    while(validarUsuarioExistente(dniUsuario) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "El usuario ingresado no existe en el sistema, ingrese otro DNI:  ";
        cin >> dniUsuario;
        cout<<endl;
        while(validarNumero())
        {
            cin >> dniUsuario;
        }
        rlutil::setColor(rlutil::BROWN);

    }

    cout << "Ingrese el nombre del Producto: ";
    cin.ignore();
    getline(cin, nombre);
    nombre = mayuscula(nombre);

    while(validarProductoExistente(nombre))
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout <<"Producto ya ingresado, ingrese otro: ";
        getline(cin, nombre);
        nombre = mayuscula(nombre);
        rlutil::setColor(rlutil::BROWN);
        cout<<endl;
    }

    cout << "Ingrese el dia vencimiento: ";
    cin >> dia;
    cout << "Ingrese el mes vencimiento: ";
    cin >> mes;
    cout << "Ingrese el anio vencimiento: ";
    cin >> anio;

    Fecha fechaVencimiento(dia,mes,anio);
    Fecha fecha;
    Producto reg;
    reg.setIdProducto(id);
    reg.setNombreProducto(nombre);
    reg.setFechaVencimiento(fechaVencimiento);
    reg.setEstadoProducto(estado);

    //agrega producto al stock
    agregarProductoNuevoAlStock(id);
    //genera el ingreso
    agregarIngresoDesdeNuevoProducto(id, dniUsuario, fecha);

    cout<<endl;
    cout<<endl;
    //system("pause");
    return reg;
}

bool validarProductoExistente(string n)
{
    Producto aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {

        if(aux.getNombreProducto() == n && aux.getEstadoProducto() == true)
        {
            return true;
        }
        pos++;
    }
    return false;
}

//valida el id de producto
bool validarProductoExistenteID(int id)
{
    Producto aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if(aux.getIdProducto() == id && aux.getEstadoProducto() == true)
        {
            return true;
        }
        pos++;
    }
    return false;
}

void listarProductos()
{
    Producto aux;
    int cont=0;
    int cantProductos = CantidadRegistrosProductos();

    rlutil::setColor(rlutil::MAGENTA);
    cout<<endl;
    cout << left;
    cout << setw(16) << "\t";
    cout << "PRODUCTOS" << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-----------------------------------------" << endl;
    cout << "\t";
    cout << setw(10)  << "ID";
    cout << setw(20) << "NOMBRE";
    cout << setw(20) << "VENCIMIENTO"<<endl;
    cout << "\t" << "-----------------------------------------" << endl;

    for(int i=0; i<cantProductos; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoProducto())
        {
            rlutil::setColor(rlutil::LIGHTCYAN);
            cout << left;
            cout << "\t";
            cout << setw(10) << aux.getIdProducto();
            cout << setw(20) << aux.getNombreProducto();
            cout << setw(20) << aux.getFechaVencimiento().toString() << endl;
        }
        else
        {
            cont++;
        }
    }
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-----------------------------------------" << endl;
    cout << "\t" << "Total: " << cantProductos - cont<< " Productos.";
    rlutil::setColor(rlutil::BROWN);
    cout<<endl;
    cout<<endl;
}

int EliminarProducto()
{
    Producto aux;
    int pos=0, idproducto;

    listarProductos();
    cout<<endl;

    cout<<"Ingrese el ID del producto a eliminar: ";
    cin>>idproducto;

    cout << endl;

         while(validarNumero())
        {
            cin >> idproducto;
        }

    while(aux.LeerDeDisco(pos)==1)
    {
        if(aux.getIdProducto() == idproducto && aux.getEstadoProducto() == true)
        {
            aux.setEstadoProducto(false);
            bool modifico = aux.ModificarArchivo(pos);
            if (modifico)
            {
                //al eliminar el producto se elimina de stock, de platillo y de recetas
                eliminarStock(idproducto);
                eliminarPlatillos(idproducto);
            }
            return pos;
        }
        pos++;
    }
    return -1;
}

void buscarProducto()
{
    Producto aux;
    int pos = 0;
    string nombre;
    bool bandera = false;

    cout << "Ingrese el nombre del Producto a buscar: ";
    cin.ignore();
    getline(cin, nombre);
    nombre = mayuscula(nombre);

    system("cls");
    rlutil::setColor(rlutil::MAGENTA);
    cout<<endl;
    cout << left;
    cout << setw(16) << "\t";
    cout << "PRODUCTOS" << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-----------------------------------------" << endl;
    cout << left;
    cout << "\t";
    cout << setw(10) << "ID";
    cout << setw(20) << "PRODUCTO";
    cout << setw(20) << "VENCIMIENTO" << endl;
    cout << "\t" << "-----------------------------------------" << endl;

    while(aux.LeerDeDisco(pos))
    {
        if(aux.getNombreProducto() == nombre && aux.getEstadoProducto())
        {
            aux.toList();
            bandera = true;
        }
        pos++;
    }

    if(bandera == false)
    {
        system("cls");
        cout<<endl;
        rlutil::setColor(rlutil::RED);
        cout << "No hay productos con ese nombre." << endl;
        rlutil::setColor(rlutil::BROWN);
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
}

void menuProducto()
{
    int opc;
    while(true)
    {
        system("cls");
        rlutil::locate(56, 5);
        rlutil::setColor(rlutil::CYAN);
        cout<<"MENU PRODUCTO"<<endl;
        rlutil::locate(40, 6);
        cout<<"----------------------------------------------"<<endl;
        rlutil::locate(48, 8);
        rlutil::setColor(rlutil::LIGHTCYAN);
        cout<<"1. AGREGAR PRODUCTO "<<endl;
        rlutil::locate(48, 9);
        cout<<"2. ELIMINAR PRODUCTO "<<endl;
        rlutil::locate(48, 10);
        cout<<"3. INGRESAR PRODUCTO EXISTENTE "<<endl;
        rlutil::locate(48, 11);
        cout<<"4. RETIRAR PRODUCTO EXISTENTE "<<endl;
        rlutil::locate(48, 12);
        cout<<"5. LISTAR PRODUCTOS "<<endl;
        rlutil::locate(48, 13);
        cout<<"6. LISTAR INGRESOS DE PRODUCTOS "<<endl;
        rlutil::locate(48, 14);
        cout<<"7. LISTAR RETIROS DE PRODUCTOS "<<endl;
        rlutil::locate(48, 15);
        cout<<"8. BUSCAR PRODUCTO "<<endl;
        rlutil::locate(48, 16);
        cout<<"-------------------------------"<<endl;
        rlutil::locate(48, 17);
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        rlutil::locate(48, 20);
        rlutil::setColor(rlutil::DARKGREY);
        cout<<"OPCION: ";
        cin>>opc;

        rlutil::setColor(rlutil::BROWN);
        system("cls");

        switch(opc)
        {
        case 1:
            if(nuevoProducto())
            {
                cout<<endl;
                rlutil::setColor(rlutil::GREEN);
                cout<<"PRODUCTO AGREGADO";
                rlutil::setColor(rlutil::BROWN);
                cout<<endl;
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                rlutil::setColor(rlutil::RED);
                cout<<"NO SE PUDO AGREGAR EL PRODUCTO";
                rlutil::setColor(rlutil::BROWN);
                cout<<endl;
                cout<<endl;
                system("pause");
            }
            break;
        case 2:
            if(EliminarProducto()!= -1)
            {
                cout<<endl;
                rlutil::setColor(rlutil::GREEN);
                cout<<"PRODUCTO ELIMINADO";
                rlutil::setColor(rlutil::BROWN);
                cout<<endl;
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                rlutil::setColor(rlutil::RED);
                cout<<"NO SE PUDO ELIMINAR EL PRODUCTO";
                rlutil::setColor(rlutil::BROWN);
                cout<<endl;
                cout<<endl;
                system("pause");
            }
            break;
        case 3:
            if(ingresarProducto())
            {
                cout<<endl;
                rlutil::setColor(rlutil::GREEN);
                cout<<"PRODUCTO AGREGADO";
                rlutil::setColor(rlutil::BROWN);
                cout<<endl;
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                rlutil::setColor(rlutil::RED);
                cout<<"NO EXISTE EL PRODUCTO";
                rlutil::setColor(rlutil::BROWN);
                cout<<endl;
                cout<<endl;
                system("pause");
            }
            break;

        case 4:
            if(retirarProductoManual())
            {
                cout<<endl;
                rlutil::setColor(rlutil::GREEN);
                cout<<"PRODUCTO RETIRADO";
                rlutil::setColor(rlutil::BROWN);
                cout<<endl;
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                rlutil::setColor(rlutil::RED);
                cout<<"NO SE PUDO RETIRAR EL PRODUCTO";
                rlutil::setColor(rlutil::BROWN);
                cout<<endl;
                cout<<endl;
                system("pause");
            }
            break;
        case 5:
            listarProductos();
            system("pause");
            break;
        case 6:
            listarIngresosDeProductosExistentes();
            system("pause");
            break;
        case 7:
            listarRetirosDeProductosExistentes();
            system("pause");
            break;
        case 8:
            buscarProducto();
            system("pause");
            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}
