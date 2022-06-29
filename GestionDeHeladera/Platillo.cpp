#include <iostream>
#include <iomanip>
#include "rlutil.h"
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
    rlutil::setColor(rlutil::LIGHTCYAN);
    cout << left;
    cout << "\t";
    cout << setw(5) << to_string(idPlatillo);
    cout << setw(25) << nombrePlatillo;
    cout << setw(15) << fechaRegistrado.toString();
    cout << setw(20) << mostrarOrientacionAlimentaria(getOrientacionAlimentaria());
    cout << setw(10) << to_string(calorias)<<endl;
    rlutil::setColor(rlutil::BROWN);
}


bool Platillo::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("Platillos.dat", "rb");
    if(p==NULL)
    {
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
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
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
        rlutil::setColor(rlutil::RED);
        cout << endl;
        cout <<"Platillo ya ingresado, ingrese otro: ";
        getline(cin, nombrePlatillo);
        nombrePlatillo = mayuscula(nombrePlatillo);
        cout << endl;
        rlutil::setColor(rlutil::BROWN);
    }

    system("cls");

    cout << "Ingrese el id del ingrendiente o 0 para no agregar mas: " << endl;
    cout<<endl;

    listarProductos();
    cin >> opc;
    while(validarNumero())
    {
        cin >> opc;
    }

    while(opc != 0)
    {
        //ingresa el platillo, con sus productos en productosXPlatillo, tambien valida su existencia.
        nuevoProductoxPlatillo(id, opc);//le pasa el id del platillo y el ingrediente a agregar.
        system("cls");
        cout<<endl;
        cout << "Ingrese el id del ingrendiente o 0 para no agregar mas: " << endl;
        cout<<endl;
        listarProductos();
        cin >> opc;
        while(validarNumero())
        {
            cin >> opc;
        }
    }

    cout<<endl;
    system("cls");
    cout<<endl;
    listarOrientacionAlimentaria();
    cout<<endl;
    cout << "Ingrese el id de la orientacion: ";
    cin >> orientacionAlimentaria;
    cout<<endl;

    while(validarNumero())
    {
        cin >> orientacionAlimentaria;
    }

    while(validarOrientacionExistentePorId(orientacionAlimentaria)== false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout <<"Orientacion inexistente, ingrese otra: ";
        cin >> orientacionAlimentaria;
        cout<<endl;
        while(validarNumero())
        {
            cin >> orientacionAlimentaria;
        }
        rlutil::setColor(rlutil::BROWN);
    }

    cout << "Ingrese las calorias: ";
    cin >> calorias;

    Fecha fecha;

    Platillo reg;
    reg.setIdPlatillo(id);
    reg.setNombrePlatillo(nombrePlatillo);
    reg.setFechaRegistrado(fecha);
    reg.setOrientacionalimentaria(orientacionAlimentaria);
    reg.setCalorias(calorias);
    reg.setEstadoPlatillo(estado);
    cout<<endl;
    cout<<endl;
    //system("pause");
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

bool validarPlatilloExistenteXId(int idPlatillo)
{
    Platillo aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if(aux.getIdPlatillo() == idPlatillo && aux.getEstadoPlatillo() == true)
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
    int cont=0;
    cout << endl;
    cout << endl;
    cout << left;
    cout << setw(30) << "\t";
    rlutil::setColor(rlutil::MAGENTA);
    cout << "LISTADO DE PLATILLOS" << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-------------------------------------------------------------------------"<< endl;
    cout << left;
    cout << "\t";
    cout << setw(5) << "ID";
    cout << setw(25) << "NOMBRE";
    cout << setw(15) << "FECHA";
    cout << setw(20) << "ORIENTACION A.";
    cout << setw(10) << "CALORIAS"<<endl;
    cout << "\t" << "-------------------------------------------------------------------------"<< endl;

    for(int i=0; i<cantPlatillos; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoPlatillo())
        {
            aux.toList();
        }
        else
        {
            cont++;
        }
    }
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-------------------------------------------------------------------------" << endl;
    cout << "\t" << "Total: " << cantPlatillos - cont<< " platillos.";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
}

