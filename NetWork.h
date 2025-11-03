#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <map>
#include "Router.h"

class NetWork
{
private:
    std::map<std::string, Router> routers;
public:
    void agregarRouter(const std::string& id);
    void conetarRouter(const std::string& id1, const std::string& id2, int costo);
    void mostrarRed() const;

};

#endif // NETWORK_H
