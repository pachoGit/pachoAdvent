#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int retVentana(std::vector<int>::iterator indice)
{
    int suma = 0;
    for (int i = 0; i < 3; ++i)
        suma += *(indice + i);
    return suma;
}

int main()
{
    int nveces = 0;
    std::ifstream archivo;
    std::string linea;
    std::vector<int> profundidades;

    archivo.open("e1.txt");
    if (!archivo.is_open())
        return -1;
    
    while (!archivo.eof())
    {
        std::getline(archivo, linea);
        if (linea.length() != 0)
            profundidades.push_back(std::stoi(linea));
    }

    for (auto i = profundidades.begin(); i != profundidades.end() - 2; ++i)
    {
        int sant = retVentana(i);
        int ssig = retVentana(i+1);
        if (ssig > sant)
            nveces++;
    }

    std::cout << nveces << std::endl;
    archivo.close();

    return 0;
}
