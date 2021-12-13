#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

typedef std::pair<int, int> Posicion;

void ver_mapa(std::map<Posicion, int> &mapa, int columnas)
{
    int i = 1;
    for (auto &punto : mapa)
    {
        std::cout << punto.second;
        if (i == columnas)
        {
            std::cout << std::endl;
            i = 1;
            continue;
        }
        i++;
    }
}

std::vector<Posicion> procesar_vecinos(std::map<Posicion, int> &mapa, Posicion &punto)
{
    auto sumar = [&] (Posicion &p) -> void
                 {
                     mapa[p]++;
                 };
    Posicion p;
    std::vector<Posicion> vecinos;
    p = std::make_pair(punto.first-1, punto.second); // Arriba
    if (mapa.find(p) != mapa.end())
    {
        sumar(p);
        vecinos.push_back(p);
    }

    p = std::make_pair(punto.first+1, punto.second); // Abajo
    if (mapa.find(p) != mapa.end())
    {
        sumar(p);
        vecinos.push_back(p);
    }
    p = std::make_pair(punto.first, punto.second-1); // Izquierda
    if (mapa.find(p) != mapa.end())
    {
        sumar(p);
        vecinos.push_back(p);
    }

    p = std::make_pair(punto.first, punto.second+1); // Derecha
    if (mapa.find(p) != mapa.end())
    {
        sumar(p);
        vecinos.push_back(p);
    }
    p = std::make_pair(punto.first-1, punto.second-1); // Arriba izquierda
    if (mapa.find(p) != mapa.end())
    {
        sumar(p);
        vecinos.push_back(p);
    }
    p = std::make_pair(punto.first-1, punto.second+1); // Arriba derecha
    if (mapa.find(p) != mapa.end())
    {
        sumar(p);
        vecinos.push_back(p);
    }

    p = std::make_pair(punto.first+1, punto.second-1); // Abajo derecha
    if (mapa.find(p) != mapa.end())
    {
        sumar(p);
        vecinos.push_back(p);
    }
    p = std::make_pair(punto.first+1, punto.second+1); // Abajo derecha
    if (mapa.find(p) != mapa.end())
    {
        sumar(p);
        vecinos.push_back(p);
    }
    return vecinos;
}

void recursivo(std::map<Posicion, int> &mapa, std::vector<Posicion> &nueves_iniciales, std::vector<Posicion> &procesados)
{
    for (auto &nueve : nueves_iniciales)
    {
        if (std::find(procesados.begin(), procesados.end(), nueve) == procesados.end())
        {
            procesados.push_back(nueve);
            std::vector<Posicion> vecinos = procesar_vecinos(mapa, nueve);
            vecinos.erase(std::remove_if(vecinos.begin(), vecinos.end(), [&] (Posicion &p)
                                                                         {
                                                                             return (mapa[p] <= 9);
                                                                         }), vecinos.end());
            mapa[nueve] = 0;
            recursivo(mapa, vecinos, procesados);
        }
    }
}

unsigned long paso(std::map<Posicion, int> &mapa)
{
    std::vector<Posicion> nueves;
    for (auto &punto : mapa)
    {
        if (punto.second == 9)
            nueves.push_back(punto.first);
        else
            punto.second++;
    }
    std::vector<Posicion> procesados;
    // Recursivo
    recursivo(mapa, nueves, procesados);
    
    for (auto &procesado : procesados)
        mapa[procesado] = 0;

    return procesados.size();
}


int main()
{
    std::ifstream archivo;
    std::string linea;
    std::map<Posicion, int> mapa;

    archivo.open("e11.txt");
    int nfila = 0;
    int ncolumna = 0;
    int columnas = 0;
    while (!archivo.eof())
    {
        std::getline(archivo, linea);
        if (linea.size() > 0)
        {
            columnas = linea.size();
            for (auto &digito : linea)
            {
                Posicion posicion = {nfila, ncolumna};
                mapa[posicion] = digito - '0';
                ncolumna++;
            }
        }
        nfila++;
        ncolumna = 0;
    }
    archivo.close();

    ver_mapa(mapa, columnas);

    unsigned long destellos = 0;
    for (int i = 0; i < 100; ++i)
        destellos += paso(mapa);

    std::cout << std::endl;

    ver_mapa(mapa, columnas);

    std::cout << destellos << std::endl;
    

    return 0;
}




