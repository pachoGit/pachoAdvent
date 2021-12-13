#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>

void ver_cueva(std::map<std::string, std::vector<std::string>> &mapa, std::string cueva)
{
    std::cout << "Cueva: " << cueva << " --> ";
    for (auto &camino : mapa[cueva])
        std::cout << camino << " ";
    std::cout << std::endl;
}

void recursivo(std::map<std::string, std::vector<std::string>> &mapa, std::vector<std::string> &cuevas)
{
    for (auto &cueva : cuevas)
    {
        if (cueva == "end" || cueva == "start")
        {
            std::cout << cueva << std::endl;
            return;
        }
        std::cout << cueva << " ";
        recursivo(mapa, mapa[cueva]);
    }
}

int main()
{
    std::ifstream archivo;
    std::string linea;
    std::map<std::string, std::vector<std::string>> mapa;

    archivo.open("e12.txt");
    while (!archivo.eof())
    {
        std::getline(archivo, linea);
        if (linea.size() > 0)
            mapa[linea.substr(0, linea.find('-'))].push_back(linea.substr(linea.find('-') + 1));
    }
    archivo.close();
    
    for (auto &cueva : mapa)
        ver_cueva(mapa, cueva.first);
    
    recursivo(mapa, mapa["start"]);

    return 0;
}




