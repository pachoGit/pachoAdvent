#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <map>

#include "../separar.hpp"

typedef char IdLed;

std::map<int, std::string> numeros =
{
    {0, "abcefg"},
    {1, "cf"},
    {2, "acdeg"},
    {3, "acdfg"},
    {4, "bcdf"},
    {5, "abdfg"},
    {6, "abdefg"},
    {7, "acf"},
    {8, "abcdefg"},
    {9, "abcdfg"}
};

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
    std::cout << "Salidas: ";
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

std::vector<std::string> ret_unicos(std::vector<std::string> &patrones)
{
    std::vector<std::string> unicos;
    for (auto &patron : patrones)
    {
        switch (patron.size())
        {
            case 2: // Es el numero 1
            case 3: // Es el numero 7
            case 4: // Es el numero cuatro
            case 7: // Es el numero 8
                unicos.push_back(patron);
                break;
        }
    }
    return unicos;
}

void generar(std::map<IdLed, std::vector<IdLed>> &leds, std::vector<std::string> &unicos)
{
    auto esta_en = [&] (std::string &cadena, char caracter) -> bool
                   {
                       return (std::find(cadena.begin(), cadena.end(), caracter) != cadena.end());
                   };

    // Trabajamos con el 1
    // Los posibles valores en los segmentos c y f
    for (auto &caracter : unicos.at(0))
    {
        leds['c'].push_back(caracter);
        leds['f'].push_back(caracter);
    }

    // Trabajamos con el 7
    // Hallamos el valor del segmento 'a'
    for (auto &caracter : unicos.at(1))
    {
        if (esta_en(unicos.at(0), caracter) == false)
        {
            leds['a'].push_back(caracter);
            break;
        }
    }


    for (auto &led : leds)
    {
        std::cout << led.first << " -> ";
        for (auto &posible : led.second)
            std::cout << posible << " ";
        std::cout << std::endl;
    }
    
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

    std::vector<IdLed> i;
    std::map<IdLed, std::vector<IdLed>> leds = {
        {'a', i},
        {'b', i},
        {'c', i},
        {'d', i},
        {'e', i},
        {'f', i}
    };

    int cantidad = 0;
    for (auto &entrada : entradas)
    {
        std::sort(entrada.patrones.begin(), entrada.patrones.end(), [] (std::string a, std::string b)
                                                                    {
                                                                        return (a.size() < b.size());
                                                                    });
        ver_entrada(entrada);
        
        std::vector<std::string> unicos = ret_unicos(entrada.patrones); // 1, 4, 7, 8
        generar(leds, unicos);

        for (auto &unico : unicos)
            std::cout << unico << std::endl;
        
        break;
        for (auto &led : leds)
            led.second.clear();
    }
    
    /*
    for (auto &led : leds)
    {
        std::sort(led.second.begin(), led.second.end());
        std::cout << led.first <<  " -> ";
        for (auto &posible : led.second)
            std::cout << posible << " ";
        std::cout << std::endl;
    }
    */

    return 0;
}



