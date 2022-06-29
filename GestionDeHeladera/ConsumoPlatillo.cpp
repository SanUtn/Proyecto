#include <iostream>
#include <cctype>
#include <iomanip>
#include "rlutil.h"
#include "ConsumoPlatillo.h"
#include "Platillo.h"
#include "ProductoStock.h"
#include "ProductosxPlatillo.h"
#include "FuncionesGlobales.h"
#include "Usuario.h"
using namespace std;

string ConsumoPlatillo::toString()
{
    string cadena;
    cadena = "Platillo: " + mostrarNombrePlatillo(idPlatillo) + " " " " + " Fecha consumo: " + getFechaConsumo().toString();
    return cadena;
}

void ConsumoPlatillo::toList()
{
    rlutil::setColor(rlutil::LIGHTCYAN);
    cout << left;
    cout << "\t";
    cout << setw(25)  << mostrarNombrePlatillo(idPlatillo);
    cout << setw(20) << getFechaConsumo().toString();
    cout << setw(15) << getUsuario() << endl;
    rlutil::setColor(rlutil::BROWN);
}


bool ConsumoPlatillo::LeerDeDisco(int pos)
{
    FILE *p;
    int leyo;
    p=fopen("ConsumosPlatillos.dat", "rb");
    if(p==NULL)
    {
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    fseek(p, pos*sizeof(ConsumoPlatillo),0);
    leyo=fread(this,sizeof(ConsumoPlatillo),1,p);

    fclose(p);

    return leyo;
}

bool ConsumoPlatillo::GrabarEnDisco()
{
    FILE *p;
    p=fopen("ConsumosPlatillos.dat", "ab");
    if(p==NULL)
    {
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    int escribio=fwrite(this, sizeof(ConsumoPlatillo),1,p);
    fclose(p);

    return escribio;
}



//METODO GUARDAR EN DISCO QUE PERMITE GUARDAR UNA MODIFICACION
//HAY QUE PASARLE LA POSICION Y EL MODO LECTURA VA RB+
bool ConsumoPlatillo::ModificarArchivo(int pos)
{
    FILE *p;
    p=fopen("ConsumosPlatillos.dat", "rb+");
    if(p==NULL)
    {
        rlutil::setColor(rlutil::RED);
        cout<<"El archivo no pudo abrirse"<<endl;
        rlutil::setColor(rlutil::BROWN);
        return false;
    }
    fseek(p, pos*sizeof(ConsumoPlatillo),0);
    int escribio=fwrite(this, sizeof(ConsumoPlatillo),1,p);
    fclose(p);

    return escribio;
}


/// Funciones globales para gestionar el consumo de un platillo
//recibe por parametro el dni del usuario que realiza el consumo
bool nuevoConsumoPlatillo(int u)
{
    ConsumoPlatillo reg;
    reg = cargarConsumoPlatillo(u);

    bool ok = reg.GrabarEnDisco();
    if(ok)
    {
        int platillo= reg.getIdPlatillo();
        int usuario = reg.getUsuario();
        if(retirarProductoDelStockDesdePlatillo(platillo))
        {
            ok = retirarProductoExistentePorConsumo(platillo, usuario);
        }
    }
    return ok;
}

int CantidadRegistrosConsumoPlatillo()
{
    FILE *p;
    p=fopen("ConsumosPlatillos.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    size_t bytes;
    int cantidad;

    fseek(p, 0, SEEK_END);
    bytes=ftell(p);

    fclose(p);
    cantidad = bytes/sizeof(ConsumoPlatillo);
    return cantidad;
}

//recibe por parametro el dni del usuario que realiza el consumo
ConsumoPlatillo cargarConsumoPlatillo(int u)
{
    int id;

    cout << "Ingrese el id del Platillo: ";
    cin >> id;

    while( validarNumero() )
    {
        cin >> id;
    }

    cout<<endl;

    //validamos que exista ese platillo
    while(buscarPlatillo(id) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "Platillo inexistente, ingrese otro: ";
        cin >> id;
        while(validarNumero())
        {
            cin >> id;
        }
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    while(validarExistenciaDeProductos(id)== false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "Lo sentimos, no hay stock de productos para cosumir ese platillo o no existe, ingrese otro: ";
        cin >> id;
        while(validarNumero())
        {
            cin >> id;
        }
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    ConsumoPlatillo reg;
    Fecha actual;
    reg.setIdPlatillo(id);
    reg.setFechaConsumo(actual);
    reg.setUsuario(u);
    cout<<endl;
    cout<<endl;
    //system("pause");
    return reg;
}

bool validarExistenciaDeProductos(int idPlatillo)
{
    bool bandera = true;
    int *vProductos;
    int cantReg = CantidadRegistrosProductosxPlatillos();
    vProductos = new int [cantReg];
    if(vProductos==NULL)
    {
        return false;
    }

    if(buscarPlatillo(idPlatillo))
    {
        //llamamos a la funcion para que cargue todos los productos de ese platillo
        buscarProductosXPlatillo(idPlatillo,vProductos,cantReg);

        for(int i=0; i<cantReg; i++)
        {
            //porque algunas posiciones del vector estan vacias, solo va a buscar las que tengan id de productos.

            if(vProductos[i]>0)
            {

                if(consultarStock(vProductos[i]) == 0)
                {
                    bandera = false;
                }
            }
        }
    }
    else
    {
        bandera = false;
    }
    delete vProductos;
    return bandera;
}

void listarConsumosPlatillo()
{
    ConsumoPlatillo aux;
    int cantConsumoPlatillo = CantidadRegistrosConsumoPlatillo();

    if (cantConsumoPlatillo != 0)
    {
        rlutil::setColor(rlutil::MAGENTA);
        cout<<endl;
        cout << left;
        cout << setw(21) << "\t";
        cout << "CONSUMOS PLATILLOS" << endl;
        rlutil::setColor(rlutil::DARKGREY);
        cout << "\t" << "--------------------------------------------------------" << endl;
        cout << left;
        cout << "\t";
        cout << setw(25) << "PLATILLO";
        cout << setw(20) << "FECHA CONSUMO";
        cout << setw(15) << "DNI USUARIO" << endl;
        cout << "\t" << "--------------------------------------------------------" << endl;

        for(int i=0; i<cantConsumoPlatillo; i++)
        {
            aux.LeerDeDisco(i);
            aux.toList();
        }
    }
    else
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "No hay consumos de platillos registrados." << endl;
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
    system("pause");
}

bool sugerenciasXOrientacion()
{
    int orientacion, dni;

    cout << "Ingrese el dni: ";
    cin >> dni;
    while(validarNumero())
    {
        cin >> dni;
    }
    cout<<endl;

    while(validarUsuarioExistente(dni) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "El usuario ingresado no existe en el sistema, ingrese otro DNI:  ";
        cin >> dni;
        while(validarNumero())
        {
            cin >> dni;
        }
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    orientacion = buscarOrientacion(dni);
    buscarPlatillosXOrientacion(orientacion);

      if(nuevoConsumoPlatilloxOrientacion(dni,orientacion))
        {
            return true;
        }

    return false;
}

int buscarOrientacion(int dni)
{
    Usuario aux;
    int cantUsuarios=CantidadRegistrosUsuario();

    for(int i=0; i<cantUsuarios; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getDNI() == dni && aux.getEstadoUsuario()== true)
        {
            return aux.getIdOrientacionAlimentaria();
        }
    }

    return -1;
}

void buscarPlatillosXOrientacion(int orientacion)
{
    Platillo aux;
    int cantPlatillos = CantidadRegistrosPlatillo();

    rlutil::setColor(rlutil::MAGENTA);
    cout<<endl;
    cout << left;
    cout << setw(20) << "\t";
    cout <<  "LISTADO DE PLATILLOS POR ORIENTACION " << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-------------------------------------------------------------------------" << endl;
    cout << left;
    cout << "\t";
    cout << setw(5) << "ID";
    cout << setw(25) << "NOMBRE";
    cout << setw(15) << "FECHA";
    cout << setw(20) << "ORIENTACION A.";
    cout << setw(10) << "CALORIAS"<<endl;
    cout << "\t" << "-------------------------------------------------------------------------" << endl;
    for(int i=0; i<cantPlatillos; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getOrientacionAlimentaria() == orientacion && aux.getEstadoPlatillo() == true)
        {
            aux.toList();
        }
    }
    cout<<endl;
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
}

bool sugerenciasXCalorias()
{
    int calorias;
    int dniusuario;

    cout << "Ingrese el dni: ";
    cin >> dniusuario;
    cout<<endl;

    while(validarNumero())
    {
        cin >> dniusuario;
    }

    while(validarUsuarioExistente(dniusuario) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "El usuario ingresado no existe en el sistema, ingrese otro DNI:  ";
        cin >> dniusuario;
        cout<<endl;

        while(validarNumero())
        {
            cin >> dniusuario;
        }
        rlutil::setColor(rlutil::BROWN);
    }

    cout << "Ingrese las calorias que desea consumir: ";
    cin >> calorias;
    cout<<endl;

     while(validarNumero())
        {
            cin >> calorias;
        }

    while(validarCalorias(calorias) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "No hay platillos con esas calorias, ingrese otro valor:  ";
        cin >> calorias;
         while(validarNumero())
        {
            cin >> calorias;
        }
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    buscarPlatillosXCalorias(calorias);
        if(nuevoConsumoPlatilloxCalorias(dniusuario,calorias))
        {
            return true;
        }
    return false;
}


void buscarPlatillosXCalorias(int calorias)
{
    Platillo aux;
    int cantPlatillos = CantidadRegistrosPlatillo();

    rlutil::setColor(rlutil::MAGENTA);
    cout<<endl;
    cout << left;
    cout << setw(20) << "\t";
    cout <<  "LISTADO DE PLATILLOS POR CALORIAS " << endl;
    rlutil::setColor(rlutil::DARKGREY);
    cout << "\t" << "-------------------------------------------------------------------------" << endl;
    cout << left;
    cout << "\t";
    cout << setw(5) << "ID";
    cout << setw(25) << "NOMBRE";
    cout << setw(15) << "FECHA";
    cout << setw(20) << "ORIENTACION A.";
    cout << setw(10) << "CALORIAS"<<endl;
    cout << "\t" << "-------------------------------------------------------------------------" << endl;

    for(int i=0; i<cantPlatillos; i++)
    {
        aux.LeerDeDisco(i);
        if(aux.getCalorias() <= calorias && aux.getEstadoPlatillo() == true)
        {
            aux.toList();
        }
    }

    cout<<endl;
    cout<<endl;
    cout<<endl;
    rlutil::setColor(rlutil::BROWN);
}


bool validarCalorias(int calorias)
{
    Platillo aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if(aux.getCalorias() == calorias && aux.getEstadoPlatillo() == true)
        {
            return true;
        }
        pos++;
    }
    return false;
}

void menuSugerenciasPlatillos()
{
    int opc;
    int aux;

    while(true)
    {
        system("cls");
        rlutil::locate(52, 5);
        rlutil::setColor(rlutil::GREY);
        cout<<"MENU SUGERENCIAS PLATILLOS"<<endl;
        rlutil::locate(40, 6);
        cout<<"-------------------------------------------------"<<endl;
        rlutil::locate(48, 8);
        rlutil::setColor(rlutil::MAGENTA);
        cout<<"1. SUGERENCIAS POR ORIENTACION"<<endl;
        rlutil::locate(48, 9);
        cout<<"2. SUGERENCIAS POR CALORIAS" <<endl;
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

            cout<<endl;
            if(sugerenciasXOrientacion())
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

            cout<<endl;
            if(sugerenciasXCalorias())
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
        case 0:
            return;
            break;
        }
        cout<<endl;
    }
}

//sugerencias por orientacion
//-------------------------------------------------
bool nuevoConsumoPlatilloxOrientacion(int u, int orientacion)
{
    ConsumoPlatillo reg;
    reg = cargarConsumoPlatilloxOrientacion(u, orientacion);

    bool ok = reg.GrabarEnDisco();
    if(ok)
    {
        int platillo= reg.getIdPlatillo();
        int usuario = reg.getUsuario();
        if(retirarProductoDelStockDesdePlatillo(platillo))
        {
            ok = retirarProductoExistentePorConsumo(platillo, usuario);
        }
    }
    return ok;
}

//recibe por parametro el dni del usuario que realiza el consumo y las calorias elegidas
ConsumoPlatillo cargarConsumoPlatilloxOrientacion(int u, int orientacion)
{
    int id;

    cout << "Ingrese el id del Platillo: ";
    cin >> id;

    while( validarNumero() )
    {
        cin >> id;
    }

    cout<<endl;

    //validamos que sea uno de los platillos sugeridos
    while(validarOrientacionesSugeridas(orientacion,id) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "Platillo no sugerido, ingrese otro: ";
        cin >> id;
        while(validarNumero())
        {
            cin >> id;
        }
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    //validamos que exista ese platillo
    while(buscarPlatillo(id) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "Platillo inexistente, ingrese otro: ";
        cin >> id;
        while(validarNumero())
        {
            cin >> id;
        }
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    while(validarExistenciaDeProductos(id)== false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "Lo sentimos, no hay stock de productos para consumir ese platillo o no existe, ingrese otro: ";
        cin >> id;
        while(validarNumero())
        {
            cin >> id;
        }
            //validamos que sea uno de los platillos sugeridos
            while(validarOrientacionesSugeridas(orientacion,id) == false)
            {
                rlutil::setColor(rlutil::RED);
                cout<<endl;
                cout << "Platillo no sugerido, ingrese otro: ";
                cin >> id;
                while(validarNumero())
                {
                    cin >> id;
                }
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
            }
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    ConsumoPlatillo reg;
    Fecha actual;
    reg.setIdPlatillo(id);
    reg.setFechaConsumo(actual);
    reg.setUsuario(u);
    cout<<endl;
    cout<<endl;
    cout<<endl;
    return reg;
}

bool validarOrientacionesSugeridas(int orientacion, int id)
{
    Platillo aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if(aux.getOrientacionAlimentaria() == orientacion && aux.getEstadoPlatillo() == true && aux.getIdPlatillo() == id)
        {
            return true;
        }
        pos++;
    }
    return false;
}



//sugerencias por calorias
//-------------------------------------------------------------------------
bool nuevoConsumoPlatilloxCalorias(int u, int calorias)
{
    ConsumoPlatillo reg;
    reg = cargarConsumoPlatilloxCalorias(u, calorias);

    bool ok = reg.GrabarEnDisco();
    if(ok)
    {
        int platillo= reg.getIdPlatillo();
        int usuario = reg.getUsuario();
        if(retirarProductoDelStockDesdePlatillo(platillo))
        {
            ok = retirarProductoExistentePorConsumo(platillo, usuario);
        }
    }
    return ok;
}

//recibe por parametro el dni del usuario que realiza el consumo y las calorias elegidas
ConsumoPlatillo cargarConsumoPlatilloxCalorias(int u, int calorias)
{
    int id;

    cout << "Ingrese el id del Platillo: ";
    cin >> id;

    while( validarNumero() )
    {
        cin >> id;
    }

    cout<<endl;

    //validamos que sea uno de los platillos sugeridos
    while(validarCaloriasSugeridas(calorias,id) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "Platillo no sugerido, ingrese otro: ";
        cin >> id;
        while(validarNumero())
        {
            cin >> id;
        }
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    //validamos que exista ese platillo
    while(buscarPlatillo(id) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "Platillo inexistente, ingrese otro: ";
        cin >> id;
        while(validarNumero())
        {
            cin >> id;
        }
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    while(validarExistenciaDeProductos(id)== false)
    {
        rlutil::setColor(rlutil::RED);
        cout<<endl;
        cout << "Lo sentimos, no hay stock de productos para consumir ese platillo o no existe, ingrese otro: ";
        cin >> id;
        while(validarNumero())
        {
            cin >> id;
        }
            //validamos que sea uno de los platillos sugeridos
            while(validarCaloriasSugeridas(calorias,id) == false)
            {
                rlutil::setColor(rlutil::RED);
                cout<<endl;
                cout << "Platillo no sugerido, ingrese otro: ";
                cin >> id;
                while(validarNumero())
                {
                    cin >> id;
                }
                cout<<endl;
                rlutil::setColor(rlutil::BROWN);
            }
        cout<<endl;
        rlutil::setColor(rlutil::BROWN);
    }

    ConsumoPlatillo reg;
    Fecha actual;
    reg.setIdPlatillo(id);
    reg.setFechaConsumo(actual);
    reg.setUsuario(u);
    cout<<endl;
    cout<<endl;
    cout<<endl;
    return reg;
}

bool validarCaloriasSugeridas(int calorias, int id)
{
    Platillo aux;
    int pos = 0;

    while(aux.LeerDeDisco(pos))
    {
        if(aux.getCalorias() <= calorias && aux.getEstadoPlatillo() == true && aux.getIdPlatillo() == id)
        {
            return true;
        }
        pos++;
    }
    return false;
}
