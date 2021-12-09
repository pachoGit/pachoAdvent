#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include "separar.hpp"

struct Entrada
{
    std::vector<std::string> patrones;
    std::vector<std::string> salidas;
};

void ver_entrada(Entrada &entrada)
{
    std::cout << "Patrones: ";
    for (auto &patron : entrada.patrones)
        std::cout << patron << " ";
    std::cout << std::endl;
    std::cout << "Valores: ";
    for (auto &valor : entrada.salidas)
        std::cout << valor << " ";
    std::cout << std::endl;
    
}

void nueva_entrada(std::vector<Entrada> &entradas, std::string linea)
{
    Entrada entrada;
    int pos_barra = linea.find('|');
    entrada.patrones = separar_car(linea.substr(0, pos_barra), ' ');
    entrada.salidas = separar_car(linea.substr(pos_barra+2), ' ');
    entradas.push_back(entrada);
}

int main()
{
    std::ifstream archivo;
    std::string linea;
    std::vector<Entrada> entradas;

    archivo.open("e8.txt");

    while (!archivo.eof())
    {
        std::getline(archivo, linea);
        if (linea.size() > 0)
            nueva_entrada(entradas, linea);
    }
    archivo.close();

    int cantidad = 0;
    for (auto &entrada : entradas)
    {
        for (auto &salida : entrada.salidas)
        {
            switch (salida.size())
            {
                case 2:
                case 3:
                case 4:
                case 7:
                    cantidad++;
                    break;
            }
        }
    }

    std::cout << cantidad << std::endl;

    return 0;
}



