#include <iostream>
#include <iomanip>
#include "rlutil.h"
#include "Usuario.h"
#include "FuncionesGlobales.h"

using namespace std;


string Usuario::getNombre()
{
    string nombres;
    nombres = nombre;
    return nombres;
}

string Usuario::getApellido()
{
    string apellidos;
    apellidos=apellido;
    return apellidos;
}


void Usuario::setNombre(string nombres)
{
    strcpy(nombre, nombres.c_str());
}

void Usuario::setApellido(string apellidos)
{
    strcpy(apellido, apellidos.c_str());
}

string Usuario::toString()
{
    string cadena;
    cadena = " Id: " + to_string(id) + " " " " + " Dni: " + to_string(DNI) + " " " " + "Nombre: " + nombre + " " " " + " Apellido: " + apellido + " " " " + " Orientacion Alimentaria: " +          mostrarOrientacionAlimentaria(getIdOrientacionAlimentaria());

    return cadena;
}

void Usuario::toList()
{
    rlutil::setColor(rlutil::LIGHTCYAN);
    cout << left;
    cout << setw(15) << to_string(DNI);
    cout << setw(15) << getNombre();
    cout << setw(15) << getApellido() << endl;
    rlutil::setColor(rlutil::BROWN);
}


bool Usuario::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("Usuarios.dat", "rb");
    if(p==NULL)
    {
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    fseek(p, pos*sizeof(Usuario),0);
    leyo=fread(this,sizeof(Usuario),1,p);

    fclose(p);

    return leyo;
}

