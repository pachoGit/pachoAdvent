#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

#define NHILOS 8

unsigned int nveces = 0;
std::vector<int> profundidades;

void resolver(int inicio, int fin)
{
    for (int i = inicio; i < fin; ++i)
    {
        if (profundidades.at(i) < profundidades.at(i+1))
            nveces++;
    }
}

int main()
{
    std::ifstream archivo;
    std::string linea;
    //std::vector<int> profundidades;

    archivo.open("e1.txt");
    if (!archivo.is_open())
        return -1;
    
    while (!archivo.eof())
    {
        std::getline(archivo, linea);
        if (linea.length() != 0)
            profundidades.push_back(std::stoi(linea));
    }

    archivo.close();

    std::thread hilos[NHILOS];
    int bloques = profundidades.size() / NHILOS;

    auto inicio_hora = std::chrono::steady_clock::now();
    for (int i = 0; i < NHILOS; ++i)
    {
        int inicio = bloques * i;
        int fin = inicio + bloques;
        if (fin == (int) profundidades.size())
            fin -= 1;
        //std::cout << i << " - " << inicio << " " << fin << std::endl;
        hilos[i] = std::thread(resolver, inicio, fin);
    }
    for (int i = 0; i < NHILOS; ++i)
        hilos[i].join();

    auto fin_hora = std::chrono::steady_clock::now();

    std::chrono::duration<double>  duracion = fin_hora - inicio_hora;
    std::cout << "Tiempo de calculo: " << duracion.count() << "s" << std::endl;

    std::cout << "Veces: " << nveces << std::endl;

    return 0;
}
