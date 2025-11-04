#include "Router.h"
#include <iostream>

Router::Router() {}

Router::Router(std::string nombre){
    id = nombre;
}

void Router::agregarConexion(const std::string& destino, int costo){
    conexciones[destino] = costo;
}

void Router::mostrarConexciones() const{
    std::cout << "Router: " << id << " esta conectado con: \n";
    for(auto& par : conexciones){
        std::cout << "-> "  << par.first << " (costo " << par.second << ")\n";
    }
}

const std::string& Router::getId() const { return id; }

