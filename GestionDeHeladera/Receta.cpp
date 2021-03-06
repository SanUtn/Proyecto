#include <iostream>
#include<string>
#include<iomanip>
#include "rlutil.h"
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
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
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
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
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
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    fseek(p, pos*sizeof(Receta),0);
    int escribio=fwrite(this, sizeof(Receta),1,p);
    fclose(p);

    return escribio;
}


/// FUINCIONES GLOBALES
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

    cout<<endl;
    listarPlatillos();
    cout<<endl;

    cout << "Ingrese el Id del Platillo: ";
    cin >> idPlatillo;
    cout<<endl;

    while(validarNumero())
    {
        cin >> idPlatillo;
    }
    while(validarPlatilloExistenteXId(idPlatillo)== false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout <<"Platillo inexistente, ingrese otro: ";
        cin >> idPlatillo;
        cout<<endl;
        while(validarNumero())
        {
            cin >> idPlatillo;
        }
        rlutil::setColor(rlutil::BROWN);
    }

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
    cout<<endl;
    //system("pause");
    return reg;
}


int EliminarReceta()
{
    Receta aux;
    int pos=0, idReceta;

    cout<<endl;
    listarRecetas2();
    cout<<endl;

    cout<<"Ingrese el ID de la receta a eliminar: ";
    cin>>idReceta;

    while(validarNumero())
    {
        cin >> idReceta;
    }

    while(aux.LeerDeDisco(pos)==1)
    {
        if(aux.getIdReceta() == idReceta && aux.getEstadoReceta()== true)
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
    int cont=0, opcion;
    int cantReg = CantidadRegistrosReceta();

    cout<<endl;
    cout<<endl;
    cout << left;
    cout << setw(10) << "\t";
    rlutil::setColor(rlutil::MAGENTA);
    cout << "LISTADO DE RECETAS" << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "--------------------------------------"  << endl;
    cout << left;
    cout << "\t";
    cout << setw(10)  << "ID";
    cout << setw(20) << "PLATILLO" << endl;
    cout << "\t" << "--------------------------------------" << endl;

    for(int i=0; i<cantReg; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoReceta())
        {
            rlutil::setColor(rlutil::LIGHTCYAN);
            cout << left;
            cout << "\t";
            cout << setw(10)  << aux.getIdReceta();
            cout << setw(20) << mostrarNombrePlatillo(aux.getIdPlatillo()) << endl;
            cont++;
        }
    }
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "--------------------------------------" << endl;
    cout << "\t" << "Total: " << cont << " recetas.";

    cout<<endl;
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);

    //si no hay recetas disponibles sale para no hacer elegir
    if(cont == 0)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout<<"Lo sentimos no hay recetas disponibles.";
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
        system("pause");
        return;
    }

    cout<<endl;
    cout<<endl;

    cout<<"Ingrese la opcion seleccionada o 0 para salir: ";
    cin>>opcion;

    cout<<endl;

    while(validarNumero())
    {
        cin >> opcion;
    }

    if(opcion==0)
    {
        return;
    }

    while(validarExisteReceta(opcion) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout<<"Opcion inexistente, por favor ingrese otra: ";
        cin>>opcion;
        cout<<endl;
        while(validarNumero())
        {
            cin >> opcion;
        }
        rlutil::setColor(rlutil::BROWN);
    }


    //muestra de la opcion elegida los ingredientes y las instrucciones
    elegirReceta(opcion);
    rlutil::setColor(rlutil::BROWN);
}

