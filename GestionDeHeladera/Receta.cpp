#include <iostream>
#include<string>
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
    int cont=0, opc;
    Receta *vRecetas;
    int cantReg = CantidadRegistrosProductosxPlatillos();
    vRecetas = new Receta [cantReg];
    if(vRecetas==NULL){exit(1);}

    //carga el vector con las recetas en orden
    cargarVectorConRecetas(vRecetas, cantReg);

    cout << "LISTADO DE RECETAS" << endl;
    cout << "----------------------------------" << endl;
    for(int i=0; i<cantReg; i++)
    {
        if(vRecetas[i].getIdReceta() != 0)
        {
          cout<<i+1<<"."<<mostrarNombrePlatillo(vRecetas[i].getIdReceta())<<endl;
          cont++;
        }
    }
    cout << "----------------------------------" << endl;
    cout << "Total: " << cont << " recetas.";

    cout<<endl;
    cout<<endl;

    //si no hay recetas disponibles sale para no hacer elegir
    if(cont == 0){
        cout<<"Lo sentimos no hay recetas disponibles, presione 0 para salir: ";
        cin>>opc;
        if(opc == 0){
        return;
        }
    }


    cout<<endl;
    cout<<endl;
    //muestra de la opcion elegida los ingredientes y las instrucciones
    elegirReceta(vRecetas);

    delete vRecetas;
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



void elegirReceta(Receta *vRecetas)
{
    int opcion;
    ProductosxPlatillo aux;
    int cantReg = CantidadRegistrosProductosxPlatillos();

    cout<<endl;
    cout<<"Ingrese la opcion seleccionada: ";
    cin>>opcion;

    if(opcion==0){
        return;
    }

    while(vRecetas[opcion-1].getIdReceta() == 0){
        cout<<endl;
        cout<<"Opcion no existente, por favor ingrese otra: ";
        cin>>opcion;
    }
        cout<<endl;
        cout<<endl;
        cout<<"Ingredientes: ";
        for(int i=0; i<cantReg; i++)
        {
            aux.LeerDeDisco(i);
            if(vRecetas[opcion-1].getIdPlatillo() == aux.getIdPlatillo())
            {
                cout<< mostrarNombreProducto(aux.getIdProducto())<<", ";
            }
        }
            cout<<endl;
            cout<<endl;
            cout<<"Intrucciones: " <<vRecetas[opcion-1].getDescripcion();
            cout<<endl;
            cout<<endl;
}

//se llena el vector con todas las recetas que tengan stock de productos
void buscarRecetaQueTegaStockDeProductos(Receta *vRecetas, int tam){
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
                vRecetas[pos++] = aux;
                }
            }
        }
    }
}

bool controlarStockDeProductosPorPlatillos(int idPlatillo){

     ProductosxPlatillo aux;
     int cantReg = CantidadRegistrosProductosxPlatillos();
     int contProductos=0, contStock=0;

        for(int i=0; i<cantReg; i++)
        {
                if(aux.LeerDeDisco(i))
                {
                    if(aux.getIdPlatillo() == idPlatillo)
                    {
                         //cuenta la cantidad de productos del platillo
                         contProductos++;
                       if(consultarStock(aux.getIdProducto())> 0)
                        {
                         //cuenta la cantidad de productos que tienen stock
                         contStock++;
                        }
                    }
                }
        }

            //si son iguales es que todos los productos tienen stock
            if(contProductos==contStock)
            {
               return true;
            }

    return false;
}

void sugerenciaRecetas(){

 Receta *vRecetas;
 int cont=0, opc;
 int cantReg = CantidadRegistrosProductosxPlatillos();
 vRecetas = new Receta [cantReg];
 if(vRecetas==NULL){exit(1);}

   //lena el vector con todas las recetas que hay con stock de productos
   buscarRecetaQueTegaStockDeProductos(vRecetas, cantReg);

    cout << "SUGERENCIAS DE RECETAS SEGUN STOCK DE PRODUCTOS" << endl;
    cout << "----------------------------------" << endl;
    for(int i=0; i<cantReg; i++)
    {
        if(vRecetas[i].getIdReceta() != 0)
        {
          cout<<i+1<<"."<<mostrarNombrePlatillo(vRecetas[i].getIdReceta())<<endl;
          cont++;
        }
    }
    cout << "----------------------------------" << endl;
    cout << "Total: " << cont << " recetas.";

    cout<<endl;
    cout<<endl;

    //si no hay recetas disponibles sale para no hacer elegir
     if(cont == 0){
        cout<<"Lo sentimos no hay recetas disponibles, presione 0 para salir: ";
        cin>>opc;
        if(opc == 0){
        return;
        }
     }

      cout<<endl;
      cout<<endl;

    //muestra de la opcion elegida los ingredientes y las instrucciones
    elegirReceta(vRecetas);

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
        case 4: sugerenciaRecetas();
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
