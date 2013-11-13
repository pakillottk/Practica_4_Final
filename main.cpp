/* 
 * File:   main.cpp
 * Author: Fasgort
 *
 * Created on 6 de noviembre de 2013, 12:45
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

#include "ListaEnlazadaD.h"
#include "AVL.h"

using namespace std;

void skipline(std::istream &stream) {
    string dummy;
    getline(stream, dummy);
}

struct CodigoPost {
    string zipcode;
    string ziptype;
    string state;
    string loctype;
    string loclat;
    string loclong;
    string location;
    string decom;
    string tax;
    string population;
    string wages;
};

struct StructPost {
    string ciudad;
    ListaEnlazadaD<CodigoPost> codigos;

    bool operator<(const StructPost& cp) const {
        return (ciudad < cp.ciudad);
    }
};

void mostrarCodigoPost(const CodigoPost& cod) {
    cout << "ZIP Code: " << cod.zipcode << endl;
    cout << "ZIP Type: " << cod.ziptype << endl;
    cout << "State: " << cod.state << endl;
    cout << "Loc. Type: " << cod.loctype << endl;
    cout << "Loc. Lat: " << cod.loclat << endl;
    cout << "Loc. Long: " << cod.loclong << endl;
    cout << "Location: " << cod.location << endl;
    cout << "Decom: " << cod.decom << endl;
    cout << "Tax: " << cod.tax << endl;
    cout << "Population: " << cod.population << endl;
    cout << "Wages: " << cod.wages << endl;
}

int main() {

    AVL<StructPost> codigosPostales;
    
    ifstream myfile("free-zipcode-database-Primary.csv");
    if (myfile.is_open()) {

        //Se ignora la primera linea
        skipline(myfile);

        stringstream ss;
        string line, dato;

        do {
            getline(myfile, line);

            // Se lee linea
            // Se averigua la ciudad
            // Se busca si la ciudad(structPost) ya está registrada en el AVL
            // Se crea la ciudad(structPost) si no ha sido creada
            // Se añade el CodigoPost a la ciudad
            // Se continua a la siguiente linea

            // CODIGO INICIAL

            ss.clear();
            ss.str(line);

            getline(ss, dato, ','); //Ignora zip
            getline(ss, dato, ','); //Ignora tipo
            ss.ignore(1); // Ignora el caracter "
            getline(ss, dato, '"'); // Toma el nombre de la ciudad
            ss.str(line); //Limpia el stringstream y vuelve a tomar la linea

            //StructPost begin

            StructPost datosAux;
            datosAux.ciudad = dato;
            StructPost* datos = codigosPostales.insertarNR(datosAux);

            //StructPost end

            //CodigoPost begin

            CodigoPost datos2;
            ss.str(line);

            //Zipcode

            ss.ignore(1);
            getline(ss, datos2.zipcode, '"');
            ss.ignore(1);

            //Ziptype

            ss.ignore(1);
            getline(ss, datos2.ziptype, '"');
            ss.ignore(1);

            //City (ignorar)

            ss.ignore(1);
            getline(ss, dato, '"');
            ss.ignore(1);

            //State

            ss.ignore(1);
            getline(ss, datos2.state, '"');
            ss.ignore(1);

            //LocType

            ss.ignore(1);
            getline(ss, datos2.loctype, '"');
            ss.ignore(1);

            //LocLat

            getline(ss, datos2.loclat, ',');

            //LocLong

            getline(ss, datos2.loclong, ',');

            //Location

            ss.ignore(1);
            getline(ss, datos2.location, '"');
            ss.ignore(1);

            //Decom

            ss.ignore(1);
            getline(ss, datos2.decom, '"');
            ss.ignore(1);

            //Tax

            getline(ss, datos2.tax, ',');

            //Population

            getline(ss, datos2.population, ',');

            //Wages

            getline(ss, datos2.wages);

            //

            datos->codigos.insertarFinal(datos2);

            //CodigoPost end

            // CODIGO FINAL

        } while (myfile.eof() == false);
        myfile.close();
    } else throw LecturaArchivoFallida();

    // MENU BEGIN

    short unsigned eleccion = 0;
    while (eleccion == 0 || eleccion == 1) {
        switch (eleccion) {
            case 0:
                cout << "1: Mostrar datos de ciudad." << endl;
                cout << "Cualquier otro numero para salir." << endl << endl;
                cout << "Eleccion: ";
                cin >> eleccion;
                skipline(cin);
                cout << endl;                
                break;
            case 1:
                StructPost post;
               
                cout << "Inserte nombre de la ciudad: ";
                getline(cin, post.ciudad);
                cout << endl;

                StructPost* encontrado = codigosPostales.busquedaNR(post);
                if (!encontrado) {
                    cout << "No se encontro " << post.ciudad << endl << endl;
                } else {
                    unsigned contador = 1;
                    Iterador<CodigoPost> codIt = encontrado->codigos.iteradorCabecera();

                    while (!codIt.iteradorNulo()) {
                        cout << "Codigo " << contador << ":" << endl;
                        cout << "---------------" << endl;
                        mostrarCodigoPost(codIt.dato());
                        cout << "---------------" << endl << endl;
                        contador++;

                        codIt.siguiente();
                    }
                }
                eleccion = 0;
        }
    }

    //MENU END

    return 0;
}
