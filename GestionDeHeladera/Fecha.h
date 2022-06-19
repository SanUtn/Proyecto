#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED
#include<cstdlib>
#include<cstring>
#include <string>
using namespace std;

    class Fecha{

    private:
            int dia;
            int mes;
            int anio;

    public:
            //getters
            int getDia(){return dia;}
            int getMes(){return mes;}
            int getAnio(){return anio;}

            //setters
            void setDia(int d){dia=d;}
            void setMes(int m){mes=m;}
            void setAnio(int a){anio=a;}

            //metodos
             Fecha(int d, int m, int a);
             Fecha();
             Fecha(int d);
             string toString();

    };













#endif // FECHA_H_INCLUDED
