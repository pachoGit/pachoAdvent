#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

void actualizar(std::map<int, unsigned long> &peces)
{
    unsigned long nuevos = peces[0]; // Todos los peces con ID 0 son nuevos
    for (int i = 0; i < 8; ++i)
        peces[i] = peces[i+1];
    peces[8] = nuevos;
    peces[6] += nuevos;
}

int main()
{
    std::ifstream archivo;
    std::string linea;
    std::vector<int> peces;

    archivo.open("e6.txt");
    if (!archivo.is_open())
        return -1;
    std::getline(archivo, linea);
    archivo.close();

    std::transform(linea.begin(), linea.end(), std::back_inserter(peces),
                   [] (unsigned char caracter) -> int
                   {
                       if (caracter != ',')
                           return caracter - '0';
                       else
                           return -1;
                   });

    peces.erase(std::remove_if(peces.begin(), peces.end(), [] (int numero)
                                                          {
                                                              return (numero == -1);
                                                          }), peces.end());

    // ID - cantidad
    std::map<int, unsigned long> npeces = {
        {0, 0},
        {1, 0},
        {2, 0},
        {3, 0},
        {4, 0},
        {5, 0},
        {6, 0},
        {7, 0},
        {8, 0}
    };

    // Iniciamos las cantidades
    for (auto &pez : peces)
        npeces[pez] += 1;

    for (int i = 0; i < 256; ++i)
        actualizar(npeces);

    unsigned long suma = 0;
    for (const auto &[id, cantidad] : npeces)
        suma += cantidad;
    
    std::cout << suma << std::endl;

    return 0;
}
