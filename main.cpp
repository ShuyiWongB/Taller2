#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "omp.h"

using namespace std;

/**
 * Función que muestra los participantes del grupo
 */
void participantes();

int main()
{
    /**
     * 
     * linea se usará para quitar los titulos del primer archivo
     * linea2 se usará para quitar los titulos del segundo archivo
     * barcode guardará el codigo de barras del primer archivo
     * name guardará el nombre comercial de cada producto
     * volume guardará el volumen del envase de cada producto
     * barcode2 guardará el codigo de barras del segundo archivo
     * quantity guardará la cantidad de cada reciclaje
     * created guardara la fecha que se hizo el reciclaje
     * 
     */ 
    string linea,linea2,barcode,name,volume,barcode2,quantity,created;
    /**
     * 
     * vectorbarcode es un vector donde se guardarán los codigos de barra del primer archivo
     * vectorname es un vector donde se guardarán los nombres de los productos
     * vectorvolume es un vector donde se guardarán los volumenes de los productos
     * vectorbarcode2 es un vector donde se guardarán los codigos de barra del segundo archivo
     * vectorquantity es un vector donde se guardarán las cantidades del reciclaje
     * vectorcreated es un vector donde se guardaran las fechas de reciclaje
     * 
     */
    vector<string> vectorbarcode,vectorname,vectorvolume,vectorbarcode2,vectorquantity,vectorcreated;
    /**
     * 
     * vectorquantityint Vector donde alojaremos las cantidades en formato doble
     * vectorcount es un vector que guardara las cantidades totales de reciclaje
     * 
     */
    vector<int> vectorquantityint, vectorcount;
    /**
     * 
     * auxiliar es donde guarda el valor del vector de manera auxiliar para la sumatoria
     * 
     */
    int auxiliar;
     
    // **
    // A R C H I V O E Q U I P O S

    ifstream archivo, archivo2;
    archivo.open("trx_taller.csv");
    archivo2.open("products_taller.csv");

#pragma omp parallel
    {
#pragma omp single 
        {
    getline(archivo,linea); // Q U I T A T Í T U L O S
    getline(archivo2,linea2);
    
#pragma omp task
            {
//GUARDA TODOS LOS DATOS EN DIFERENTES VECTORES
    while(archivo.good())
        {
        getline(archivo, barcode2, ';');
        vectorbarcode2.push_back(barcode2);

        getline(archivo, quantity, ';');
        vectorquantity.push_back(quantity);

        getline(archivo, created, '\n');
        vectorcreated.push_back(created);
        }

        while(archivo2.good())
        {
        getline(archivo2, barcode, ';');
        vectorbarcode.push_back(barcode);

        getline(archivo2, name, ';');
        vectorname.push_back(name);

        getline(archivo2, volume, '\n');
        vectorvolume.push_back(volume);
        }
//TRANSFORMA LOS VALORES STRING DE QUANTITY A INT PARA SUMAR
    for (int a = 0; a < vectorquantity.size(); a++){
        string Cant = vectorquantity[a].substr(1,vectorquantity[a].length());
        int Cantidad = atoi(Cant.c_str());
        vectorquantityint.push_back(Cantidad);
    }
    
    // C R E A A R C H I V O R E S U M E N

    ofstream archivoFixture("resumen.csv");

    archivoFixture << "Barcode;";
    archivoFixture << "Name;";
    archivoFixture << "Volume;";
    archivoFixture << "Count\n";

#pragma omp critical
//SUMA LAS CANTIDADES Y LAS GUARDA EN UN NUEVO VECTOR INDEXADO A BARCODE
    for (int l=0; l<vectorbarcode.size(); l++){
        for (int h=0; h<vectorbarcode2.size(); h++){
            if (vectorbarcode[l] == vectorbarcode2[h]){
                auxiliar = auxiliar + vectorquantityint[h];
            }
        }
        vectorcount.push_back(auxiliar);
        auxiliar = 0;
    }
//GUARDA LOS DATOS EN UN NUEVO EXCEL
    for(int i=0;i<vectorbarcode.size();i++){
        archivoFixture << vectorbarcode[i];
        archivoFixture << ";"+vectorname[i];
        archivoFixture << ";"+vectorvolume[i] + ";";
        archivoFixture << vectorcount[i] << endl;
    }

            }
        }
    }

    return 0;
}

void participantes() {
    std::cout << std::endl << "=== Tarea ===" << std::endl;
    std::cout << std::endl << "Shu-yi Wong" << std::endl; 
}
