#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

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
             void Cargar();
             void Mostrar();



    };













#endif // FECHA_H_INCLUDED
