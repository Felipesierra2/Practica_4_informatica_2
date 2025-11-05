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

void Router::updateEntry(const std::string& destino, const std::string& nextHop, int costo){
    if(destino == id){
        table[destino] = RouteEntry{"-",0};
        return;
    }
    table[destino] = RouteEntry{nextHop, costo};
}

void Router::clearTable(){
    table.clear();
}

void Router::printTable() const{
    std::cout << "Tabla de enrutamiento del router " << id <<":" << std::endl;

    if(table.empty()) {
        std::cout << " (Tabla vacía)" << std::endl;
        return;
    }
    std::cout << "Destino   SiguienteHop  Costo\n";
    std::cout << "------------------------------\n";

    for (const auto& p:table){
        const auto& dest = p.first;
        const auto& entry = p.second;

        std::string nh = entry.nextHop.empty() ? "-" : entry.nextHop;
        std::cout << dest << "      " << nh << "        " << entry.cost << std::endl;
    }
}

const std::map<std::string, RouteEntry>& Router::getTable() const{
    return table;
}

void Router::removeConexion(const std::string& destino) {
    auto it = conexciones.find(destino);
    if (it != conexciones.end()) conexciones.erase(it);
}


