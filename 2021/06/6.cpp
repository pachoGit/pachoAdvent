#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void actualizar(std::vector<int> &peces)
{
    int nuevos = 0;
    for (auto &pez : peces)
    {
        pez--;
        if (pez <= -1)
        {
            pez = 6;
            nuevos++;
        }
    }

    for (int i = 0; i < nuevos; ++i)
        peces.push_back(8);
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

    for (int i = 1; i <= 80; ++i)
        actualizar(peces);

    std::cout << peces.size() << std::endl;

    return 0;
}