void listarRecetas2()
{
    Receta aux;
    int cont=0;
    int cantReg = CantidadRegistrosReceta();

    cout<<endl;
    cout<<endl;
    cout << left;
    cout << setw(10) << "\t";
    rlutil::setColor(rlutil::MAGENTA);
    cout << "LISTADO DE RECETAS" << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "--------------------------------------"  << endl;
    cout << left;
    cout << "\t";
    cout << setw(10)  << "ID";
    cout << setw(20) << "PLATILLO" << endl;
    cout << "\t" << "--------------------------------------" << endl;

    for(int i=0; i<cantReg; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoReceta())
        {
            rlutil::setColor(rlutil::LIGHTCYAN);
            cout << left;
            cout << "\t";
            cout << setw(10)  << aux.getIdReceta();
            cout << setw(20) << mostrarNombrePlatillo(aux.getIdPlatillo()) << endl;
            cont++;
        }
    }
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "--------------------------------------" << endl;
    cout << "\t" << "Total: " << cont << " recetas.";

    cout<<endl;
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);

    //si no hay recetas disponibles sale para no hacer elegir
    if(cont == 0)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout<<"Lo sentimos no hay recetas disponibles.";
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
        system("pause");
        return;
    }

    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);

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
        if(aux.getIdReceta() == idreceta && aux.getEstadoReceta()==true)
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
        if(reg.getIdReceta() == idreceta && reg.getEstadoReceta()==true)
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

    while(reg.LeerDeDisco(pos))
    {
        if(reg.getIdReceta() == opc && reg.getEstadoReceta()==true)
        {
            int cantReg = CantidadProductosxPlatillo(reg.getIdPlatillo());
            vProductos = new int [cantReg];
            if(vProductos==NULL)
            {
                return;
            }

            //funcion que se encuentra en stock, llena el vector con los productos del platillo consultado.
            buscarProductosXPlatillo(reg.getIdPlatillo(), vProductos, cantReg);

            rlutil::setColor(rlutil::LIGHTGREEN);
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
            rlutil::setColor(rlutil::BROWN);

        }
        pos++;
    }
    delete vProductos;
    rlutil::setColor(rlutil::BROWN);
}

//aca si valida que haya stock en los productos para mostrar la receta
bool elegirReceta2(int opc)
{
    Receta reg;
    int pos = 0;
    Producto *vProductos;



    while(reg.LeerDeDisco(pos))
    {
        if(reg.getIdReceta() == opc && reg.getEstadoReceta()==true)
        {
            int cantReg = CantidadProductosxPlatillo(reg.getIdPlatillo());
            vProductos = new Producto [cantReg];
            if(vProductos==NULL)
            {
                exit(1);
            }
            //controlar que tengan stock esos productos
            if(controlarStockDeProductosPorPlatillos(reg.getIdPlatillo()))
            {

                //se encuentra en funciones globales, llena el vector con los productos de ese platillo
                copiarProductos(vProductos, cantReg, reg.getIdPlatillo());

                rlutil::setColor(rlutil::LIGHTGREEN);
                cout<<endl;
                cout<<endl;
                cout<<"Ingredientes: ";
                for(int i=0; i<cantReg; i++)
                {
                    cout<< mostrarNombreProducto(vProductos[i].getIdProducto())<<", ";
                }
                cout<<endl;
                cout<<endl;
                cout<<"Intrucciones: " <<reg.getDescripcion();
                cout<<endl;
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
            }
            else
            {
                return false;
            }
        }
        pos++;
    }
    delete vProductos;
    rlutil::setColor(rlutil::BROWN);
    return true;
}

void buscarProductosDelPlatillo(int idP, int *vProductos, int tam)
{
    ProductosxPlatillo aux;
    int pos = 0;
    bool bandera;
    ponerEnCeroElVector(vProductos,tam);

    for(int i=0; i<tam; i++)
    {
        bandera = false;
        while(aux.LeerDeDisco(pos) && bandera == false)
        {
            if(aux.getIdPlatillo()==idP)
            {
                vProductos[i] = aux.getIdProducto();
                bandera = true;
                //que sea diferente al ya guardado
            }
            pos++;
        }
    }

}


