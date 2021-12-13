#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<int> separar(std::string &cadena, char delimitador)
{
    std::vector<int> resultado;
    std::stringstream cad(cadena);
    std::string elemento;

    while (std::getline(cad, elemento, delimitador))
        resultado.push_back(std::stoi(elemento));

    return resultado;
}

int main()
{
    std::ifstream archivo;
    std::string linea;
    std::vector<int> posiciones;

    archivo.open("e7.txt");
    if (!archivo.is_open())
        return -1;
    std::getline(archivo, linea);
    archivo.close();

    posiciones = separar(linea, ',');

    std::sort(posiciones.begin(), posiciones.end());

    auto calc_mediana = [&] () -> int
                       {
                           int nelemntos = posiciones.size();
                           if (nelemntos % 2 == 1)
                           {
                               return posiciones.at((nelemntos + 1) / 2);
                           }
                           else
                           {
                               int posicion = nelemntos / 2;
                               int n1 = posiciones.at(posicion);
                               int n2 = posiciones.at(posicion - 1);
                               return (int) ((n1 + n2) / 2);
                           }
                       };

    int mediana = calc_mediana();

    int suma = 0;
    std::for_each(posiciones.begin(), posiciones.end(), [&] (int &numero)
                                                        {
                                                            suma += std::abs(numero - mediana);
                                                        });


    std::cout << "Mediana: " << mediana << std::endl;
    std::cout << suma << std::endl;

    return 0;
}
