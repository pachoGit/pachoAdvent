#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


int main()
{
    //std::vector<std::string> lista = {"ab", "cd"};
    std::string cadena = "ab";
    std::string nuevo = "acb";

    std::sort(nuevo.begin(), nuevo.end());
    std::cout << "Nuevo: " << nuevo << std::endl;
    std::cout << "Cadena: " << cadena << std::endl;

    //auto resultado = std::search(cadena.begin(), cadena.end(), nuevo.begin(), nuevo.end());
    //auto resultado = std::search(nuevo.begin(), nuevo.end(), cadena.begin(), cadena.end());
    auto resultado = std::find(cadena.begin(), cadena.end(), cadena.at(0));
    if (resultado == cadena.end())
        std::cout << "No encontrado" << std::endl;
    else
        std::cout << "Encontrado" << std::endl;

    std::vector<std::pair<int, int>> cuencas = {
        {4, 5}, {6, 6}, {7, 9}
    };
    std::pair<int, int> b = {7, 9};

    auto r = std::find(cuencas.begin(), cuencas.end(), b);
    if (r == cuencas.end())
        std::cout << "NO ENCONTRADO" << std::endl;
    else
        std::cout << "ENCONTRADO" << std::endl;

    return 0;
}



