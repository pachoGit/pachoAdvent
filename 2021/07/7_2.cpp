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

    double suma = 0;
    std::for_each(posiciones.begin(), posiciones.end(), [&] (int &numero)
                                                        {
                                                            suma += numero;
                                                        });
    int promedio = std::floor(suma / posiciones.size());

    int combustible = 0;
    std::for_each(posiciones.begin(), posiciones.end(), [&] (int &numero)
                                                        {
                                                            int distancia = std::abs(numero - promedio);
                                                            int cantidad = (distancia * (distancia + 1)) / 2;
                                                            combustible += cantidad;
                                                        });

    std::cout << combustible << std::endl;

    return 0;
}