int EliminarPlatillo()
{
    Platillo aux;
    int pos=0, idplatillo;

    listarPlatillos();
    cout<<endl;

    cout<<"Ingrese el ID del platillo a eliminar: ";
    cin>>idplatillo;
    cout << endl;

    while(validarNumero())
    {
        cin >> idplatillo;
    }

    while(aux.LeerDeDisco(pos)==1)
    {
        if(aux.getIdPlatillo() == idplatillo && aux.getEstadoPlatillo() == true)
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

    while(validarPlatilloExistente(nombre)== false)
    {
        rlutil::setColor(rlutil::RED);
        cout << endl;
        cout <<"Platillo inexistente, ingrese otro: ";
        getline(cin, nombre);
        nombre = mayuscula(nombre);
        cout << endl;
        rlutil::setColor(rlutil::BROWN);
    }

    system("cls");
    cout << endl;
    cout << endl;
    cout << left;
    cout << setw(20) << "\t";
    rlutil::setColor(rlutil::MAGENTA);
    cout <<  "LISTADO DE PLATILLOS POR NOMBRE " << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-------------------------------------------------------------------------" << endl;
    cout << left;
    cout << "\t";
    cout << setw(5) << "ID";
    cout << setw(25) << "NOMBRE";
    cout << setw(15) << "FECHA";
    cout << setw(20) << "ORIENTACION A.";
    cout << setw(10) << "CALORIAS"<<endl;
    cout << "\t" << "-------------------------------------------------------------------------" << endl;

    while(reg.LeerDeDisco(pos))
    {
        if(reg.getNombrePlatillo() == nombre && reg.getEstadoPlatillo())
        {
            reg.toList();
            bandera = true;
        }
        pos++;
    }

    cout<<endl;
    cout<<endl;
    cout<<endl;

    if(bandera == false)
    {
        rlutil::setColor(rlutil::RED);
        system("cls");
        cout<<endl;
        cout << "No hay platillos con ese nombre." << endl;
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }
    rlutil::setColor(rlutil::BROWN);
}

void busquedaPlatilloOrientacion()
{
    Platillo reg;
    int pos = 0;
    bool bandera = false;
    int opc;

    cout << endl;
    cout << endl;
    listarOrientacionAlimentaria();
    cout << endl;
    cout << endl;

    cout << "Ingrese el id de la orientacion a buscar: ";
    cin >> opc;
    cout << endl;
    while(validarNumero())
    {
        cin >> opc;
    }



    while(validarOrientacionExistentePorId(opc)== false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout <<"Orientacion inexistente, ingrese otra: ";
        cin >> opc;
        cout<<endl;
        while(validarNumero())
        {
            cin >> opc;
        }
        rlutil::setColor(rlutil::BROWN);
    }

    system("cls");

    rlutil::setColor(rlutil::MAGENTA);
    cout<<endl;
    cout<<endl;
    cout << left;
    cout << setw(20) << "\t";
    cout <<  "LISTADO DE PLATILLOS POR ORIENTACION: " << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-------------------------------------------------------------------------" << endl;
    cout << left;
    cout << "\t";
    cout << setw(5) << "ID";
    cout << setw(25) << "NOMBRE";
    cout << setw(15) << "FECHA";
    cout << setw(20) << "ORIENTACION A.";
    cout << setw(10) << "CALORIAS"<<endl;
    cout << "\t" << "-------------------------------------------------------------------------" << endl;

    while(reg.LeerDeDisco(pos))
    {
        if(reg.getOrientacionAlimentaria() == opc && reg.getEstadoPlatillo())
        {
            reg.toList();
            bandera = true;
        }
        pos++;
    }

    cout<<endl;
    cout<<endl;
    cout<<endl;

    if(bandera == false)
    {
        rlutil::setColor(rlutil::RED);
        system("cls");
        cout<<endl;
        cout << "No hay platillos con esa orientacion." << endl;
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    rlutil::setColor(rlutil::BROWN);
}

void menuBuscarPlatillo()
{
    int opc;
    while(true)
    {
        system("cls");
        rlutil::locate(52, 5);
        rlutil::setColor(rlutil::GREY);
        cout<<"MENU BUSCAR PLATILLOS"<<endl;
        rlutil::locate(40, 6);
        cout<<"---------------------------------------------"<<endl;
        rlutil::locate(48, 8);
        rlutil::setColor(rlutil::MAGENTA);
        cout<<"1. BUSCAR POR NOMBRE"<<endl;
        rlutil::locate(48, 9);
        cout<<"2. BUSCAR POR ORIENTACION"<<endl;
        rlutil::locate(48, 10);
        cout<<"-------------------"<<endl;
        rlutil::locate(48, 11);
        cout<<"0. SALIR"<<endl;
        rlutil::locate(48, 12);
        cout<<endl;

        rlutil::locate(48, 15);
        rlutil::setColor(rlutil::GREY);
        cout<<"OPCION: ";
        cin>>opc;
        rlutil::setColor(rlutil::BROWN);

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
        rlutil::locate(56, 5);
        rlutil::setColor(rlutil::CYAN);
        cout<<"MENU PLATILLO"<<endl;
        rlutil::locate(40, 6);
        cout<<"-----------------------------------------------"<<endl;
        rlutil::locate(48, 8);
        rlutil::setColor(rlutil::LIGHTCYAN);
        cout<<"1. AGREGAR PLATILLO "<<endl;
        rlutil::locate(48, 9);
        cout<<"2. ELIMINAR PLATILLO "<<endl;
        rlutil::locate(48, 10);
        cout<<"3. LISTAR PLATILLOS "<<endl;
        rlutil::locate(48, 11);
        cout<<"4. LISTAR PRODUCTOS POR PLATILLO" << endl;
        rlutil::locate(48, 12);
        cout<<"5. BUSCAR PLATILLO"<<endl;
        rlutil::locate(48, 13);
        cout<<"--------------------------------"<<endl;
        rlutil::locate(48, 14);
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        rlutil::locate(48, 17);
        rlutil::setColor(rlutil::DARKGREY);
        cout<<"OPCION: ";
        cin>>opc;

        rlutil::setColor(rlutil::BROWN);
        system("cls");

        switch(opc)
        {
        case 1:
            if(nuevoPlatillo())
            {
                rlutil::setColor(rlutil::GREEN);
                cout<<endl;
                cout<<"PLATILLO AGREGADO";
                cout<<endl;
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
                system("pause");
            }
            else
            {
                rlutil::setColor(rlutil::RED);
                cout<<endl;
                cout<<"NO SE PUDO AGREGAR EL PLATILLO";
                cout<<endl;
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
                system("pause");
            }
            break;
        case 2:
            if(EliminarPlatillo()!= -1)
            {
                rlutil::setColor(rlutil::GREEN);
                cout<<endl;
                cout<<"PLATILLO ELIMINADO";
                cout<<endl;
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
                system("pause");
            }
            else
            {
                rlutil::setColor(rlutil::RED);
                cout<<endl;
                cout<<"NO SE PUDO ELIMINAR EL PLATILLO";
                cout<<endl;
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
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
            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}
