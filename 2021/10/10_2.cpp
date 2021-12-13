#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>

int main()
{
    std::ifstream archivo;
    std::string linea;
    std::vector<std::string> lineas;

    archivo.open("e10.txt");
    while (!archivo.eof())
    {
        std::getline(archivo, linea);
        if (linea.size() > 0)
            lineas.push_back(linea);
    }
    archivo.close();

    std::stack<char> pila;
    std::vector<unsigned long> puntuaciones;

    for (auto &linea : lineas)
    {
        bool correcto = true;
        for (auto &caracter : linea)
        {
            if (!correcto)
                break;
            switch (caracter)
            {
                case '(':
                case '{':
                case '[':
                case '<':
                    pila.push(caracter);
                    break;
                case ')':
                    if (pila.top() != '(')
                        correcto = false;
                    pila.pop();
                    break;
                case '}':
                    if (pila.top() != '{')
                        correcto = false;
                    pila.pop();
                    break;
                case ']':
                    if (pila.top() != '[')
                        correcto = false;
                    pila.pop();
                    break;
                case '>':
                    if (pila.top() != '<')
                        correcto = false;
                    pila.pop();
                    break;
            }
        }
        if (correcto)
        {
            std::vector<char> resto;
            unsigned long puntuacion = 0;
            while (!pila.empty())
            {
                resto.push_back(pila.top());
                pila.pop();
            }
            for (auto &r : resto)
            {
                puntuacion *= 5;
                switch (r)
                {
                    case '(':
                        puntuacion += 1;
                        break;
                    case '[':
                        puntuacion += 2;
                        break;
                    case '{':
                        puntuacion += 3;
                        break;
                    case '<':
                        puntuacion += 4;
                        break;
                }
            }
            puntuaciones.push_back(puntuacion);
        }
        while (!pila.empty())
            pila.pop();
    }

    std::sort(puntuaciones.begin(), puntuaciones.end());
    std::cout << puntuaciones.at(((puntuaciones.size() + 1) / 2)-1) << std::endl;
    
    return 0;
}



