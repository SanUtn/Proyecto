#include <iostream>
#include <iomanip>
#include "ProductosxPlatillo.h"
#include "Platillo.h"
#include "FuncionesGlobales.h"

using namespace std;

string Platillo::getNombrePlatillo()
{
    string nombrePlatillos;
    nombrePlatillos=nombrePlatillo;
    return nombrePlatillos;
}

string Platillo::toString()
{
    string cadena;
    cadena = "Id: " +
             to_string(idPlatillo) +
             " " " " +
             " Nombre: " +
             nombrePlatillo + " " " " +
             fechaRegistrado.toString() +
             " " " " +
             " Orientacion alimentaria: "
             + mostrarOrientacionAlimentaria(getOrientacionAlimentaria()) + " " " "    + " Calorias: "
             + to_string(calorias);

    return cadena;
}


void Platillo::toList()
{
    cout << left;
    cout << setw(5) << to_string(idPlatillo);
    cout << setw(20) << nombrePlatillo;
    cout << setw(15) << fechaRegistrado.toString();
    cout << setw(20) << mostrarOrientacionAlimentaria(getOrientacionAlimentaria());
    cout << setw(10) << to_string(calorias)<<endl;
}


bool Platillo::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("Platillos.dat", "rb");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        return false;
    }
    fseek(p, pos*sizeof(Platillo),0);
    leyo=fread(this,sizeof(Platillo),1,p);

    fclose(p);

    return leyo;
}

bool Platillo::GrabarEnDisco()
{
    FILE *p;
    p=fopen("Platillos.dat", "ab");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        return false;
    }
    int escribio=fwrite(this, sizeof(Platillo),1,p);
    fclose(p);

    return escribio;
}

//METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
//HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
bool Platillo::ModificarArchivo(int pos)
{
    FILE *p;
    p=fopen("Platillos.dat", "rb+");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        return false;
    }
    fseek(p, pos*sizeof(Platillo),0);
    int escribio=fwrite(this, sizeof(Platillo),1,p);
    fclose(p);

    return escribio;
}

/// Funciones globales para gestionar Platillos
bool nuevoPlatillo()
{
    Platillo reg;
    reg = cargarPlatillo();
    bool ok = reg.GrabarEnDisco();
    return ok;
}

int CantidadRegistrosPlatillo()
{
    FILE *p;
    p=fopen("Platillos.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    size_t bytes;
    int cantidad;

    fseek(p, 0, SEEK_END);
    bytes=ftell(p);

    fclose(p);
    cantidad = bytes/sizeof(Platillo);
    return cantidad;
}

Platillo cargarPlatillo()
{
    int opc;
    int id;
    string nombrePlatillo;
    int dia,mes, anio;
    int orientacionAlimentaria;
    int calorias;
    bool estado = true;

    id = CantidadRegistrosPlatillo()+1;

    cout << "Ingrese el nombre del platillo: ";
    cin.ignore();
    getline(cin, nombrePlatillo);

    nombrePlatillo = mayuscula(nombrePlatillo);

    while(validarPlatilloExistente(nombrePlatillo))
    {
        cout <<"Platillo ya ingresado, ingrese otro: ";
        getline(cin, nombrePlatillo);
        nombrePlatillo = mayuscula(nombrePlatillo);
    }


    cout<<"Ingrese el dia: ";
    cin>>dia;
    cout<<"Ingrese el mes: ";
    cin>>mes;
    cout<<"Ingrese el anio: ";
    cin>>anio;
    cout<<endl;
    system("cls");

    cout << "Ingrese el id del ingrendiente o 0 para no agregar mas: " << endl;
    cout<<endl;
    listarProductos();
    cin >> opc;

    while(opc != 0)
    {

        nuevoProductoxPlatillo(id, opc);//le pasa el id del platillo y el ingrediente a agregar.

        system("cls");
        cout << "Ingrese el id del ingrendiente o 0 para no agregar mas: " << endl;
        cout<<endl;
        listarProductos();
        cin >> opc;
    }
    cout<<endl;
    system("cls");
    cout<<endl;
    listarOrientacionAlimentaria();
    cout<<endl;
    cout << "Ingrese el id de la orientacion: ";
    cin >> orientacionAlimentaria;
    cout<<endl;
    cout << "Ingrese las calorias: ";
    cin >> calorias;

    Fecha fecha(dia, mes, anio);

    Platillo reg;
    reg.setIdPlatillo(id);
    reg.setNombrePlatillo(nombrePlatillo);
    reg.setFechaRegistrado(fecha);
    reg.setOrientacionalimentaria(orientacionAlimentaria);
    reg.setCalorias(calorias);
    reg.setEstadoPlatillo(estado);
    cout<<endl;
    cout<<endl;
    system("pause");
    return reg;
}

bool validarPlatilloExistente(string n)
{
    Platillo aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if(aux.getNombrePlatillo() == n && aux.getEstadoPlatillo() == true)
        {
            return true;
        }
        pos++;
    }
    return false;
}

