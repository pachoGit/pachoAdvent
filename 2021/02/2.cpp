#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>

struct Posicion
{
    int profundidad;
    int horizontal;
};

struct Info
{
    char comando[20];
    int valor;
};

int main()
{
    std::vector<Info> instrucciones;
    FILE *archivo = fopen("e2.txt", "r");

    Info info;
    while (fscanf(archivo, "%s %d", info.comando, &info.valor))
    {
        if (feof(archivo) != 0)
            break;
        instrucciones.push_back(info);
    }

    fclose(archivo);

    Posicion posicion = {0, 0};

    for (auto instruccion : instrucciones)
    {
        if (strcmp(instruccion.comando, "forward") == 0)
            posicion.horizontal += instruccion.valor;
        if (strcmp(instruccion.comando, "down") == 0)
            posicion.profundidad += instruccion.valor;
        if (strcmp(instruccion.comando, "up") == 0)
            posicion.profundidad -= instruccion.valor;
    }

    std::cout << posicion.profundidad * posicion.horizontal << std::endl;

    return 0;
}

