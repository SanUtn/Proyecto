#include <iostream>
#include<string>
#include "Receta.h"
#include "FuncionesGlobales.h"

using namespace std;

string Receta::getDescripcion()
{
    string descripciones;
    descripciones = descripcion;
    return descripciones;
}

string Receta::toString()
{
    string cadena;
    cadena = "Id receta: " + to_string(idReceta) + " " " " + " Id Platillo: " + mostrarNombrePlatillo(getIdReceta()) + " " " " + " Instrucciones: " + getDescripcion();
    return cadena;
}

bool Receta::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("Recetas.dat", "rb");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        return false;
    }
    fseek(p, pos*sizeof(Receta),0);
    leyo=fread(this,sizeof(Receta),1,p);

    fclose(p);

    return leyo;
}

bool Receta::GrabarEnDisco()
{
    FILE *p;
    p=fopen("Recetas.dat", "ab");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        return false;
    }
    int escribio=fwrite(this, sizeof(Receta),1,p);
    fclose(p);

    return escribio;
}



//METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
//HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
bool Receta::ModificarArchivo(int pos)
{
    FILE *p;
    p=fopen("Recetas.dat", "rb+");
    if(p==NULL)
    {
        cout<<"El archivo no pudo abrirse"<<endl;
        return false;
    }
    fseek(p, pos*sizeof(Receta),0);
    int escribio=fwrite(this, sizeof(Receta),1,p);
    fclose(p);

   return escribio;
}


/// Funciones globales para gestionar Usuario
bool nuevaReceta()
{
    Receta reg;
    reg = cargarReceta();
    bool ok = reg.GrabarEnDisco();
    return ok;
}

int CantidadRegistrosReceta()
{
    FILE *p;
    p=fopen("Recetas.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    size_t bytes;
    int cantidad;

    fseek(p, 0, SEEK_END);
    bytes=ftell(p);

    fclose(p);
    cantidad = bytes/sizeof(Receta);
    return cantidad;
}

Receta cargarReceta()
{
    int id;
    int idPlatillo;
    string descripcion;
    bool estado = true;

    id = CantidadRegistrosReceta()+1;

    listarPlatillos();
    cout<<endl;

    cout << "Ingrese el Id del Platillo: ";
    cin >> idPlatillo;
    cout << "Ingrese la descripcion: ";
    cin.ignore();
    getline(cin, descripcion);

    Receta reg;
    reg.setIdReceta(id);
    reg.setIdPlatillo(idPlatillo);
    reg.setDescripcion(descripcion);
    reg.setEstadoReceta(estado);
    cout<<endl;
    cout<<endl;
    system("pause");
    return reg;
}


void listarRecetas()
{
    Receta aux;
    int cont=0;
    int cantRecetas = CantidadRegistrosReceta();
    cout << "LISTADO DE RECETAS" << endl;
    cout << "----------------------------------" << endl;
    for(int i=0; i<cantRecetas; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoReceta())
        {
            cout<<aux.toString()<<endl;
        }else{
        cont++;
        }
    }
    cout << "----------------------------------" << endl;
    cout << "Total: " << cantRecetas - cont << " recetas.";
    cout<<endl;
    cout<<endl;
    system("pause");
}

int EliminarReceta()
{
    Receta aux;
    int pos=0, idReceta;

    listarRecetas();
    cout<<endl;

    cout<<"Ingrese el ID de la receta a eliminar: ";
    cin>>idReceta;

    while(aux.LeerDeDisco(pos)==1)
    {
        if(aux.getIdReceta() == idReceta)
        {
            aux.setEstadoReceta(false);
            aux.ModificarArchivo(pos);
            return pos;
        }
        pos++;
    }
    return -1;
}


void menuRecetas()
{
    int opc;
    while(true)
    {
        system("cls");

        cout<<"MENU RECETAS"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. AGREGAR RECETAS "<<endl;
        cout<<"2. ELIMINAR RECETA" <<endl;
        cout<<"3. LISTAR RECETAS "<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: "<<endl;
        cin>>opc;

        system("cls");

        switch(opc)
        {
        case 1:
            if(nuevaReceta())
            {
                cout<<endl;
                cout<<"RECETA AGREGADA";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO AGREGAR LA RECETA";
                cout<<endl;
                system("pause");
            }
            break;
        case 2:
            if(EliminarReceta()!= -1)
            {
                cout<<endl;
                cout<<"RECETA ELIMINADA";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO ELIMINAR LA RECETA";
                cout<<endl;
                system("pause");
            }
            break;
        case 3:
            listarRecetas();
            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}
