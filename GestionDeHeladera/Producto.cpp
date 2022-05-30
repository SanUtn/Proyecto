#include <iostream>
#include "Producto.h"
#include "IngresoProducto.h"
#include "RetiroProducto.h"

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
    cadena = "Id del producto: " + to_string(idProducto) + " " " " + " Nombre del Producto: " + nombreProducto;/*" Dni del Usuario: " + to_string(dniUsuario) + " " " " + " Fecha ingreso: " + fechaIngreso.toString();*/
    return cadena;
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
        cout<<"El archivo no pudo abrirse"<<endl;
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
    //int dniUsuario; //ver de hacer que lo tome de la sesion.
    //int dia, mes, anio;
    bool estado = true;

    id = CantidadRegistrosProductos()+1;

    cout << "Ingrese el nombre del Producto: ";
    cin.ignore();
    getline(cin, nombre);

    while(validarProductoExistente(nombre))
    {
        cout <<"Producto ya ingresado, ingrese otro: ";
        cin.ignore();
        getline(cin, nombre);

    }
    /*cout << "Ingrese el dni del Usuario: ";
    //cin >> dniUsuario;
    cout << "Ingrese el dia: ";
    cin >> dia;
    cout << "Ingrese el mes: ";
    cin >> mes;
    cout << "Ingrese el anio: ";
    cin >> anio;

    Fecha fecha(dia, mes, anio);*/
    Producto reg;
    reg.setIdProducto(id);
    reg.setNombreProducto(nombre);
    //reg.setDniUsuario(dniUsuario);
    //reg.setFechaIngreso(fecha);
    reg.setEstadoProducto(estado);
    cout<<endl;
    cout<<endl;
    system("pause");
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

void listarProductos()
{
    Producto aux;
    int cont=0;
    int cantProductos = CantidadRegistrosProductos();
    cout << "LISTADO DE PRODUCTOS" << endl;
    cout << "----------------------------------" << endl;
    for(int i=0; i<cantProductos; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoProducto())
        {
            cout<<aux.toString()<<endl;
        }else{
         cont++;
        }
    }
    cout << "----------------------------------" << endl;
    cout << "Total: " << cantProductos - cont<< " Productos.";
    cout<<endl;
    cout<<endl;
    //system("pause");
}

int EliminarProducto()
{
    Producto aux;
    int pos=0, idproducto;

    listarProductos();
    cout<<endl;

    cout<<"Ingrese el ID del producto a eliminar: ";
    cin>>idproducto;

    while(aux.LeerDeDisco(pos)==1)
    {
        if(aux.getIdProducto() == idproducto)
        {
            aux.setEstadoProducto(false);
            aux.ModificarArchivo(pos);
            return pos;
        }
        pos++;
    }
    return -1;
}


void menuProducto()
{
    int opc;
    while(true)
    {
        system("cls");

        cout<<"MENU PRODUCTO"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. AGREGAR PRODUCTO "<<endl;
        cout<<"2. ELIMINAR PRODUCTO "<<endl;
        cout<<"3. INGRESAR PRODUCTO EXISTENTE "<<endl;
        cout<<"4. RETIRAR PRODUCTO EXISTENTE "<<endl;
        cout<<"5. LISTAR PRODUCTOS "<<endl;
        cout<<"6. LISTAR INGRESOS DE PRODUCTOS "<<endl;
        cout<<"7. LISTAR RETIROS DE PRODUCTOS "<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: "<<endl;
        cin>>opc;

        system("cls");

        switch(opc)
        {
        case 1:
            if(nuevoProducto())
            {
                cout<<endl;
                cout<<"PRODUCTO AGREGADO";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO AGREGAR EL PRODUCTO";
                cout<<endl;
                system("pause");
            }
            break;
        case 2:
            if(EliminarProducto()!= -1)
            {
                cout<<endl;
                cout<<"PRODUCTO ELIMINADO";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO ELIMINAR EL PRODUCTO";
                cout<<endl;
                system("pause");
            }
            break;
        case 3:  if(ingresarProducto())
            {
                cout<<endl;
                cout<<"PRODUCTO AGREGADO";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO EXISTE EL PRODUCTO";
                cout<<endl;
                system("pause");
            }
            break;

        case 4:  if(retirarProducto())
            {
                cout<<endl;
                cout<<"PRODUCTO RETIRADO";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO EXISTE EL PRODUCTO";
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
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}
