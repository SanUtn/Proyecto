#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include "rlutil.h"
#include "FuncionesGlobales.h"

using namespace std;

bool validarNumero()
{
    if( std::cin.fail() )
    {
        rlutil::setColor(rlutil::RED);
        std::cout << "Error, ingrese un ID valido: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<int>::max(),'\n');
        rlutil::setColor(rlutil::BROWN);
        return true;
    }
    return false;
}

void menuConsumos()
{
    int opc;
    while(true)
    {
        system("cls");
        rlutil::locate(54, 5);
        rlutil::setColor(rlutil::CYAN);
        cout<<"MENU CONSUMOS"<<endl;
        rlutil::locate(40, 6);
        cout<<"-------------------------------------------"<<endl;
        rlutil::setColor(rlutil::LIGHTCYAN);
        rlutil::locate(48,8);
        cout<<"1. AGREGAR CONSUMO PRODUCTO "<<endl;
        rlutil::locate(48,9);
        cout<<"2. LISTAR CONSUMO PRODUCTOS"<<endl;
        rlutil::locate(48,10);
        cout<<"3. AGREGAR CONSUMO PLATILLO "<<endl;
        rlutil::locate(48,11);
        cout<<"4. LISTAR CONSUMO PLATILLOS"<<endl;
        rlutil::locate(48,12);
        cout<<"---------------------------"<<endl;
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
            if(nuevoConsumoProducto())
            {
                rlutil::setColor(rlutil::GREEN);
                cout<<endl;
                cout<<"CONSUMO AGREGADO";
                cout<<endl;
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
                system("pause");
            }
            else
            {
                rlutil::setColor(rlutil::RED);
                cout<<endl;
                cout<<"NO SE PUDO AGREGAR EL CONSUMO";
                cout<<endl;
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
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

int CantidadProductosxPlatillo(int idplatillo)
{
    ProductosxPlatillo reg;
    int pos = 0;
    int cant = 0;

    while(reg.LeerDeDisco(pos))
    {
        if(reg.getIdPlatillo() == idplatillo)
        {
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
        if(reg.getIdProducto() == idproducto && reg.getEstadoStock() == true)
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
            //cantidad de productos del platillo.
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
        rlutil::locate(52, 5);
        rlutil::setColor(rlutil::CYAN);
        cout<<"MENU REPORTES"<<endl;
        rlutil::locate(40, 6);
        cout<<"---------------------------------------"<<endl;
        rlutil::setColor(rlutil::LIGHTCYAN);
        rlutil::locate(48,8);
        cout<<"1. CONSUMOS ANUALES "<<endl;
        rlutil::locate(48,9);
        cout<<"2. CONSUMOS MENSUALES"<<endl;
        rlutil::locate(48,10);
        cout<<"3. ALERTA DE STOCK"<<endl;
        rlutil::locate(48,11);
        cout<<"4. ALERTA SIN STOCK"<<endl;
        rlutil::locate(48,12);
        cout<<"5. PRODUCTOS A VENCER"<<endl;
        rlutil::locate(48,13);
        cout<<"6. PRODUCTOS VENCIDOS"<<endl;
        rlutil::locate(48,14);
        cout<<"----------------------"<<endl;
        rlutil::locate(48,15);
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        rlutil::locate(48,18);
        rlutil::setColor(rlutil::DARKGREY);
        cout<<"OPCION: ";
        cin>>opc;

        rlutil::setColor(rlutil::BROWN);
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
            alertaStock();
            system("pause");
            break;
        case 4:
            alertaSinStock();
            system("pause");
            break;
        case 5:
            alertaDeProductosAVencer();
            system("pause");
            break;
        case 6:
            alertaDeProductosVencidos();
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
        rlutil::locate(52, 5);
        rlutil::setColor(rlutil::GREY);
        cout<<"MENU CONSUMOS ANUALES"<<endl;
        rlutil::locate(40, 6);
        cout<<"---------------------------------------------"<<endl;
        rlutil::locate(48, 8);
        rlutil::setColor(rlutil::MAGENTA);
        cout<<"1. CONSUMOS PLATILLOS "<<endl;
        rlutil::locate(48, 9);
        cout<<"2. CONSUMOS PRODUCTOS"<<endl;
        rlutil::locate(48, 10);
        cout<<"-------------------"<<endl;
        rlutil::locate(48, 11);
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        rlutil::locate(48, 14);
        rlutil::setColor(rlutil::GREY);
        cout<<"OPCION: ";
        cin>>opc;
        rlutil::setColor(rlutil::BROWN);

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
        rlutil::locate(52, 5);
        rlutil::setColor(rlutil::GREY);
        cout<<"MENU CONSUMOS MENSUALES"<<endl;
        rlutil::locate(40, 6);
        cout<<"---------------------------------------------"<<endl;
        rlutil::setColor(rlutil::MAGENTA);
        rlutil::locate(48, 8);
        cout<<"1. CONSUMOS PLATILLOS "<<endl;
        rlutil::locate(48, 9);
        cout<<"2. CONSUMOS PRODUCTOS"<<endl;
        rlutil::locate(48, 10);
        cout<<"-------------------"<<endl;
        rlutil::locate(48, 11);
        cout<<"0. SALIR"<<endl;
        cout<<endl;

        rlutil::locate(48, 14);
        rlutil::setColor(rlutil::GREY);
        cout<<"OPCION: ";
        cin>>opc;
        rlutil::setColor(rlutil::BROWN);

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

//cuando se elimina un producto debe eliminarse también el platillo y sus recetas
void eliminarPlatillos(int idproducto)
{
    ProductosxPlatillo reg;

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

//recibe un platillo chequea si existe en recetas y setea su estado a false.
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

void modificarVencimientoProducto(int idproducto, Fecha fecha)
{
    Producto reg;
    int pos = 0;

    while(reg.LeerDeDisco(pos))
    {
        if(reg.getIdProducto() == idproducto)
        {
            reg.setFechaVencimiento(fecha);
            reg.ModificarArchivo(pos);
        }
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
            if(bandera==true)
            {
                rlutil::setColor(rlutil::MAGENTA);
                cout<<endl;
                cout << left;
                cout << setw(16) << "\t";
                cout << "CONSUMOS ANUALES DE PLATILLOS" << endl;
                rlutil::setColor(rlutil::DARKGREY);
                cout << "\t" << "--------------------------------------------------------" << endl;
                cout << left;
                cout << "\t";
                cout << setw(25) << "PLATILLO";
                cout << setw(20) << "FECHA CONSUMO";
                cout << setw(15) << "DNI USUARIO" << endl;
                cout << "\t" << "--------------------------------------------------------" << endl;
                bandera = false;
                rlutil::setColor(rlutil::BROWN);
            }
            reg.toList();
        }
        else
        {
            rlutil::setColor(rlutil::RED);
            cout<<endl;
            cout<<"No existen consumos, ingrese otro anio o 0 para salir: ";
            cin>>opc;
            cout<<endl;
            rlutil::setColor(rlutil::BROWN);
            if(opc==0)
            {
                return;
            }
            else
            {
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
            if(bandera==true)
            {
                rlutil::setColor(rlutil::MAGENTA);
                cout << endl;
                cout << left;
                cout << setw(15) << "\t";
                cout << "CONSUMOS MENSUALES DE PLATILLOS" << endl;
                rlutil::setColor(rlutil::DARKGREY);
                cout <<  "\t" << "--------------------------------------------------------" << endl;
                cout << left;
                cout << "\t";
                cout << setw(25) << "PLATILLO";
                cout << setw(20) << "FECHA CONSUMO";
                cout << setw(15) << "DNI USUARIO" << endl;
                cout <<  "\t" << "--------------------------------------------------------" << endl;
                bandera = false;
                rlutil::setColor(rlutil::BROWN);
            }
            reg.toList();
        }
        else
        {
            rlutil::setColor(rlutil::RED);
            cout<<endl;
            cout<<"No existen consumos, ingrese otro MES o 0 para salir: ";
            cin>>opc;
            cout<<endl;
            rlutil::setColor(rlutil::BROWN);
            if(opc==0)
            {
                return;
            }
            else
            {
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
            if(bandera==true)
            {
                rlutil::setColor(rlutil::MAGENTA);
                cout<<endl;
                cout << left;
                cout << setw(3) << "\t";
                cout << "CONSUMOS ANUALES DE PRODUCTOS" << endl;
                rlutil::setColor(rlutil::DARKGREY);
                cout << "\t" << "---------------------------------" << endl;
                cout << left;
                cout << "\t";
                cout << setw(20) << "PRODUCTO";
                cout << setw(20) << "FECHA CONSUMO" << endl;
                cout << "\t" << "---------------------------------" << endl;
                bandera = false;
                rlutil::setColor(rlutil::BROWN);
            }
            reg.toList();
        }
        else
        {
            rlutil::setColor(rlutil::RED);
            cout<<endl;
            cout<<"No existen consumos, ingrese otro anio o 0 para salir: ";
            cin>>opc;
            cout<<endl;
            rlutil::setColor(rlutil::BROWN);
            if(opc==0)
            {
                return;
            }
            else
            {
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
            if(bandera==true)
            {
                rlutil::setColor(rlutil::MAGENTA);
                cout << endl;
                cout << left;
                cout << setw(2) << "\t";
                cout << "CONSUMOS MENSUALES DE PRODUCTOS" << endl;
                rlutil::setColor(rlutil::DARKGREY);
                cout << "\t" << "---------------------------------" << endl;
                cout << left;
                cout << "\t";
                cout << setw(20) << "PRODUCTO";
                cout << setw(20) << "FECHA CONSUMO" << endl;
                cout << "\t" << "---------------------------------" << endl;
                bandera = false;
                rlutil::setColor(rlutil::BROWN);
            }
            reg.toList();
        }
        else
        {
            rlutil::setColor(rlutil::RED);
            cout<<endl;
            cout<<"No existen consumos, ingrese otro MES o 0 para salir: ";
            cin>>opc;
            cout<<endl;
            rlutil::setColor(rlutil::BROWN);
            if(opc==0)
            {
                return;
            }
            else
            {
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

    rlutil::setColor(rlutil::MAGENTA);
    cout << endl;
    cout << left;
    cout << setw(2) << "\t";
    cout << "PRODUCTOS PROXIMOS A AGOTARSE" << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-------------------------------" << endl;
    cout << left;
    cout << "\t";
    cout << setw(25) << "PRODUCTO";
    cout << setw(20) << "STOCK" << endl;
    cout<< "\t" << "-------------------------------" << endl;
    rlutil::setColor(rlutil::BROWN);

    for(int i=0; i<cantStocks; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoStock() &&  aux.getStock()<= 2 && aux.getStock()!= 0 )
        {
            aux.toList();
        }
        else
        {
            cont++;
        }
    }
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-------------------------------"  << endl;
    cout << "\t" << "Total: " << cantStocks - cont << " registros.";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
}

void alertaSinStock()
{
    ProductoStock aux;
    int cont=0;
    int cantStocks = CantidadRegistrosStock();

    rlutil::setColor(rlutil::MAGENTA);
    cout << endl;
    cout << left;
    cout << setw(7) << "\t";
    cout << "PRODUCTOS SIN STOCK" << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "------------------------------"  << endl;
    cout << left;
    cout << "\t";
    cout << setw(25) << "PRODUCTO";
    cout << setw(20) << "STOCK" << endl;
    cout<< "\t" << "------------------------------"  << endl;
    rlutil::setColor(rlutil::BROWN);

    for(int i=0; i<cantStocks; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getEstadoStock() &&  aux.getStock()== 0)
        {
            aux.toList();
        }
        else
        {
            cont++;
        }
    }
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "------------------------------" << endl;
    cout << "\t" << "Total: " << cantStocks - cont << " registros.";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
}

//muestra los que vencen hoy y los que les falta dos dias para vencer
void alertaDeProductosAVencer()
{
    Producto aux;
    Fecha fecha;
    int cont=0;
    int cantReg = CantidadRegistrosProductos();
    int stock;
    bool bandera = false;

    rlutil::setColor(rlutil::MAGENTA);
    cout << endl;
    cout << left;
    cout << setw(3) << "\t";
    cout << "PRODUCTOS PROXIMOS A VENCER" << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-------------------------------" << endl;
    cout << left;
    cout << "\t";
    cout << setw(20) << "PRODUCTO";
    cout << setw(20) << "VENCIMIENTO" << endl;
    cout << "\t" << "-------------------------------"  << endl;
    rlutil::setColor(rlutil::BROWN);

    for(int i=0; i<cantReg; i++)
    {
        if(aux.LeerDeDisco(i))
        {
            if(aux.getEstadoProducto() == true)
            {
                stock = buscarStockDeProducto(aux.getIdProducto());

                if(stock > 0)
                {
                    if(aux.getFechaVencimiento().getAnio() == fecha.getAnio())
                    {
                        if(aux.getFechaVencimiento().getMes() == fecha.getMes())
                        {
                            int dif = aux.getFechaVencimiento().getDia() - fecha.getDia();
                            if(dif <= 2 && dif >= 0)
                            {
                                rlutil::setColor(rlutil::LIGHTCYAN);
                                cout << left;
                                cout << "\t";
                                cout << setw(20) << aux.getNombreProducto();
                                cout << setw(20) << aux.getFechaVencimiento().toString() << endl;
                                cont++;
                                bandera = true;
                                rlutil::setColor(rlutil::BROWN);
                            }
                        }
                        else if(aux.getFechaVencimiento().getMes() == fecha.getMes() + 1)
                        {
                            int dif2 = fecha.getDia() - aux.getFechaVencimiento().getDia();

                            if(dif2 == fecha.getDia()- 2 || dif2 == fecha.getDia()- 1)
                            {
                                rlutil::setColor(rlutil::LIGHTCYAN);
                                cout << left;
                                cout << "\t";
                                cout << setw(20) << aux.getNombreProducto();
                                cout << setw(20) << aux.getFechaVencimiento().toString() << endl;
                                cont++;
                                bandera = true;
                                rlutil::setColor(rlutil::BROWN);
                            }
                        }
                    }

                }
            }
        }
    }

    if(bandera)
    {
        rlutil::setColor(rlutil::DARKGREY);
        cout << "\t" << "-------------------------------"  << endl;
        cout << "\t" << "Total: " << cont << " Productos.";
        rlutil::setColor(rlutil::BROWN);
    }
    else
    {
        rlutil::setColor(rlutil::RED);
        system("cls");
        cout << endl;
        cout << "No hay productos proximos a vencerse." << endl;
        cout << endl;
        rlutil::setColor(rlutil::BROWN);
    }

    cout<<endl;
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
}

void alertaDeProductosVencidos()
{
    Producto aux;
    Fecha fecha;
    int cont=0;
    int cantReg = CantidadRegistrosProductos();
    int stock;
    bool bandera = false;

    rlutil::setColor(rlutil::MAGENTA);
    cout << endl;
    cout << left;
    cout << setw(8) << "\t";
    cout << "PRODUCTOS VENCIDOS" << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-------------------------------" << endl;
    cout << left;
    cout << "\t";
    cout << setw(20) << "PRODUCTO";
    cout << setw(20) << "VENCIMIENTO" << endl;
    cout << "\t" << "-------------------------------" << endl;
    rlutil::setColor(rlutil::BROWN);

    for(int i=0; i<cantReg; i++)
    {
        if(aux.LeerDeDisco(i))
        {
            if(aux.getEstadoProducto() == true)
            {
                stock = buscarStockDeProducto(aux.getIdProducto());

                if(stock > 0)
                {
                    int difAnio = fecha.getAnio() - aux.getFechaVencimiento().getAnio();
                    int difMes =  fecha.getMes() - aux.getFechaVencimiento().getMes();
                    int difDia =  fecha.getDia() - aux.getFechaVencimiento().getDia() ;

                    if(difAnio == 0)
                    {
                        if(difMes == 0)
                        {
                            //significa que el producto ya vencio
                            if(difDia > 0)
                            {
                                rlutil::setColor(rlutil::LIGHTCYAN);
                                cout << left;
                                cout << "\t";
                                cout << setw(20) << aux.getNombreProducto();
                                cout << setw(20) << aux.getFechaVencimiento().toString() << endl;
                                cont++;
                                bandera = true;
                                rlutil::setColor(rlutil::BROWN);
                            }
                        //significa que el producto ya vencio
                        }else if(difMes > 0){
                            rlutil::setColor(rlutil::LIGHTCYAN);
                            cout << left;
                            cout << "\t";
                            cout << setw(20) << aux.getNombreProducto();
                            cout << setw(20) << aux.getFechaVencimiento().toString() << endl;
                            cont++;
                            bandera = true;
                            rlutil::setColor(rlutil::BROWN);
                        }//significa que el producto ya vencio
                        }else if (difAnio > 0){
                                rlutil::setColor(rlutil::LIGHTCYAN);
                                cout << left;
                                cout << "\t";
                                cout << setw(20) << aux.getNombreProducto();
                                cout << setw(20) << aux.getFechaVencimiento().toString() << endl;
                                cont++;
                                bandera = true;
                                rlutil::setColor(rlutil::BROWN);
                            }
                        }
                    }
                }
            }
    if(bandera)
    {
        rlutil::setColor(rlutil::DARKGREY);
        cout << "\t" << "-------------------------------"<< endl;
        cout << "\t" << "Total: " << cont << " Productos.";
        rlutil::setColor(rlutil::BROWN);
    }
    else
    {
        rlutil::setColor(rlutil::RED);
        system("cls");
        cout<<endl;
        cout << "No hay productos vencidos." << endl;
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    cout<<endl;
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
}



