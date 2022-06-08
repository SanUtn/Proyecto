#include <iostream>
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

    id = CantidadRegistrosUsuario()+1;

    cout << "Ingrese el DNI: ";
    cin >> dni;
    while(validarUsuarioExistente(dni))
    {
        cout << "Usuario ya existente."<<endl;
        cout << "Ingrese el DNI: ";
        cin >> dni;
    }

    cout << "Ingrese el nombre: ";
    cin >> nombre;
    cout << "Ingrese el apellido: ";
    cin >> apellido;
    cout<<endl;
    listarOrientacionAlimentaria();
    cout<<endl;
    cout << "Ingrese la orientacion alimentaria: ";
    cin >> idOrientacionAlimentaria;

    Usuario reg;
    reg.setId(id);
    reg.setDNI(dni);
    reg.setNombre(nombre);
    reg.setApellido(apellido);
    reg.setIdOrientacionAlimentaria(idOrientacionAlimentaria);
    reg.setEstadoUsuario(estado);
    cout<<endl;
    cout<<endl;
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
    cout << "LISTADO DE USUARIOS" << endl;
    cout << "----------------------------------" << endl;
    for(int i=0; i<cantUsuarios; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoUsuario())
        {
            cout<<aux.toString()<<endl;
        }else{
            cont++;
        }
    }
    cout << "----------------------------------" << endl;
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

    cout<<"Ingrese el dni del usuario a eliminar: ";
    cin>>dni;

    while(aux.LeerDeDisco(pos)==1)
    {
        if(aux.getDNI()==dni)
        {
            aux.setEstadoUsuario(false);
            aux.ModificarArchivo(pos);
            return pos;
        }
        pos++;
    }
    return -1;
}



void menuUsuario()
{
    int opc;
    while(true)
    {
        system("cls");

        cout<<"MENU USUARIO"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. AGREGAR USUARIO "<<endl;
        cout<<"2. ELIMINAR USUARIO"<<endl;
        cout<<"3. LISTAR USUARIOS "<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: "<<endl;
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
            if(EliminarUsuario()!= -1)
            {
                cout<<endl;
                cout<<"USUARIO ELIMINADO";
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
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}


