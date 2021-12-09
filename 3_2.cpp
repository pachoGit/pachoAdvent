#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

std::array<int, 2> contar(std::vector<std::string> &reporte, int indice)
{
    std::array<int, 2> resultado = {0, 0};
    for (std::string &numero : reporte)
    {
        if (numero.at(indice) == '1')
            resultado.at(0) += 1;
        if (numero.at(indice) == '0')
            resultado.at(1) += 1;
    }
    return resultado;
}

int main()
{
    std::ifstream archivo;
    std::string linea;
    std::vector<std::string> reporte;
    std::vector<std::string> reporte_copia;

    archivo.open("e3.txt");
    if (!archivo.is_open())
        return -1;
    
    while (!archivo.eof())
    {
        std::getline(archivo, linea);
        if (linea.length() != 0)
            reporte.push_back(linea);
    }
    archivo.close();

    std::array<int, 2> nbits;
    std::copy(reporte.begin(), reporte.end(), std::back_inserter(reporte_copia));

    for (int i = 0; i < reporte.at(0).size() && reporte.size() > 1; ++i)
    {
        nbits = contar(reporte, i);
        if (nbits.at(0) >= nbits.at(1)) // Hay mas valores de un bit
        {
            //std::cout << "Eliminando los que tienen 0 en: " << i << std::endl;
            reporte.erase(std::remove_if(reporte.begin(), reporte.end(), [&] (std::string &numero)
                                                                         {
                                                                             return (numero.at(i) == '0');
                                                                         }), reporte.end());
        }
        else
        {
            //std::cout << "Eliminando los que tienen 1 en: " << i << std::endl;
            reporte.erase(std::remove_if(reporte.begin(), reporte.end(), [&] (std::string &numero)
                                                                         {
                                                                             return (numero.at(i) == '1');
                                                                         }), reporte.end());
        }
        /*
          for (auto &numero : reporte)
          std::cout << numero << std::endl;
        */
    }

    // Para sacar con los de menor numero de bits
    for (int i = 0; i < reporte_copia.at(0).size() && reporte_copia.size() > 1; ++i)
    {
        nbits = contar(reporte_copia, i);
        if (nbits.at(0) < nbits.at(1)) // Hay mas valores de un bit
        {
            //std::cout << "Eliminando los que tienen 0 en: " << i << std::endl;
            reporte_copia.erase(std::remove_if(reporte_copia.begin(), reporte_copia.end(), [&] (std::string &numero)
                                                                                           {
                                                                                               return (numero.at(i) == '0');
                                                                                           }), reporte_copia.end());
        }
        else
        {
            //std::cout << "Eliminando los que tienen 1 en: " << i << std::endl;
            reporte_copia.erase(std::remove_if(reporte_copia.begin(), reporte_copia.end(), [&] (std::string &numero)
                                                                                           {
                                                                                               return (numero.at(i) == '1');
                                                                                           }), reporte_copia.end());
        }
        /*
          for (auto &numero : reporte)
          std::cout << numero << std::endl;
        */
    }


    for (auto &numero : reporte)
        std::cout << "Numero Final: " << numero << std::endl;
    for (auto &numero : reporte_copia)
        std::cout << "Numero Final: " << numero << std::endl;

    int resultado = std::stoi(reporte.at(0), nullptr, 2) * std::stoi(reporte_copia.at(0), nullptr, 2);
    std::cout << resultado << std::endl;

    
    return 0;
}
