#include <iostream>
#include <iomanip>
#include "FuncionesGlobales.h"

using namespace std;

void menuConsumos()
{
    int opc;
    while(true)
    {
        system("cls");

        cout<<"MENU CONSUMOS"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. AGREGAR CONSUMO PRODUCTO "<<endl;
        cout<<"2. LISTAR CONSUMO PRODUCTOS"<<endl;
        cout<<"3. AGREGAR CONSUMO PLATILLO "<<endl;
        cout<<"4. LISTAR CONSUMO PLATILLOS"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: ";
        cin>>opc;

        system("cls");

        switch(opc)
        {
        case 1:
            if(nuevoConsumoProducto())
            {

                cout<<endl;
                cout<<"CONSUMO AGREGADO";
                cout<<endl;
                system("pause");
            }
            else
            {
                cout<<endl;
                cout<<"NO SE PUDO AGREGAR EL CONSUMO";
                cout<<endl;
                system("pause");
            }
            break;
        case 2:
            listarConsumosPoductos();
            break;
        case 3:
            menuSugerenciasPlatillos();
            break;
        case 4:
            listarConsumosPlatillo();
            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}

int CantidadProductosxPlatillo(int idplatillo){
    ProductosxPlatillo reg;
    int pos = 0;
    int cant = 0;

    while(reg.LeerDeDisco(pos)){
            if(reg.getIdPlatillo() == idplatillo){
                cant++;
            }
        pos++;
    }

    return cant;
}

int buscarStockDeProducto(int idproducto)
{
    ProductoStock reg;
    int pos = 0;

    while(reg.LeerDeDisco(pos))
    {
        if(reg.getIdProducto() == idproducto)
        {
            return reg.getStock();
        }
        pos++;
    }
    return -1;
}


void copiarProductos(Producto *vDinamico, int cantidad, int idplatillo)
{
    ProductosxPlatillo reg;
    int pos = 0;
    int i = 0;

    while(reg.LeerDeDisco(pos) && cantidad != 0)
    {
        if(reg.getIdPlatillo() == idplatillo)
        {
            vDinamico[i].setIdProducto(reg.getIdProducto());
            i++;
            cantidad--;
        }
        pos++;
    }
}



void menuReportes()
{
    int opc;
    while(true)
    {
        system("cls");

        cout<<"MENU REPORTES"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. CONSUMOS ANUALES "<<endl;
        cout<<"2. CONSUMOS MENSUALES"<<endl;
        cout<<"3. MENU DE SUGERENCIAS"<<endl;
        cout<<"4. ALERTA DE STOCK"<<endl;
        cout<<"5. ALERTA SIN STOCK"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: ";
        cin>>opc;

        system("cls");

        switch(opc)
        {
        case 1:
            menuConsumosAnuales();
            break;
        case 2:
            menuConsumosMensuales();
            break;
        case 3:
            //MenuSugerencias();
            system("pause");
            break;
        case 4:
            alertaStock();
            system("pause");
            break;
             case 5:
            alertaSinStock();
            system("pause");
            break;
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}

void menuConsumosAnuales()
{
    int opc;
    while(true)
    {
        system("cls");

        cout<<"MENU CONSUMOS ANUALES"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. CONSUMOS PLATILLOS "<<endl;
        cout<<"2. CONSUMOS PRODUCTOS"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: ";
        cin>>opc;

        system("cls");

        switch(opc)
        {
        case 1:
            PlatillosAnual();
            cout<<endl;
            cout<<endl;
            system("pause");
            break;
        case 2:
            ProductosAnual();
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

void menuConsumosMensuales()
{
    int opc;
    while(true)
    {
        system("cls");

        cout<<"MENU CONSUMOS MENSUALES"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"1. CONSUMOS PLATILLOS "<<endl;
        cout<<"2. CONSUMOS PRODUCTOS"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        cout<<"OPCION: ";
        cin>>opc;

        system("cls");

        switch(opc)
        {
        case 1:
            PlatillosMensual();
            cout<<endl;
            cout<<endl;
            system("pause");
            break;
        case 2:
            ProductosMensual();
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

string mostrarOrientacionAlimentaria(int id)
{
    OrientacionAlimentaria aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if (aux.getIdOrientacionAlimentaria() == id)
        {
            return aux.getDescripcion();
        }
        pos++;
    }
}

string mostrarNombreProducto(int id)
{
    Producto aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if (aux.getIdProducto() == id)
        {
            return aux.getNombreProducto();
        }
        pos++;
    }
}

string mostrarNombrePlatillo(int id)
{
    Platillo aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if (aux.getIdPlatillo() == id)
        {
            return aux.getNombrePlatillo();
        }
        pos++;
    }
}

string mayuscula(string cadena)
{
    for (int i = 0; i < cadena.length(); i++) cadena[i] = toupper(cadena[i]);
    return cadena;
}



void eliminarStock(int idproducto)
{
    ProductoStock reg;
    int pos = 0;

    while(reg.LeerDeDisco(pos))
    {
        if(reg.getIdProducto() == idproducto && reg.getEstadoStock())
        {
            reg.setEstadoStock(false);
            reg.ModificarArchivo(pos);
        }
        pos++;
    }
}

void eliminarPlatillos(int idproducto)
{
    ProductosxPlatillo reg;
    Platillo aux;
    int pos = 0;

    while(reg.LeerDeDisco(pos))
    {
        if(reg.getIdProducto() == idproducto)
        {
            EliminarPlatilloPorParametro(reg.getIdPlatillo());
            eliminarRecetasPorPlatillo(reg.getIdPlatillo());
        }
        pos++;
    }
}

void eliminarRecetasPorPlatillo(int idplatillo)
{
    Receta reg;
    int pos = 0;

    while(reg.LeerDeDisco(pos))
    {
        if(reg.getIdPlatillo() == idplatillo)
        {
            EliminarRecetaPorParametro(reg.getIdReceta());
        }
        pos++;
    }
}

    void modificarVencimientoProducto(int idproducto, Fecha fecha){
        Producto reg;
        int pos = 0;

        while(reg.LeerDeDisco(pos)){
                if(reg.getIdProducto() == idproducto){
                    reg.setFechaVencimiento(fecha);
                    reg.ModificarArchivo(pos);
                }
            pos++;
        }
    }

void prueba()
{
    Producto reg;

    int pos = 0;

    while(reg.LeerDeDisco(pos))
    {
        cout << reg.toString() << endl;
        pos++;
    }
}

void PlatillosAnual()
{
    ConsumoPlatillo reg;
    int pos = 0;
    int opc;
    bool bandera=true; //para mostrar el encabezado.

    cout << "Ingrese el anio a consultar: ";
    cin >> opc;

        cout<<endl;
        cout<<endl;

    while(reg.LeerDeDisco(pos++))
    {
        if (reg.getFechaConsumo().getAnio() == opc)
        {
            if(bandera==true){
                cout << left;
                cout << setw(15) << "\t";
                cout << "CONSUMOS ANUALES DE PLATILLOS" << endl;
                cout << "---------------------------------------------------------------" << endl;
                cout << setw(15)  << "PLATILLO";
                cout << setw(15) << "FECHA CONSUMO";
                cout << setw(15) << "DNI USUARIO" << endl;
                cout << "---------------------------------------------------------------" << endl;
                bandera = false;
            }
            reg.toList();
        }else{
        cout<<endl;
        cout<<"No existen consumos, ingrese otro anio o 0 para salir: ";
        cin>>opc;
        cout<<endl;
            if(opc==0){
                return;
            }else{
                bandera=true;//para que vuelva a mostrar el encabezado.
                pos=0;//para que vuelva a recorrer todos
            }
        }
    }
}

void PlatillosMensual()
{
    ConsumoPlatillo reg;
    int pos = 0;
    int opc;
    bool bandera = true;

    cout << "Ingrese el mes a consultar: ";
    cin >> opc;

    cout<<endl;
    cout<<endl;

    while(reg.LeerDeDisco(pos++))
    {
        if (reg.getFechaConsumo().getMes() == opc)
        {
            if(bandera==true){
                cout << left;
                cout << setw(15) << "\t";
                cout << "CONSUMOS MENSUALES DE PLATILLOS" << endl;
                cout << "---------------------------------------------------------------" << endl;
                cout << setw(15)  << "PLATILLO";
                cout << setw(15) << "FECHA CONSUMO";
                cout << setw(15) << "DNI USUARIO" << endl;
                cout << "---------------------------------------------------------------" << endl;
                bandera = false;
            }
            reg.toList();
        }else{
        cout<<endl;
        cout<<"No existen consumos, ingrese otro MES o 0 para salir: ";
        cin>>opc;
        cout<<endl;
            if(opc==0){
                return;
            }else{
                bandera=true;//para que vuelva a mostrar el encabezado.
                pos=0;//para que vuelva a recorrer todos
            }
        }
    }
}

void ProductosAnual()
{
    ConsumoProducto reg;
    int pos = 0;
    int opc;
    bool bandera=true; //para mostrar el encabezado.

    cout << "Ingrese el anio a consultar: ";
    cin >> opc;

        cout<<endl;
        cout<<endl;

    while(reg.LeerDeDisco(pos++))
    {
        if (reg.getFechaConsumo().getAnio() == opc)
        {
            if(bandera==true){
                cout << left;
                cout << setw(15) << "\t";
                cout << "CONSUMOS PRODUCTOS" << endl;
                cout << "---------------------------------------------------------------" << endl;
                cout << setw(15)  << "PRODUCTO";
                cout << setw(15) << "FECHA CONSUMO" << endl;
                cout << "---------------------------------------------------------------" << endl;
                bandera = false;
            }
            reg.toList();
        }else{
        cout<<endl;
        cout<<"No existen consumos, ingrese otro anio o 0 para salir: ";
        cin>>opc;
        cout<<endl;
            if(opc==0){
                return;
            }else{
                bandera=true;//para que vuelva a mostrar el encabezado.
                pos=0;//para que vuelva a recorrer todos
            }
        }
    }
}

void ProductosMensual()
{
    ConsumoProducto reg;
    int pos = 0;
    int opc;
    bool bandera = true;

    cout << "Ingrese el mes a consultar: ";
    cin >> opc;

    cout<<endl;
    cout<<endl;

    while(reg.LeerDeDisco(pos++))
    {
        if (reg.getFechaConsumo().getMes() == opc)
        {
            if(bandera==true){
                cout << left;
                cout << setw(15) << "\t";
                cout << "CONSUMOS PRODUCTO" << endl;
                cout << "---------------------------------------------------------------" << endl;
                cout << setw(15)  << "PRODUCTO";
                cout << setw(15) << "FECHA CONSUMO" << endl;
                cout << "---------------------------------------------------------------" << endl;
                bandera = false;
            }
            reg.toList();
        }else{
        cout<<endl;
        cout<<"No existen consumos, ingrese otro MES o 0 para salir: ";
        cin>>opc;
        cout<<endl;
            if(opc==0){
                return;
            }else{
                bandera=true;//para que vuelva a mostrar el encabezado.
                pos=0;//para que vuelva a recorrer todos
            }
        }
    }
}

void alertaStock()
{
    ProductoStock aux;
    int cont=0;
    int cantStocks = CantidadRegistrosStock();
    cout << "PRODUCTOS PROXIMOS A AGOTARSE" << endl;
    cout << "----------------------------------" << endl;
    for(int i=0; i<cantStocks; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoStock() &&  aux.getStock()<= 2 && aux.getStock()!= 0 )
        {
            cout<<aux.toString()<<endl;
        }
        else
        {
            cont++;
        }
    }
    cout << "----------------------------------" << endl;
    cout << "Total: " << cantStocks - cont << " registros.";
    cout<<endl;
    cout<<endl;
}

void alertaSinStock()
{
    ProductoStock aux;
    int cont=0;
    int cantStocks = CantidadRegistrosStock();
    cout << "PRODUCTOS PROXIMOS A AGOTARSE" << endl;
    cout << "----------------------------------" << endl;
    for(int i=0; i<cantStocks; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoStock() &&  aux.getStock()== 0)
        {
            cout<<aux.toString()<<endl;
        }
        else
        {
            cont++;
        }
    }
    cout << "----------------------------------" << endl;
    cout << "Total: " << cantStocks - cont << " registros.";
    cout<<endl;
    cout<<endl;
}

