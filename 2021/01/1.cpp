#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <chrono>

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

    auto inicio = std::chrono::steady_clock::now();
    for (auto i = profundidades.begin() + 1; i != profundidades.end(); ++i)
    {
        if (*i > *(i-1))
            nveces++;
    }
    auto fin = std::chrono::steady_clock::now();

    std::chrono::duration<double>  duracion = fin - inicio;
    std::cout << "Tiempo de calculo: " << duracion.count() << "s" << std::endl;

    std::cout << nveces << std::endl;
    archivo.close();

    return 0;
}
