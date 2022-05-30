#include <iostream>
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
    cadena = "Id Platillo: " +
    to_string(idPlatillo) +
    " " " " +
    " Nombre Platillo: " +
    nombrePlatillo + " " " " +
    fechaRegistrado.toString() +
    " " " " +
    " Orientacion alimentaria: "
    + mostrarOrientacionAlimentaria(getOrientacionAlimentaria());

    return cadena;
}


bool Platillo::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("Platillos.dat", "rb");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        exit(1);
    }
    fseek(p, pos*sizeof(Platillo),0);
    leyo=fread(this,sizeof(Platillo),1,p);

    fclose(p);

    if(leyo)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Platillo::GrabarEnDisco()
{
    FILE *p;
    p=fopen("Platillos.dat", "ab");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        exit(1);
    }
    int escribio=fwrite(this, sizeof(Platillo),1,p);
    fclose(p);

    if(escribio)
    {
        return true;
    }
    else
    {
        return false;
    }
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
        exit(1);
    }
    fseek(p, pos*sizeof(Platillo),0);
    int escribio=fwrite(this, sizeof(Platillo),1,p);
    fclose(p);

    if(escribio)
    {
        return true;
    }
    else
    {
        return false;
    }
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
    bool estado = true;

    id = CantidadRegistrosPlatillo()+1;

    cout << "Ingrese el nombre del platillo: ";
    cin.ignore();
    getline(cin, nombrePlatillo);


    cout<<"Ingrese el dia: ";
    cin>>dia;
    cout<<"Ingrese el mes: ";
    cin>>mes;
    cout<<"Ingrese el anio: ";
    cin>>anio;
    cout<<endl;

    cout << "Ingrese el id del ingrendiente o 0 para no agregar mas: " << endl;
    listarProductos();
    cin >> opc;

    while(opc != 0){

        nuevoProductoxPlatillo(id, opc);

        cout << "Ingrese el nombre del ingrendiente o 0 para no agregar mas: " << endl;
        listarProductos();
        cin >> opc;
    }
    cout<<endl;

    cout<<endl;
    listarOrientacionAlimentaria();
    cout<<endl;
    cout << "Ingrese el id de la orientacion: ";
    cin >> orientacionAlimentaria;

    Fecha fecha(dia, mes, anio);

    Platillo reg;
    reg.setIdPlatillo(id);
    reg.setNombrePlatillo(nombrePlatillo);
    reg.setFechaRegistrado(fecha);
    reg.setOrientacionalimentaria(orientacionAlimentaria);
    reg.setEstadoPlatillo(estado);
    cout<<endl;
    cout<<endl;
    system("pause");
    return reg;
}


void listarPlatillos()
{
    Platillo aux;
    int cantPlatillos = CantidadRegistrosPlatillo();
    int pos = 0, cont=0;
    cout << "LISTADO DE PLATILLOS" << endl;
    cout << "----------------------------------" << endl;
    for(int i=0; i<cantPlatillos; i++)
    {
        aux.LeerDeDisco(i); //un while aca?
        if(aux.getEstadoPlatillo())
        {
            cout<<aux.toString()<<endl;
        }else {
        cont++;
        }
    }
    cout << "----------------------------------" << endl;
    cout << "Total: " << cantPlatillos - cont<< " platillos.";
    cout<<endl;
    cout<<endl;
    system("pause");
}

int EliminarPlatillo(){
        Platillo aux;
        int pos=0, idplatillo;

        listarPlatillos();
        cout<<endl;

        cout<<"Ingrese el ID del platillo a eliminar: ";
        cin>>idplatillo;

        while(aux.LeerDeDisco(pos)==1){
           if(aux.getIdPlatillo() == idplatillo){
                aux.setEstadoPlatillo(false);
                aux.ModificarArchivo(pos);
                return pos;
           }
           pos++;
        }
        return -1;
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
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: "<<endl;
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
             if(EliminarPlatillo()!= -1){
                            cout<<endl;
                            cout<<"PLATILLO ELIMINADO";
                            cout<<endl;
                            system("pause");
                        }else {
                             cout<<endl;
                            cout<<"NO SE PUDO ELIMINAR EL PLATILLO";
                            cout<<endl;
                            system("pause");
                        }
            break;
        case 3:
            listarPlatillos();
            break;
        case 4:
            listarProductosxPlatillo();
            system("pause");
            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}
