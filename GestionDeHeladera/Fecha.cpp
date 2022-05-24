#include <iostream>
#include "Fecha.h"

using namespace std;

    void Fecha::Cargar(){
        cout<<"Ingrese el dia: ";
        cin>>dia;
        cout<<"Ingrese el mes: ";
        cin>>mes;
        cout<<"Ingrese el anio: ";
        cin>>anio;
    }

    void Fecha::Mostrar(){
        cout<<"Fecha: ";
        cout<<dia<<"/"<<mes<<"/"<<anio<<endl;
    }
