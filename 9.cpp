#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

int main()
{
    std::ifstream archivo;
    std::string linea;
    int nfila = 0;
    int ncolumna = 0;
    
    archivo.open("e9.txt");
    std::map<std::pair<int, int>, int> mapa;

    while (!archivo.eof())
    {
        std::getline(archivo, linea);
        if (linea.length() != 0)
        {
            for (auto &digito : linea)
            {
                std::pair<int, int> posicion = std::make_pair(nfila, ncolumna);
                mapa[posicion] = digito - '0';
                //std::cout << "Guardando la posicion: "  << nfila << " " << ncolumna << " -> " << mapa[posicion] << std::endl;
                ncolumna++;
            }
        }
        nfila++;
        ncolumna = 0;
    }
    archivo.close();

    auto ret_adys = [&] (std::pair<int, int> posicion) -> std::vector<int>
                    {
                        std::vector<int> adys;
                        if (mapa.find(std::make_pair(posicion.first+1, posicion.second)) != mapa.end())
                            adys.push_back(mapa[std::make_pair(posicion.first+1, posicion.second)]);
                        if (mapa.find(std::make_pair(posicion.first-1, posicion.second)) != mapa.end())
                            adys.push_back(mapa[std::make_pair(posicion.first-1, posicion.second)]);
                        if (mapa.find(std::make_pair(posicion.first, posicion.second+1)) != mapa.end())
                            adys.push_back(mapa[std::make_pair(posicion.first, posicion.second+1)]);
                        if (mapa.find(std::make_pair(posicion.first, posicion.second-1)) != mapa.end())
                            adys.push_back(mapa[std::make_pair(posicion.first, posicion.second-1)]);
                        std::sort(adys.begin(), adys.end());
                        return adys;
                    };

    std::vector<int> menores;
    for (auto &punto : mapa)
    {
        std::vector<int> adys = ret_adys(punto.first);
        int menor = adys.at(0);
        if (punto.second < menor)
            menores.push_back(punto.second);
    }

    
    int suma = 0;
    std::for_each(menores.begin(), menores.end(), [&] (int &menor)
                                                  {
                                                      suma += (menor + 1);
                                                  });
    std::cout << suma << std::endl;


    return 0;
}




