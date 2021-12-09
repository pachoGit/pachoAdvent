#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

int main()
{
    std::ifstream archivo;
    std::string linea;
    std::vector<std::string> reporte;

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

    std::array<std::array<int, 2>, 12> result_nbits = { 0 };

    for (std::string &numero : reporte)
    {
        for (int i = 0; i < 12; ++i)
        {
            if (numero.at(i) == '1')
                result_nbits.at(i).at(0) += 1;
            if (numero.at(i) == '0')
                result_nbits.at(i).at(1) += 1;
        }
    }

    /*
    for (auto &nbits : result_nbits)
        std::cout << "Unos: " << nbits.at(0) << " Ceros: " << nbits.at(1) << std::endl;
    return 0;
    */

    std::array<std::string, 2> tasas = {"", ""};

    for (auto &nbits : result_nbits)
    {
        if (nbits.at(0) > nbits.at(1))
        {
            tasas.at(0).push_back('1');
            tasas.at(1).push_back('0');
        }
        else
        {
            tasas.at(0).push_back('0');
            tasas.at(1).push_back('1');
        }
    }    

    int resultado = std::stoi(tasas.at(0), nullptr, 2) * std::stoi(tasas.at(1), nullptr, 2);
    std::cout << resultado << std::endl;

    return 0;
}
