#include <iostream>
#include "NetWork.h"
#include "Router.h"

using namespace std;

int main()
{
    NetWork red;

    if(red.loadFromFile("topologia.txt")){
        red.mostrarRed();
    }
    return 0;
}
