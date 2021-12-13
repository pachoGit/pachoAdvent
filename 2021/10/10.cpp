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

    int puntuacion = 0;
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
                    {
                        puntuacion += 3;
                        correcto = false;
                    }
                    pila.pop();
                    break;
                case '}':
                    if (pila.top() != '{')
                    {
                        puntuacion += 1197;
                        correcto = false;
                    }
                    pila.pop();
                    break;
                case ']':
                    if (pila.top() != '[')
                    {
                        puntuacion += 57;
                        correcto = false;
                    }
                    pila.pop();
                    break;
                case '>':
                    if (pila.top() != '<')
                    {
                        puntuacion += 25137;
                        correcto = false;
                    }
                    pila.pop();
                    break;
            }
        }
        while (!pila.empty())
            pila.pop();
    }

    std::cout << puntuacion << std::endl;

    return 0;
}



