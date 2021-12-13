#ifndef SEPARAR_HPP
#define SEPARAR_HPP

#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> separar_car(std::string cadena, char delimitador)
{
    std::vector<std::string> resultado;
    std::stringstream cad(cadena);
    std::string elemento;

    while (std::getline(cad, elemento, delimitador))
        resultado.push_back(elemento);

    return resultado;
}

std::vector<std::string> separar_cad(std::string cadena, std::string delimitador) {
    std::size_t pos_inicio = 0, pos_final, delim_len = delimitador.length();
    std::string token;
    std::vector<std::string> resultado;

    while ((pos_final = cadena.find(delimitador, pos_inicio)) != std::string::npos) {
        token = cadena.substr(pos_inicio, pos_final - pos_inicio);
        pos_inicio = pos_final + delim_len;
        resultado.push_back(token);
    }

    resultado.push_back(cadena.substr(pos_inicio));
    return resultado;
}



#endif /* SEPARAR_HPP */
