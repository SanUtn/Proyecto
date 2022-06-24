#include <iostream>
#include <iomanip>
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
    cout << left;
    cout << setw(10) << to_string(DNI);
    cout << setw(17) << getNombre();
    cout << setw(17)  << getApellido() << endl;
}


bool Usuario::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("Usuarios.dat", "rb");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
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
        cout<<"El archivo no pudo abrirse"<<endl;
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
        cout<<"El archivo no pudo abrirse"<<endl;
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
    if(reg.getId() == -1)
    {
        cout << endl;
        cout << "CARGA DE USUARIO CANCELADA" <<endl;
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
        cout << "Usuario ya existente."<<endl;
        cout << "Ingrese el DNI o 0 para salir: ";
        cin >> dni;
        if(dni == 0)
        {
            reg.setId(-1);
            return reg;
        }
    }

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
    cout << setw(20) << "\t";
    cout << "USUARIOS" << endl;
    cout << "---------------------------------------------------------------" << endl;

    cout << setw(4)  << "ID";
    cout << setw(10) << "DNI";
    cout << setw(17) << "NOMBRE";
    cout << setw(17)  << "APELLIDO";
    cout << setw(20) << "O. ALIMENTARIA" << endl;

    cout << "---------------------------------------------------------------" << endl;
    for(int i=0; i<cantUsuarios; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoUsuario())
        {
            cout << left;
            cout << setw(4)  << aux.getId();
            cout << setw(10) << aux.getDNI();
            cout << setw(17) << aux.getNombre();
            cout << setw(17)  << aux.getApellido();
            cout << setw(20) << mostrarOrientacionAlimentaria(aux.getIdOrientacionAlimentaria()) << endl;
        }
        else
        {
            cont++;
        }
    }
    cout << "---------------------------------------------------------------" << endl;
    cout << "Total: " << cantUsuarios - cont<< " Usuarios.";
    cout<<endl;
    cout<<endl;
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

    cout << "Ingrese el nombre del usuario a buscar: ";
    cin.ignore();
    getline(cin, nombre);
    nombre = mayuscula(nombre);
    cout << endl;
    cout << left;
    cout << setw(10) << "DNI";
    cout << setw(17) << "NOMBRE";
    cout << setw(17)  << "APELLIDO" << endl;
    cout << endl;
    while(reg.LeerDeDisco(pos))
    {
        if(reg.getNombre() == nombre && reg.getEstadoUsuario())
        {
            reg.toList();
            bandera = true;
        }
        pos++;
    }

    if(bandera == false)
    {
        system("cls");
        cout << "No hay usuarios con ese nombre." << endl;
    }
    cout << endl;
}

void buscarUsuarioDNI()
{
    Usuario reg;
    int pos = 0;
    bool bandera = false;
    int dni;

    cout << "Ingrese el dni: ";
    cin >> dni;

    cout << endl;
    cout << left;
    cout << setw(10) << "DNI";
    cout << setw(17) << "NOMBRE";
    cout << setw(17)  << "APELLIDO" << endl;
    cout << endl;
    while(reg.LeerDeDisco(pos))
    {
        if(reg.getDNI() == dni && reg.getEstadoUsuario())
        {
            reg.toList();
            bandera = true;
        }
        pos++;
    }
    if(bandera == false)
    {
        system("cls");
        cout << "No hay usuarios con ese dni." << endl;
    }
    cout << endl;
}

void buscarUsuarioOrientacion()
{
    Usuario reg;
    int pos = 0;
    bool bandera = false;
    int orientacion;

    listarOrientacionAlimentaria();

    cout << "Ingrese el id de la orientacion: ";
    cin >> orientacion;

    system("cls");

    cout << endl;
    cout << left;
    cout << setw(10) << "DNI";
    cout << setw(17) << "NOMBRE";
    cout << setw(17)  << "APELLIDO" << endl;
    cout << endl;
    while(reg.LeerDeDisco(pos))
    {
        if(reg.getIdOrientacionAlimentaria() == orientacion && reg.getEstadoUsuario())
        {
            reg.toList();
            bandera = true;
        }
        pos++;
    }
    if(bandera == false)
    {
        system("cls");
        cout << "No hay usuarios con esa orientacion." << endl;
    }
    cout << endl;
}

void menuBuscarUsuario()
{
    int opc;
    while(true)
    {
        system("cls");

        cout<<"MENU USUARIO"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. BUSCAR POR NOMBRE"<<endl;
        cout<<"2. BUSCAR POR DNI"<<endl;
        cout<<"3. BUSCAR POR ORIENTACION"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: ";
        cin>>opc;

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

        cout<<"MENU USUARIO"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. AGREGAR USUARIO "<<endl;
        cout<<"2. ELIMINAR USUARIO"<<endl;
        cout<<"3. LISTAR USUARIOS "<<endl;
        cout<<"4. BUSCAR USUARIO"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: ";
        cin>>opc;

        system("cls");

        switch(opc)
        {
        case 1:
            if(nuevoUsuario())
            {
                cout<<endl;
                cout<<"USUARIO AGREGADO";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO AGREGAR EL USUARIO";
                cout<<endl;
                system("pause");
            }
            break;
        case 2:
            aux = EliminarUsuario();
            if(aux!= -1 && aux!= -2)
            {
                cout<<endl;
                cout<<"USUARIO ELIMINADO";
                cout<<endl;
                system("pause");
            }
            else if(aux == -2){
                cout<<endl;
                cout<<"ELIMINACION CANCELADA";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO ELIMINAR EL USUARIO";
                cout<<endl;
                system("pause");
            }
            break;
        case 3:
            listarUsuarios();
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


