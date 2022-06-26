#include <iostream>
#include <iomanip>
#include "rlutil.h"
#include "OrientacionAlimentaria.h"
#include "FuncionesGlobales.h"


using namespace std;

string OrientacionAlimentaria::getDescripcion()
{
    string descripciones;
    descripciones = descripcion;
    return descripciones;
}

string OrientacionAlimentaria::toString()
{
    string cadena;
    cadena = "Id Orientacion Alimentaria: " + to_string(idOrientacionAlimentaria) + " " " " + " Descripcion: " + descripcion;
    return cadena;
}

bool OrientacionAlimentaria::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("OrientacionesAlimentarias.dat", "rb");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        return false;
    }
    fseek(p, pos*sizeof(OrientacionAlimentaria),0);
    leyo=fread(this,sizeof(OrientacionAlimentaria),1,p);

    fclose(p);

    return leyo;
}

bool OrientacionAlimentaria::GrabarEnDisco()
{
    FILE *p;
    p=fopen("OrientacionesAlimentarias.dat", "ab");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        return false;
    }
    int escribio=fwrite(this, sizeof(OrientacionAlimentaria),1,p);
    fclose(p);

    return escribio;
}

//METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
//HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
bool OrientacionAlimentaria::ModificarArchivo(int pos)
{
    FILE *p;
    p=fopen("OrientacionesAlimentarias.dat", "rb+");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        return false;
    }
    fseek(p, pos*sizeof(OrientacionAlimentaria),0);
    int escribio=fwrite(this, sizeof(OrientacionAlimentaria),1,p);
    fclose(p);

    return escribio;
}


/// Funciones globales para gestionar la Orientacion Alimentaria
bool nuevaOrientacionAlimentaria()
{
    OrientacionAlimentaria reg;
    reg = cargarOrientacionAlimentaria();
    bool ok = reg.GrabarEnDisco();
    return ok;
}

int CantidadRegistrosOA()
{
    FILE *p;
    p=fopen("OrientacionesAlimentarias.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    size_t bytes;
    int cantidad;

    fseek(p, 0, SEEK_END);
    bytes=ftell(p);

    fclose(p);
    cantidad = bytes/sizeof(OrientacionAlimentaria);
    return cantidad;
}

OrientacionAlimentaria cargarOrientacionAlimentaria()
{
    int id;
    string descripcion;
    bool estado = true;

    id = CantidadRegistrosOA()+1;

    cout << "Ingrese la descripcion: ";
    cin.ignore();
    getline(cin, descripcion);

    descripcion = mayuscula(descripcion);

    while(validarOrientacionExistente(descripcion))
    {
        cout <<"Orientacion ya ingresada, ingrese otro: ";
        getline(cin, descripcion);
        descripcion = mayuscula(descripcion);
    }

    OrientacionAlimentaria reg;
    reg.setIdOrientacionAlimentaria(id);
    reg.setDescripcion(descripcion);
    reg.setEstadoOrientacion(estado);
    cout<<endl;
    cout<<endl;
    system("pause");
    return reg;
}

bool validarOrientacionExistente(string n)
{
    OrientacionAlimentaria aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        ///ver de pasar todo el nombre a mayuscula para que no haya repetidos
        // nombre = n.toupper();//transforma todo a mayuscula por si se tipea diferente pero existe
        if(aux.getDescripcion() == n && aux.getEstadoOrientacion() == true)
        {
            return true;
        }
        pos++;
    }
    return false;
}


void listarOrientacionAlimentaria()
{
    OrientacionAlimentaria aux;
    int cont=0;
    int cantOA = CantidadRegistrosOA();

    rlutil::setColor(rlutil::MAGENTA);
    cout << left;
    cout << "\t" << "\t";
    cout << "ORIENTACIONES ALIMENTARIAS" << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t"<<"-------------------------------------------" << endl;

    cout << left;
    cout << setw(5) << "\t" <<"\t" << "ID";
    cout << setw(5)  << "\t" <<"\t" << "NOMBRE" << endl;
    cout << "\t"<<"-------------------------------------------" << endl;

    for(int i=0; i<cantOA; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoOrientacion())
        {
            rlutil::setColor(rlutil::LIGHTCYAN);
            cout << left;
            cout << setw(5)  << "\t" << "\t" << aux.getIdOrientacionAlimentaria();
            cout << setw(5) << "\t" << "\t" << aux.getDescripcion() << endl;
        }
        else
        {
            cont++;
        }
    }
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t"<<"-------------------------------------------" << endl;
    cout << "\t"<<"Total: " << cantOA - cont<< " orientaciones alimentarias.";
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
}

int EliminarOrientacionAlimentaria()
{
    OrientacionAlimentaria aux;
    int pos=0, idOrientacion;

    listarOrientacionAlimentaria();
    cout<<endl;

    cout<<"Ingrese el ID de la orientacion a eliminar: ";
    cin>>idOrientacion;

    while(aux.LeerDeDisco(pos)==1)
    {
        if(aux.getIdOrientacionAlimentaria() == idOrientacion)
        {
            aux.setEstadoOrientacion(false);
            aux.ModificarArchivo(pos);
            return pos;
        }
        pos++;
    }
    return -1;
}

void menuOrientacionAlimentaria()
{
    int opc;
    while(true)
    {
        system("cls");
        rlutil::locate(51, 5);
        rlutil::setColor(rlutil::CYAN);
        cout<<"MENU ORIENTACION ALIMENTARIA"<<endl;
        rlutil::locate(40, 6);
        cout<<"------------------------------------------------"<<endl;
        rlutil::setColor(rlutil::LIGHTCYAN);
        rlutil::locate(53, 8);
        cout<<"1. AGREGAR ORIENTACION "<<endl;
        rlutil::locate(53, 9);
        cout<<"2. ELIMINAR ORIENTACION" <<endl;
        rlutil::locate(53, 10);
        cout<<"3. LISTAR ORIENTACIONES "<<endl;
        rlutil::locate(53, 11);
        cout<<"-----------------------"<<endl;
        rlutil::locate(53, 12);
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        rlutil::locate(53, 15);
        rlutil::setColor(rlutil::DARKGREY);
        cout<<"OPCION: ";
        cin>>opc;

        rlutil::setColor(rlutil::BROWN);
        system("cls");

        switch(opc)
        {
        case 1:
            if(nuevaOrientacionAlimentaria())
            {
                cout<<endl;
                cout<<"ORIENTACION AGREGADA";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO AGREGAR LA ORIENTACION";
                cout<<endl;
                system("pause");
            }
            break;
        case 2:
            if(EliminarOrientacionAlimentaria()!= -1)
            {
                cout<<endl;
                cout<<"ORIENTACION ELIMINADA";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO ELIMINAR LA ORIENTACION";
                cout<<endl;
                system("pause");
            }
            break;
        case 3:
            listarOrientacionAlimentaria();
            system("pause");
            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}
