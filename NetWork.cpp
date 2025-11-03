#include "NetWork.h"
#include <iostream>



void NetWork::agregarRouter(const std::string& id){
    if(routers.find(id) == routers.end()){
        routers[id] = Router(id);
    }else{
        std::cout << "El router: " << id << " ya existe.\n";
    }

}
