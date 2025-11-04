#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <map>

class Router
{
private:
    std::string id; /*Nombre del router*/
    std::map<std::string, int> conexciones; /*Costo del enelace*/
public:
    Router();
    Router(std::string nombre);
    void agregarConexion(const std::string& destino, int costo);
    void mostrarConexciones()const;
    const std::string& getId() const;
};

#endif // ROUTER_H
