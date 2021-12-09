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

bool actualizar(std::vector<Celda> &celdas, Punto punto)
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
        /*
        std::cout << "Comprobando la linea: " << contador << std::endl;
        contador++;
        */

        Punto punto;
        if (linea.p1.x == linea.p2.x)
        {
            int inicio = std::min(linea.p1.y, linea.p2.y);
            int fin    = std::max(linea.p1.y, linea.p2.y);
            for (int i = inicio; i <= fin; ++i)
            {
                punto = {linea.p1.x, i};
                //std::cout << "(" << punto.x << ", " << punto.y << ") ";
                if (actualizar(celdas, punto) == false)
                    celdas.push_back({punto, 1});
            }
            //std::cout << std::endl;
        }
        else if (linea.p1.y == linea.p2.y)
        {
            int inicio = std::min(linea.p1.x, linea.p2.x);
            int fin    = std::max(linea.p1.x, linea.p2.x);
            for (int i = inicio; i <= fin; ++i)
            {
                punto = {i, linea.p1.y};
                //std::cout << "(" << punto.x << ", " << punto.y << ") ";
                if (actualizar(celdas, punto) == false)
                    celdas.push_back({punto, 1});
            }
            //std::cout << std::endl;
        }
        else if (linea.p1.x == linea.p1.y && linea.p2.x == linea.p2.y)
        {
            int inicio = std::min(linea.p1.x, linea.p2.x);
            int fin    = std::max(linea.p1.x, linea.p2.x);
            for (int i = inicio; i <= fin; ++i)
            {
                punto = {i, i};
                //std::cout << "(" << punto.x << ", " << punto.y << ") ";
                if (actualizar(celdas, punto) == false)
                    celdas.push_back({punto, 1});
            }
            //std::cout << std::endl;
        }
        else
        {
            bool sumar_ejes = false;
            Punto partida;
            if (linea.p1.x < linea.p2.x)
            {
                if (linea.p1.y < linea.p2.y)
                {
                    // p1 suma en "x" y "y"
                    partida = linea.p1; // Sumar en ambos
                    sumar_ejes = true;
                }
                else
                {
                    // p1 suma en "x" y resta en "Y"
                    partida = linea.p1;
                }
            }
            else
            {
                if (linea.p1.y < linea.p2.y)
                {
                    partida = linea.p2;
                }
                else
                {
                    partida = linea.p2; // Sumar en ambos
                    sumar_ejes = true;
                }
            }

            int xfin = std::max(linea.p1.x, linea.p2.x);
            int ycont = 0;
            if (sumar_ejes)
            {
                for (int x = partida.x; x <= xfin; ++x)
                {
                    punto = {x, partida.y + ycont};
                    //std::cout << "(" << punto.x << ", " << punto.y << ") ";
                    if (actualizar(celdas, punto) == false)
                        celdas.push_back({punto, 1});
                    ycont++;
                }
            }

            else
            {
                for (int x = partida.x; x <= xfin; ++x)
                {
                    punto = {x, partida.y - ycont};
                    //std::cout << "(" << punto.x << ", " << punto.y << ") ";
                    if (actualizar(celdas, punto) == false)
                        celdas.push_back({punto, 1});
                    ycont++;
                }
                //std::cout << std::endl;
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