//se llena el vector con todas las recetas que tengan stock de productos
void buscarRecetaQueTegaStockDeProductos(Receta *vRecetas, int tam)
{
    Receta aux;

    ponerEnCeroElVectorDeRecetas(vRecetas, tam);

    for(int i=0; i<tam; i++)
    {
        if(aux.LeerDeDisco(i))
        {
            if(aux.getEstadoReceta()==true)
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

    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if(aux.getIdPlatillo() == idPlatillo)
        {
            if(consultarStock(aux.getIdProducto()) <= 0)
            {
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
    bool elegir=true;
    int cantReg = CantidadRegistrosReceta();
    vRecetas = new Receta [cantReg];
    if(vRecetas==NULL)
    {
        return;
    }

    //lena el vector con todas las recetas que hay con stock de productos
    buscarRecetaQueTegaStockDeProductos(vRecetas, cantReg);

    rlutil::setColor(rlutil::MAGENTA);
    cout<<endl;
    cout<<endl;
    cout << left;
    cout << "\t";
    cout << "SUGERENCIAS DE RECETAS SEGUN STOCK DE PRODUCTOS" << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-----------------------------------------------" << endl;

    for(int i=0; i<cantReg; i++)
    {
        if(vRecetas[i].getIdReceta() != 0)
        {
            rlutil::setColor(rlutil::LIGHTCYAN);
            cout << "\t" << "\t";
            cout<<i+1<<"."<<mostrarNombrePlatillo(vRecetas[i].getIdPlatillo())<<endl;
            cont++;
        }
    }
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-----------------------------------------------" << endl;
    cout << "\t" << "Total: " << cont << " recetas.";

    cout<<endl;
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);

    //si no hay recetas disponibles sale para no hacer elegir
    if(cont == 0)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout<<"Lo sentimos no hay recetas disponibles.";
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
        return;
    }

    cout<<endl;
    cout<<endl;

    cout<<"Ingrese la opcion seleccionada o 0 para salir: ";
    cin>>opcion;

    while(validarNumero())
    {
        cin >> opcion;
    }

    if(opcion==0)
    {
        return;
    }

    while(validarExisteReceta(opcion) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout<<"Opcion no existente, por favor ingrese otra: ";
        cin>>opcion;
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }
    //muestra de la opcion elegida los ingredientes y las instrucciones
    elegir = elegirReceta2(opcion);

    //si elige una receta que existe pero no tiene stock
    if(elegir == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout<<endl;
        cout<<"Lo sentimos no hay stock de productos para la receta seleccionada.";
        cout<<endl;
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
        return;
    }

    delete vRecetas;
    rlutil::setColor(rlutil::BROWN);
}

void menuRecetas()
{
    int opc;
    while(true)
    {
        system("cls");
        rlutil::locate(59, 5);
        rlutil::setColor(rlutil::CYAN);
        cout<<"MENU RECETAS"<<endl;
        rlutil::locate(40, 6);
        cout<<"----------------------------------------------------"<<endl;
        rlutil::setColor(rlutil::LIGHTCYAN);
        rlutil::locate(48,8);
        cout<<"1. AGREGAR RECETA "<<endl;
        rlutil::locate(48,9);
        cout<<"2. ELIMINAR RECETA" <<endl;
        rlutil::locate(48,10);
        cout<<"3. LISTAR RECETAS "<<endl;
        rlutil::locate(48,11);
        cout<<"4. SUGERENCIAS POR STOCK DE PRODUCTOS "<<endl;
        rlutil::locate(48,12);
        cout<<"-------------------------------------"<<endl;
        rlutil::locate(48,13);
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        rlutil::locate(48,16);
        rlutil::setColor(rlutil::DARKGREY);
        cout<<"OPCION: ";
        cin>>opc;

        rlutil::setColor(rlutil::BROWN);
        system("cls");

        switch(opc)
        {
        case 1:
            if(nuevaReceta())
            {
                rlutil::setColor(rlutil::GREEN);
                cout<<endl;
                cout<<"RECETA AGREGADA";
                cout<<endl;
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
                system("pause");
            }
            else
            {
                rlutil::setColor(rlutil::RED);
                cout<<endl;
                cout<<"NO SE PUDO AGREGAR LA RECETA";
                cout<<endl;
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
                system("pause");
            }
            break;
        case 2:
            if(EliminarReceta()!= -1)
            {
                rlutil::setColor(rlutil::GREEN);
                cout<<endl;
                cout<<"RECETA ELIMINADA";
                cout<<endl;
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
                system("pause");
            }
            else
            {
                rlutil::setColor(rlutil::RED);
                cout<<endl;
                cout<<"NO SE PUDO ELIMINAR LA RECETA";
                cout<<endl;
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
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
