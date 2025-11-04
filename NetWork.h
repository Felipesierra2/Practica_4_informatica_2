#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include "Router.h"

class NetWork
{
private:
    std::map<std::string, Router> routers;
    std::map<std::string, std::vector<std::pair<std::string,int>>> adj;
public:
    void agregarRouter(const std::string& id);
    void conetarRouters(const std::string& id1, const std::string& id2, int costo);
    void mostrarRed() const;

    int getCosto(const std::string& src, const std::string& dst) const;
    std::vector<std::string> getPath(const std::string& src, const std::string& dst)const;

};

#endif // NETWORK_H
