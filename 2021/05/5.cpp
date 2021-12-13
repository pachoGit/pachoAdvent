#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>

struct Punto
{
    int x, y;

    bool operator == (struct Punto &otro)
    {
        return (x == otro.x && y == otro.y);
    }
};
    
struct Linea
{
    struct Punto p1;
    struct Punto p2;
};

struct Celda
{
    struct Punto punto;
    int valor;
};

void ver_linea(struct Linea linea)
{
    std::cout << "Linea: " << linea.p1.x << " " << linea.p1.y << " " << linea.p2.x << " " << linea.p2.y << std::endl;
}

bool existe_punto(std::vector<Celda> &celdas, Punto punto)
{
    for (auto &celda : celdas)
    {
        if (celda.punto == punto)
        {
            celda.valor++;
            return true;
        }
    }
    return false;
}

int main()
{
    FILE *archivo = fopen("e5.txt", "r");
    if (!archivo)
        return -1;

    std::vector<Linea> lineas;

    Linea linea;
    while (fscanf(archivo, "%d,%d -> %d,%d", &linea.p1.x, &linea.p1.y, &linea.p2.x, &linea.p2.y))
    {
        if (feof(archivo) != 0)
            break;
        lineas.push_back(linea);
    }
    fclose(archivo);

    std::vector<Celda> celdas;
    
    int contador = 1;
    for (auto &linea : lineas)
    {
        std::cout << "Comprobando la linea: " << contador << std::endl;
        contador++;
        Punto punto;
        if (linea.p1.x == linea.p2.x)
        {
            int inicio = std::min(linea.p1.y, linea.p2.y);
            int fin    = std::max(linea.p1.y, linea.p2.y);
            for (int i = inicio; i <= fin; ++i)
            {
                punto = {linea.p1.x, i};
                if (existe_punto(celdas, punto) == false)
                    celdas.push_back({punto, 1});
            }
        }
        if (linea.p1.y == linea.p2.y)
        {
            int inicio = std::min(linea.p1.x, linea.p2.x);
            int fin    = std::max(linea.p1.x, linea.p2.x);
            for (int i = inicio; i <= fin; ++i)
            {
                punto = {i, linea.p1.y};
                if (existe_punto(celdas, punto) == false)
                    celdas.push_back({punto, 1});
            }
        }
    }

    int resultado = 0;
    for (auto &celda : celdas)
        if (celda.valor >= 2)
            resultado++;

    std::cout << resultado << std::endl;

    return 0;
}
