#include "NetWork.h"
#include <iostream>
#include <queue>
#include <functional>
#include <limits>
#include <algorithm>


void NetWork::agregarRouter(const std::string& id){
    if(routers.find(id) == routers.end()){
        routers[id] = Router(id);
    }else{
        std::cout << "El router: " << id << " ya existe.\n";
    }

}

void NetWork::conetarRouters(const std::string& id1, const std::string& id2, int costo){
    auto it1 = routers.find(id1);
    auto it2 = routers.find(id2);
    if (it1 == routers.end() || it2 == routers.end()) {
        std::cout << "Uno de los routers no existe: " << id1 << " o " << id2 << "\n";
        return;
    }

    it1->second.agregarConexion(id2, costo);
    it2->second.agregarConexion(id1, costo);
}

void NetWork::mostrarRed() const{
    std::cout << "========RED DE ENRUTADORES==========" << std::endl;
    for (const auto& par:routers){
        par.second.mostrarConexciones();
        std::cout << "\n";
    }
}

static std::pair<std::unordered_map<std::string,int>, std::unordered_map<std::string,std::string>>
dijkstra_aux(const std::map<std::string, Router>& routers,
             const std::map<std::string, std::vector<std::pair<std::string, int>>>& adj,
             const std::string& src){

    const int INF = std::numeric_limits<int>::max() / 4;
    std::unordered_map<std::string,int> dist;
    std::unordered_map<std::string, std::string> prev;

    for (const auto& p : routers){
        dist[p.first] = INF;
        prev[p.first] = "";
    }

    if(routers.find(src) == routers.end()){
        return{dist,prev};
    }

    using PI = std::pair<int, std::string>;
    std::priority_queue<PI, std::vector<PI>, std::greater<PI>> pq;

    dist[src] = 0;
    pq.push({0,src});

    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();
        if(d != dist[u]) continue;
        auto it = adj.find(u);
        if(it == adj.end()) continue;

        for (const auto& edge: it -> second){
            const std::string& v = edge.first;
            int w = edge.second;

            if(dist[u] != INF && dist[u] + w <dist[v]){
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return {dist, prev};
}

int NetWork::getCosto(const std::string& src, const std::string& dst) const{

}





