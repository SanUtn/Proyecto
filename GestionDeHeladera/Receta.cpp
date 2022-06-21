#include <iostream>
#include<string>
#include<iomanip>
#include "Receta.h"
#include "FuncionesGlobales.h"
#include "ProductosxPlatillo.h"

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

void listarRecetas()
{
    Receta aux;
    int cont=0, opc, opcion;
    int cantReg = CantidadRegistrosReceta();

    cout << left;
    cout << setw(10) << "\t";
    cout << "RECETAS" << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << setw(4)  << "ID";
    cout << setw(15) << "PLATILLO" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for(int i=0; i<cantReg; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoReceta())
        {
            cout << left;
            cout << setw(4)  << aux.getIdReceta();
            cout << setw(15) << mostrarNombrePlatillo(aux.getIdPlatillo()) << endl;
            cont++;
        }
    }
    cout << "----------------------------------" << endl;
    cout << "Total: " << cont << " recetas.";

    cout<<endl;
    cout<<endl;

    //si no hay recetas disponibles sale para no hacer elegir
    if(cont == 0)
    {
        cout<<"Lo sentimos no hay recetas disponibles.";
        system("pause");
        return;
    }

    cout<<endl;
    cout<<endl;

    cout<<"Ingrese la opcion seleccionada o 0 para salir: ";
    cin>>opcion;

    if(opcion==0)
    {
        return;
    }

    while(validarExisteReceta(opcion) == false)
    {
        cout<<endl;
        cout<<"Opcion no existente, por favor ingrese otra: ";
        cin>>opcion;
    }
    //muestra de la opcion elegida los ingredientes y las instrucciones
    elegirReceta(opcion);
}

void cargarVectorConRecetas(Receta *vRecetas, int tam)
{
    Receta aux;
    int pos=0;

    ponerEnCeroElVectorDeRecetas(vRecetas,tam);

    for(int i=0; i<tam; i++)
    {
        if(aux.LeerDeDisco(i))
        {
            if(aux.getEstadoReceta())
            {
                vRecetas[pos++] = aux;
            }
        }
    }
}

void ponerEnCeroElVectorDeRecetas(Receta *vRecetas, int tam)
{
    for(int i=0; i<tam; i++)
    {
        vRecetas[i].setIdReceta(0);
    }
}

void EliminarRecetaPorParametro(int idreceta)
{
    Receta aux;
    int pos=0;

    while(aux.LeerDeDisco(pos)==1)
    {
        if(aux.getIdReceta() == idreceta)
        {
            aux.setEstadoReceta(false);
            aux.ModificarArchivo(pos);
            return;
        }
        pos++;
    }
}

bool validarExisteReceta(int idreceta)
{
    Receta reg;
    int pos = 0;


    while(reg.LeerDeDisco(pos))
    {
        if(reg.getIdReceta() == idreceta && reg.getEstadoReceta())
        {
            return true;
        }
        pos++;
    }
    return false;
}

void elegirReceta(int opc)
{
    Receta reg;
    int pos = 0;
    int *vProductos;


    //int cantReg = CantidadRegistrosProductosxPlatillos();

    while(reg.LeerDeDisco(pos))
    {
        if(reg.getIdReceta() == opc)
        {
            int cantReg = CantidadProductosxPlatillo(reg.getIdPlatillo());
            vProductos = new int [cantReg];
            buscarProductosXPlatillo(reg.getIdPlatillo(), vProductos, cantReg);

            cout<<endl;
            cout<<endl;
            cout<<"Ingredientes: ";
            for(int i=0; i<cantReg; i++)
            {
                cout<< mostrarNombreProducto(vProductos[i])<<", ";
            }
            cout<<endl;
            cout<<endl;
            cout<<"Intrucciones: " <<reg.getDescripcion();
            cout<<endl;
            cout<<endl;
        }
        pos++;
    }
    delete vProductos;
}


//se llena el vector con todas las recetas que tengan stock de productos
void buscarRecetaQueTegaStockDeProductos(Receta *vRecetas, int tam)
{
    Receta aux;
    int pos=0;

    ponerEnCeroElVectorDeRecetas(vRecetas, tam);

    for(int i=0; i<tam; i++)
    {
        if(aux.LeerDeDisco(i))
        {
            if(aux.getEstadoReceta())
            {
                if(controlarStockDeProductosPorPlatillos(aux.getIdPlatillo()))
                {
                    vRecetas[i] = aux;
                }
            }
        }
    }
}

bool controlarStockDeProductosPorPlatillos(int idPlatillo)
{

    ProductosxPlatillo aux;
    int cantReg = CantidadProductosxPlatillo(idPlatillo);
    bool bandera = true;
    int pos = 0;

    while(aux.LeerDeDisco(pos)){
            if(aux.getIdPlatillo() == idPlatillo){
                if(consultarStock(aux.getIdProducto()) <= 0){
                    return false;
                   }
            }
        pos++;
    }
    return true;
}

void sugerenciaRecetas()
{

    Receta *vRecetas;
    int cont=0, opcion;
    //int cantReg = CantidadRegistrosProductosxPlatillos();
    int cantReg = CantidadRegistrosReceta();
    vRecetas = new Receta [cantReg];
    if(vRecetas==NULL)
    {
        exit(1);
    }

    //lena el vector con todas las recetas que hay con stock de productos
    buscarRecetaQueTegaStockDeProductos(vRecetas, cantReg);

    cout << "SUGERENCIAS DE RECETAS SEGUN STOCK DE PRODUCTOS" << endl;
    cout << "----------------------------------" << endl;
    for(int i=0; i<cantReg; i++)
    {
        if(vRecetas[i].getIdReceta() != 0)
        {
            cout<<i+1<<"."<<mostrarNombrePlatillo(vRecetas[i].getIdPlatillo())<<endl;
            cont++;
        }
    }
    cout << "----------------------------------" << endl;
    cout << "Total: " << cont << " recetas.";

    cout<<endl;
    cout<<endl;

     //si no hay recetas disponibles sale para no hacer elegir
    if(cont == 0)
    {
        cout<<"Lo sentimos no hay recetas disponibles.";
        system("pause");
        return;
    }

    cout<<endl;
    cout<<endl;

    cout<<"Ingrese la opcion seleccionada o 0 para salir: ";
    cin>>opcion;

    if(opcion==0)
    {
        return;
    }

    while(validarExisteReceta(opcion) == false)
    {
        cout<<endl;
        cout<<"Opcion no existente, por favor ingrese otra: ";
        cin>>opcion;
    }
    //muestra de la opcion elegida los ingredientes y las instrucciones
    elegirReceta(opcion);

    delete vRecetas;
}

void menuRecetas()
{
    int opc;
    while(true)
    {
        system("cls");

        cout<<"MENU RECETAS"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. AGREGAR RECETA "<<endl;
        cout<<"2. ELIMINAR RECETA" <<endl;
        cout<<"3. LISTAR RECETAS "<<endl;
        cout<<"4. SUGERENCIAS POR STOCK DE PRODUCTOS "<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: ";
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
            cout<<endl;
            cout<<endl;
            system("pause");
            break;
        case 4:
            sugerenciaRecetas();
            cout<<endl;
            cout<<endl;
            system("pause");

            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}
