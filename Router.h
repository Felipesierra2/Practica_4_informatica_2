#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <map>

struct RouteEntry{
    std::string nextHop;
    int cost;
};

class Router
{
private:
    std::string id; /*Nombre del router*/
    std::map<std::string, int> conexciones; /*Costo del enelace*/
    std::map<std::string, RouteEntry> table;
public:
    Router();
    Router(std::string nombre);

    void agregarConexion(const std::string& destino, int costo);
    void mostrarConexciones()const;
    void removeConexion(const std::string &destino);
    const std::string& getId() const;

    void updateEntry(const std::string& destino, const std::string& nextHop, int costo);
    void clearTable();
    void printTable() const;
    const std::map<std::string, RouteEntry>& getTable() const;
};

#endif // ROUTER_H
