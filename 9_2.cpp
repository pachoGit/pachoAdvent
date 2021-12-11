#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

/*
void recursivo(std::vector<std::pair<int, int>> &cuencas_inicio, std::vector<std::pair<int, int>> &cuencas_final)
{
    for (auto &cuenca : cuencas_inicio)
    {
        bool existe = (std::find(cuencas_final.begin(), cuencas.end(), cuenca) != cuencas_final.end());
        if (existe)
            
    }
}
*/

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

    std::vector<std::pair<int, int>> menores;
    for (auto &punto : mapa)
    {
        std::vector<int> adys = ret_adys(punto.first);
        int menor = adys.at(0);
        if (punto.second < menor)
            menores.push_back(punto.first);
    }

    auto ret_cuencas = [&] (std::pair<int, int> &menor) -> std::vector<std::pair<int, int>>
            {
                std::vector<std::pair<int, int>> cuencas;
                std::pair<int, int> cuenca = std::make_pair(menor.first - 1, menor.second);
                while (mapa.find(cuenca) != mapa.end())
                {
                    if (mapa[cuenca] == 9)
                        break;
                    cuencas.push_back(cuenca);
                    cuenca.first--;
                }
                cuenca = std::make_pair(menor.first + 1, menor.second);
                while (mapa.find(cuenca) != mapa.end())
                {
                    if (mapa[cuenca] == 9)
                        break;
                    cuencas.push_back(cuenca);
                    cuenca.first++;
                }
                cuenca = std::make_pair(menor.first, menor.second - 1);
                while (mapa.find(cuenca) != mapa.end())
                {
                    if (mapa[cuenca] == 9)
                        break;
                    cuencas.push_back(cuenca);
                    cuenca.second--;
                }
                cuenca = std::make_pair(menor.first, menor.second + 1);
                while (mapa.find(cuenca) != mapa.end())
                {
                    if (mapa[cuenca] == 9)
                        break;
                    cuencas.push_back(cuenca);
                    cuenca.second++;
                }
                cuencas.push_back(menor);
                return cuencas;
            };

    std::vector<std::pair<int, int>> cuencas_final;

    auto existe_cuenca = [&] (std::pair<int, int> &cuenca) -> bool
                         {
                             return (std::find(cuencas_final.begin(), cuencas_final.end(), cuenca) != cuencas_final.end());
                         };

    std::function<void(std::vector<std::pair<int, int>>)> recursivo = [&] (std::vector<std::pair<int, int>> cuencas) -> void
                                                                      {
                                                                          for (auto &cuenca : cuencas)
                                                                          {
                                                                              cuencas_final.push_back(cuenca);
                                                                              //std::cout << "De: (" << cuenca.first << ", " << cuenca.second << ") -> " << mapa[cuenca] << std::endl;
                                                                              std::vector<std::pair<int, int>> nuevos = ret_cuencas(cuenca);
                                                                              nuevos.erase(std::remove_if(nuevos.begin(), nuevos.end(), [&](auto &n)
                                                                                                                                        {
                                                                                                                                            return (existe_cuenca(n));
                                                                                                                                        }), nuevos.end());

                                                                              recursivo(nuevos);
                                                                          }
                                                                      };

    std::vector<int> tams;
    for (auto &menor : menores)
    {
        std::vector<std::pair<int, int>> cuencas_menor = ret_cuencas(menor);
        std::cout << "Cuencas iniciales de: (" << menor.first << ", " << menor.second << ") -> " << mapa[menor] << " --- ";
        std::cout << std::endl;
        recursivo(cuencas_menor);
        
        std::sort(cuencas_final.begin(), cuencas_final.end());
        auto unicos = std::unique(cuencas_final.begin(), cuencas_final.end());
        cuencas_final.erase(unicos, cuencas_final.end());

        tams.push_back(cuencas_final.size());
        cuencas_final.clear();
    }

    std::sort(tams.begin(), tams.end());
    int i = tams.size() - 1;

    std::cout << tams.at(i) * tams.at(i-1) * tams.at(i-2) << std::endl;

    
    return 0;
}




