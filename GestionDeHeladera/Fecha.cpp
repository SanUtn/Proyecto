#include <iostream>
#include "Fecha.h"
#include <ctime>

using namespace std;


Fecha::Fecha(int d, int m, int a)
{
    dia=d;
    mes=m;
    anio=a;
}


string Fecha::toString()
{
    string cadena;
    cadena = "Fecha: " + to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
    return cadena;
}


//funcion para crear un objeto con la fecha actual, con la fecha de hoy.
Fecha::Fecha()
{
    time_t rawtime;
    struct tm timeinfo;

    time (&rawtime);
    timeinfo = *(localtime (&rawtime));

    dia = timeinfo.tm_mday;
    mes = timeinfo.tm_mon + 1;
    anio = timeinfo.tm_year + 1900;
}