void listarPlatillos()
{
    Platillo aux;
    int cantPlatillos = CantidadRegistrosPlatillo();
    int pos = 0, cont=0;
    cout << setw(45)<<"LISTADO DE PLATILLOS" << endl;
    cout << "--------------------------------------------------------------------------"<< endl;
    cout << left;
    cout << setw(5) << "ID";
    cout << setw(20) << "NOMBRE";
    cout << setw(15) << "FECHA";
    cout << setw(20) << "ORIENTACION A.";
    cout << setw(10) << "CALORIAS"<<endl;
    cout<< "--------------------------------------------------------------------------"<< endl;
    for(int i=0; i<cantPlatillos; i++)
    {
        aux.LeerDeDisco(i); //un while aca?
        if(aux.getEstadoPlatillo())
        {
            aux.toList();
        }
        else
        {
            cont++;
        }
    }
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "Total: " << cantPlatillos - cont<< " platillos.";
    cout<<endl;
    cout<<endl;
}

int EliminarPlatillo()
{
    Platillo aux;
    int pos=0, idplatillo;

    listarPlatillos();
    cout<<endl;

    cout<<"Ingrese el ID del platillo a eliminar: ";
    cin>>idplatillo;

    while(aux.LeerDeDisco(pos)==1)
    {
        if(aux.getIdPlatillo() == idplatillo)
        {
            aux.setEstadoPlatillo(false);
            aux.ModificarArchivo(pos);
            return pos;
        }
        pos++;
    }
    return -1;
}

void EliminarPlatilloPorParametro(int idplatillo)
{
    Platillo aux;
    int pos=0;

    while(aux.LeerDeDisco(pos)==1)
    {
        if(aux.getIdPlatillo() == idplatillo)
        {
            aux.setEstadoPlatillo(false);
            aux.ModificarArchivo(pos);
            return;
        }
        pos++;
    }
}

void buscarPlatilloNombre()
{
    Platillo reg;
    int pos = 0;
    bool bandera = false;
    string nombre;

    cout << "Ingrese el nombre del platillo a buscar: ";
    cin.ignore();
    getline(cin, nombre);
    nombre = mayuscula(nombre);
    cout << endl;

    while(reg.LeerDeDisco(pos))
    {
        if(reg.getNombrePlatillo() == nombre && reg.getEstadoPlatillo())
        {
            cout << reg.toString() << endl;
            bandera = true;
        }
        pos++;
    }

    if(bandera == false)
    {
        cout << "No hay platillos con ese nombre." << endl;
    }
}

void busquedaPlatilloOrientacion()
{
    Platillo reg;
    int pos = 0;
    bool bandera = false;
    int opc;

    listarOrientacionAlimentaria();

    cout << "Ingrese el id de la orientacion a buscar: ";
    cin >> opc;
    cout << endl;

    while(reg.LeerDeDisco(pos))
    {
        if(reg.getOrientacionAlimentaria() == opc && reg.getEstadoPlatillo())
        {
            cout << reg.toString() << endl;
            bandera = true;
        }
        pos++;
    }

    if(bandera == false)
    {
        cout << "No hay platillos con ese id." << endl;
    }
}

void menuBuscarPlatillo()
{
    int opc;
    while(true)
    {
        system("cls");

        cout<<"MENU PLATILLOS"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. BUSCAR POR NOMBRE"<<endl;
        cout<<"2. BUSCAR POR ORIENTACION"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: ";
        cin>>opc;

        system("cls");

        switch(opc)
        {
        case 1:
            buscarPlatilloNombre();
            system("pause");
            break;
        case 2:
            busquedaPlatilloOrientacion();
            system("pause");
            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}

void menuPlatillo()
{
    int opc;
    while(true)
    {
        system("cls");

        cout<<"MENU PLATILLO"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. AGREGAR PLATILLO "<<endl;
        cout<<"2. ELIMINAR PLATILLO "<<endl;
        cout<<"3. LISTAR PLATILLOS "<<endl;
        cout<<"4. LISTAR PRODUCTOS POR PLATILLO" << endl;
        cout<<"5. BUSCAR PLATILLO"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: ";
        cin>>opc;

        system("cls");

        switch(opc)
        {
        case 1:
            if(nuevoPlatillo())
            {
                cout<<endl;
                cout<<"PLATILLO AGREGADO";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO AGREGAR EL PLATILLO";
                cout<<endl;
                system("pause");
            }
            break;
        case 2:
            if(EliminarPlatillo()!= -1)
            {
                cout<<endl;
                cout<<"PLATILLO ELIMINADO";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO ELIMINAR EL PLATILLO";
                cout<<endl;
                system("pause");
            }
            break;
        case 3:
            listarPlatillos();
            system("pause");
            break;
        case 4:
            listarProductosxPlatillo();
            system("pause");
            break;
        case 5:
            menuBuscarPlatillo();
            system("pause");
            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}