bool Usuario::GrabarEnDisco()
{
    FILE *p;
    p=fopen("Usuarios.dat", "ab");
    if(p==NULL)
    {
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    int escribio=fwrite(this, sizeof(Usuario),1,p);
    fclose(p);

    return escribio;
}



//METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
//HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
bool Usuario::ModificarArchivo(int pos)
{
    FILE *p;
    p=fopen("Usuarios.dat", "rb+");
    if(p==NULL)
    {
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    fseek(p, pos*sizeof(Usuario),0);
    int escribio=fwrite(this, sizeof(Usuario),1,p);
    fclose(p);

    return escribio;
}


/// Funciones globales para gestionar Usuario
bool nuevoUsuario()
{
    Usuario reg;
    reg = cargarUsuario();
    //si ingresa 0 para salir se setea el id en -1.
    if(reg.getId() == -1)
    {
        rlutil::setColor(rlutil::RED);
        cout << endl;
        cout << "CARGA DE USUARIO CANCELADA" <<endl;
        cout << endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    bool ok = reg.GrabarEnDisco();
    return ok;
}

int CantidadRegistrosUsuario()
{
    FILE *p;
    p=fopen("Usuarios.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    size_t bytes;
    int cantidad;

    fseek(p, 0, SEEK_END);
    bytes=ftell(p);

    fclose(p);
    cantidad = bytes/sizeof(Usuario);
    return cantidad;
}

Usuario cargarUsuario()
{
    int id;
    int dni;
    string nombre;
    string apellido;
    int idOrientacionAlimentaria;
    bool estado = true;
    Usuario reg;

    id = CantidadRegistrosUsuario()+1;

    cout << "Ingrese el DNI o 0 para salir: ";
    cin >> dni;

    if(dni == 0)
    {
        reg.setId(-1);
        return reg;
    }

    while(validarUsuarioExistente(dni))
    {
        rlutil::setColor(rlutil::RED);
        cout << endl;
        cout << "Usuario ya existente."<<endl;
        cout << endl;
        rlutil::setColor(rlutil::BROWN);
        cout << "Ingrese el DNI o 0 para salir: ";
        cin >> dni;
        if(dni == 0)
        {
            reg.setId(-1);
            return reg;
        }
    }

    rlutil::setColor(rlutil::BROWN);
    cout << "Ingrese el nombre: ";
    cin.ignore();
    getline(cin, nombre);
    nombre = mayuscula(nombre);
    cout << "Ingrese el apellido: ";
    getline(cin, apellido);
    apellido = mayuscula(apellido);
    cout<<endl;
    listarOrientacionAlimentaria();
    cout<<endl;
    cout << "Ingrese el id de la orientacion alimentaria: ";
    cin >> idOrientacionAlimentaria;


    reg.setId(id);
    reg.setDNI(dni);
    reg.setNombre(nombre);
    reg.setApellido(apellido);
    reg.setIdOrientacionAlimentaria(idOrientacionAlimentaria);
    reg.setEstadoUsuario(estado);

    return reg;
}

bool validarUsuarioExistente(int dni)
{
    Usuario aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if(aux.getDNI() == dni && aux.getEstadoUsuario() == true)
        {
            return true;
        }
        pos++;
    }
    return false;
}

void listarUsuarios()
{
    Usuario aux;
    int cont=0;
    int cantUsuarios=CantidadRegistrosUsuario();
    cout << left;
    cout<<endl;
    cout<<endl;
    cout << "\t" << "\t" <<"\t";
    rlutil::setColor(rlutil::MAGENTA);
    cout << "USUARIOS" << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout <<"---------------------------------------------------------------" << endl;

    cout << setw(5)  <<  "ID";
    cout << setw(10) <<  "DNI";
    cout << setw(15) <<  "NOMBRE";
    cout << setw(15) <<  "APELLIDO";
    cout << setw(10) <<  "O. ALIMENTARIA" << endl;

    cout <<"---------------------------------------------------------------" << endl;
    for(int i=0; i<cantUsuarios; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoUsuario())
        {
            rlutil::setColor(rlutil::LIGHTCYAN);
            cout << left;
            cout << setw(5) << aux.getId();
            cout << setw(10) << aux.getDNI();
            cout << setw(15)<< aux.getNombre();
            cout << setw(15)<< aux.getApellido();
            cout << setw(10)<< mostrarOrientacionAlimentaria(aux.getIdOrientacionAlimentaria()) << endl;
        }
        else
        {
            cont++;
        }
    }
    rlutil::setColor(rlutil::DARKGREY);
    cout <<"---------------------------------------------------------------" << endl;
    cout <<"Total: " << cantUsuarios - cont<< " Usuarios.";
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
}


int EliminarUsuario()
{
    Usuario aux;
    int pos=0, dni;

    listarUsuarios();
    cout<<endl;

    cout<<"Ingrese el dni del usuario a eliminar o 0 para cancelar: ";
    cin>>dni;
    if(dni == 0){
        return -2;
    }

    while(aux.LeerDeDisco(pos)==1)
    {
        if(aux.getDNI()==dni && aux.getEstadoUsuario() == true)
        {
            aux.setEstadoUsuario(false);
            aux.ModificarArchivo(pos);
            return pos;
        }
        pos++;
    }
    return -1;
}

void buscarUsuarioNombre()
{
    Usuario reg;
    int pos = 0;
    bool bandera = false;
    string nombre;

    rlutil::setColor(rlutil::BROWN);
    cout << "Ingrese el nombre del usuario a buscar: ";
    cin.ignore();
    getline(cin, nombre);
    nombre = mayuscula(nombre);
    cout << endl;
    rlutil::setColor(rlutil::MAGENTA);
    cout << left;
    cout << setw(15)<<"DNI";
    cout << setw(15)<<"NOMBRE";
    cout << setw(15)<<"APELLIDO" << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout <<"----------------------------------------------" << endl;

    while(reg.LeerDeDisco(pos))
    {
        if(reg.getNombre() == nombre && reg.getEstadoUsuario())
        {
            reg.toList();
            bandera = true;
        }
        pos++;
    }
    rlutil::setColor(rlutil::DARKGREY);
    cout <<"----------------------------------------------" << endl;

    if(bandera == false)
    {
        system("cls");
        rlutil::setColor(rlutil::RED);
        cout << endl;
        cout << "No hay usuarios con ese nombre." << endl;
        cout << endl;
        rlutil::setColor(rlutil::BROWN);
    }
    cout << endl;
    rlutil::setColor(rlutil::BROWN);
}

void buscarUsuarioDNI()
{
    Usuario reg;
    int pos = 0;
    bool bandera = false;
    int dni;

    rlutil::setColor(rlutil::BROWN);
    cout << "Ingrese el dni: ";
    cin >> dni;

    rlutil::setColor(rlutil::MAGENTA);
    cout << endl;
    cout << left;
    cout << setw(15) << "DNI";
    cout << setw(15) << "NOMBRE";
    cout << setw(15) << "APELLIDO" << endl;
     rlutil::setColor(rlutil::DARKGREY);
    cout <<"----------------------------------------------" << endl;

    while(reg.LeerDeDisco(pos))
    {
        if(reg.getDNI() == dni && reg.getEstadoUsuario())
        {
            reg.toList();
            bandera = true;
        }
        pos++;
    }
     rlutil::setColor(rlutil::DARKGREY);
    cout <<"----------------------------------------------" << endl;
    if(bandera == false)
    {
        system("cls");
        rlutil::setColor(rlutil::RED);
        cout << endl;
        cout << "No hay usuarios con ese dni." << endl;
        cout << endl;
        rlutil::setColor(rlutil::BROWN);
    }
    cout << endl;
    rlutil::setColor(rlutil::BROWN);
}

void buscarUsuarioOrientacion()
{
    Usuario reg;
    int pos = 0;
    bool bandera = false;
    int orientacion;

    cout<<endl;
    cout<<endl;
    listarOrientacionAlimentaria();

    rlutil::setColor(rlutil::BROWN);
    cout<<endl;
    cout<<endl;
    cout << "Ingrese el id de la orientacion: ";
    cin >> orientacion;

    system("cls");

    rlutil::setColor(rlutil::MAGENTA);
    cout << endl;
    cout << left;
    cout << setw(15) << "DNI";
    cout << setw(15) << "NOMBRE";
    cout << setw(15)  << "APELLIDO" << endl;
     rlutil::setColor(rlutil::DARKGREY);
    cout <<"----------------------------------------------" << endl;
    while(reg.LeerDeDisco(pos))
    {
        if(reg.getIdOrientacionAlimentaria() == orientacion && reg.getEstadoUsuario())
        {
            reg.toList();
            bandera = true;
        }
        pos++;
    }
     rlutil::setColor(rlutil::DARKGREY);
    cout <<"----------------------------------------------" << endl;
    if(bandera == false)
    {
        system("cls");
        rlutil::setColor(rlutil::RED);
        cout << endl;
        cout << "No hay usuarios con esa orientacion." << endl;
        cout << endl;
        rlutil::setColor(rlutil::BROWN);
    }
    cout << endl;
    rlutil::setColor(rlutil::BROWN);
}

void menuBuscarUsuario()
{
    //rlutil::setBackgroundColor(rlutil::GREY);
    int opc;
    while(true)
    {
        system("cls");
        rlutil::locate(52, 5);
        rlutil::setColor(rlutil::GREY);
        cout<<"MENU BUSCAR USUARIO"<<endl;
        rlutil::locate(40, 6);
        cout<<"---------------------------------------"<<endl;
        rlutil::locate(48, 8);
        rlutil::setColor(rlutil::MAGENTA);
        cout<<"1. BUSCAR POR NOMBRE"<<endl;
        rlutil::locate(48, 9);
        cout<<"2. BUSCAR POR DNI"<<endl;
        rlutil::locate(48, 10);
        cout<<"3. BUSCAR POR ORIENTACION"<<endl;
        rlutil::locate(48, 11);
        cout<<"-------------------------"<<endl;
        rlutil::locate(48, 12);
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        rlutil::locate(48, 15);
        rlutil::setColor(rlutil::GREY);
        cout<<"OPCION: ";
        cin>>opc;

        rlutil::setColor(rlutil::BROWN);
        //rlutil::setBackgroundColor(rlutil::BLACK);
        system("cls");

        switch(opc)
        {
        case 1:
            buscarUsuarioNombre();
            system("pause");
            break;
        case 2:
            buscarUsuarioDNI();
            system("pause");
            break;
        case 3:
            buscarUsuarioOrientacion();
            system("pause");
            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}


void menuUsuario()
{
    int opc;
    int aux;
    while(true)
    {
        system("cls");
        rlutil::locate(52, 5);
        rlutil::setColor(rlutil::CYAN);
        cout<<"MENU USUARIO"<<endl;
        rlutil::locate(40, 6);
        cout<<"-------------------------------------"<<endl;
        rlutil::locate(48, 8);
        rlutil::setColor(rlutil::LIGHTCYAN);
        cout<<"1. AGREGAR USUARIO "<<endl;
        rlutil::locate(48, 9);
        cout<<"2. ELIMINAR USUARIO"<<endl;
        rlutil::locate(48, 10);
        cout<<"3. LISTAR USUARIOS "<<endl;
        rlutil::locate(48, 11);
        cout<<"4. BUSCAR USUARIO"<<endl;
        rlutil::locate(48, 12);
        cout<<"-------------------"<<endl;
        rlutil::locate(48, 13);
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        rlutil::locate(48, 16);
        rlutil::setColor(rlutil::DARKGREY);
        cout<<"OPCION: ";
        cin>>opc;

        rlutil::setColor(rlutil::BROWN);
        system("cls");

        switch(opc)
        {
        case 1:
            if(nuevoUsuario())
            {
                rlutil::setColor(rlutil::GREEN);
                cout<<endl;
                cout<<"USUARIO AGREGADO";
                cout<<endl;

                rlutil::setColor(rlutil::BROWN);
                cout<<endl;
                system("pause");
            }
            else
            {
                rlutil::setColor(rlutil::RED);
                cout<<endl;
                cout<<"NO SE PUDO AGREGAR EL USUARIO";
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
                cout<<endl;
                system("pause");
            }
            break;
        case 2:
            aux = EliminarUsuario();
            if(aux!= -1 && aux!= -2)
            {
                rlutil::setColor(rlutil::GREEN);
                cout<<endl;
                cout<<"USUARIO ELIMINADO";
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
                cout<<endl;
                system("pause");
            }
            else if(aux == -2){
                rlutil::setColor(rlutil::RED);
                cout<<endl;
                cout<<"ELIMINACION CANCELADA";
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
                cout<<endl;
                system("pause");
            }
            else
            {
                rlutil::setColor(rlutil::RED);
                cout<<endl;
                cout<<"NO SE PUDO ELIMINAR EL USUARIO";
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
                cout<<endl;
                system("pause");
            }
            break;
        case 3:
            listarUsuarios();
            rlutil::setColor(rlutil::BROWN);
            system("pause");
            break;
        case 4:
            menuBuscarUsuario();
            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}


