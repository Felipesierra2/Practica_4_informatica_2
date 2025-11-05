#include "NetWork.h"
#include <iostream>
#include <queue>
#include <functional>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>



void NetWork::agregarRouter(const std::string& id){
    if(routers.find(id) == routers.end()){
        routers[id] = Router(id);
    }else{
        std::cout << "El router: " << id << " ya existe.\n";
    }

}

void NetWork::conetarRouters(const std::string& id1, const std::string& id2, int costo, bool recompute){
    auto it1 = routers.find(id1);
    auto it2 = routers.find(id2);
    if (it1 == routers.end() || it2 == routers.end()) {
        std::cout << "Uno de los routers no existe: " << id1 << " o " << id2 << "\n";
        return;
    }

    it1->second.agregarConexion(id2, costo);
    it2->second.agregarConexion(id1, costo);

    auto actualizar_o_agregar = [&](const std::string& a, const std::string& b, int w){
        auto& vec = adj[a];
        bool encontrado = false;
        for (auto& p : vec){
            if (p.first == b){
                p.second = w; encontrado = true;
                break;
            }
        }
        if (!encontrado) vec.emplace_back(b, w);
    };

    actualizar_o_agregar(id1, id2, costo);
    actualizar_o_agregar(id2, id1, costo);

    if (recompute) computeAllRoutes();

}

void NetWork::mostrarRed() const{
    std::cout << "========RED DE ENRUTADORES==========" << std::endl;
    for (const auto& par:routers){
        par.second.mostrarConexciones();
        std::cout << "\n";
    }
    for (const auto& [nombre, router] : routers) {
        std::cout << "Tabla de " << nombre << ":\n";
        router.printTable();
    }
}

static std::pair<std::unordered_map<std::string,int>, std::unordered_map<std::string,std::string>>
dijkstra_aux(const std::map<std::string, Router>& routers,
             const std::map<std::string, std::vector<std::pair<std::string, int>>>& adj,
             const std::string& src){

    const int INF = std::numeric_limits<int>::max() / 4;
    std::unordered_map<std::string,int> dist;
    std::unordered_map<std::string, std::string> prev;
    std::unordered_map<std::string,int> hops;

    for (const auto& p : routers){
        dist[p.first] = INF;
        prev[p.first] = "";
        hops[p.first] = INF;
    }

    if(routers.find(src) == routers.end()){
        return{dist,prev};
    }

    using PI = std::pair<int, std::string>;
    std::priority_queue<PI, std::vector<PI>, std::greater<PI>> pq;

    dist[src] = 0;
    hops[src] = 0;
    pq.push({0,src});

    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();
        if(d != dist[u]) continue;

        auto it = adj.find(u);
        if(it == adj.end()) continue;

        for (const auto& edge: it -> second){
            const std::string& v = edge.first;
            int w = edge.second;

            if(dist[u] == INF) continue;
            int nd = dist[u] + w;
            int nh = hops[u] + 1;

            /*Si encontramos mejor distancia O misma distancia, pero menos hops
             -> actualizamos*/
            if(nd < dist[v] || (nd == dist[v] && nh < hops[v])){
                dist[v] = nd;
                prev[v] = u;
                hops[v] = nh;
                pq.push({dist[v], v});

            }
        }
    }

    return {dist, prev};
}

int NetWork::getCosto(const std::string& src, const std::string& dst) const{
    auto resultado = dijkstra_aux(routers, adj, src);
    const auto &dist = resultado.first;
    auto it = dist.find(dst);

    if (it == dist.end()) return -1;
    int val = it ->second;
    const int INF = std::numeric_limits<int>::max() / 4;

    if (val >= INF) return -1;

    return val;
}

std::vector<std::string> NetWork::getPath(const std::string& src, const std::string& dst) const{
    auto resultado = dijkstra_aux(routers,adj,src);
    const auto &dist = resultado.first;
    const auto &prev = resultado.second;

    std::vector<std::string> path;
    auto it = dist.find(dst);
    const int INF = std::numeric_limits<int>::max() / 4;

    if (it == dist.end() || it -> second >= INF) return path;

    std::string cur = dst;
    while(!cur.empty()){
        path.push_back(cur);

        if (cur == src) break;

        auto itp = prev.find(cur);

        if(itp == prev.end() || itp ->second.empty()) {path.clear(); return path;}

        cur = itp->second;
    }

    std::reverse(path.begin(), path.end());

    if (path.empty() || path.front() != src) return {};

    return path;
}

void NetWork::computeAllRoutes(){

    for(auto &p : routers){
        p.second.clearTable();
    }

    for(const auto& src_pair: routers){
        const std::string src = src_pair.first;

        auto result = dijkstra_aux(routers,adj,src);
        const auto& dist = result.first;
        const auto& prev = result.second;

        for(const auto& dst_pair : routers) {
            const std::string dst = dst_pair.first;

            auto itd = dist.find(dst);
            const int INF = std::numeric_limits<int>::max() / 4;
            if(itd == dist.end() || itd->second >= INF){
                continue;
            }

            std::vector<std::string> path;
            std::string cur = dst;
            while(true){
                path.push_back(cur);

                if(cur == src) break;

                auto itp = prev.find(cur);

                if(itp == prev.end() || itp->second.empty()){
                    path.clear();
                    break;
                }

                cur = itp->second;
            }

            if (path.empty()) continue;
            std::reverse(path.begin(), path.end());

            std::string nextHop;
            if(src == dst){
                nextHop = "-";
            }else if (path.size() >= 2){
                nextHop = path[1];
            }else{
                nextHop = path.front();
            }

            int cost = itd->second;

            routers[src].updateEntry(dst,nextHop,cost);

        }
    }
}

void NetWork::removeLink(const std::string& id1, const std::string& id2, bool recompute){
    auto it1 = adj.find(id1);
    if(it1 != adj.end()){
        auto& vec = it1->second;
        vec.erase(std::remove_if(vec.begin(), vec.end(),
                                 [&](const std::pair<std::string,int>&p){ return p.first == id2;}),
                  vec.end());
    }
    auto it2 = adj.find(id1);
    if(it2 != adj.end()){
        auto& vec = it2->second;
        vec.erase(std::remove_if(vec.begin(), vec.end(),
                                 [&](const std::pair<std::string,int>&p){ return p.first == id2;}),
                  vec.end());
    }

    auto r1 = routers.find(id1);
    // if (r1 != routers.end()) r1->second.removeConexion(id2);

    auto r2 = routers.find(id2);
    // if(r2 != routers.end())r1->second.removeConexion(id2);

    if (recompute) computeAllRoutes();
}

bool NetWork::loadFromFile(const std::string& path){
    std::ifstream f(path);
    if (!f.is_open()){
        std::cerr << "No se pudo abrir el archivo: " << path << "\n";
        return false;
    }

    std::string line;

    while (std::getline(f,line)){
        if (line.empty()) continue;

        if (line.size() > 0 && line[0] == '#') continue;

        std::istringstream iss(line);
        std::string u,v;
        int cost;
        if (!(iss >> u >> v >> cost)){
            continue;
        }

        if(routers.find(u) == routers.end()) agregarRouter(u);
        if(routers.find(v) == routers.end()) agregarRouter(v);

        conetarRouters(u, v, cost);
    }
    computeAllRoutes();
    return true;
}





