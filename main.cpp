#include <iostream>
#include "NetWork.h"
#include "Router.h"

using namespace std;

int main()
{
    NetWork red;

    red.agregarRouter("A");
    red.agregarRouter("B");
    red.agregarRouter("C");

    red.conetarRouters("A","B",5);
    red.conetarRouters("B","C",3);
    red.conetarRouters("A","C",8);

    red.mostrarRed();


    cout << "Hello World!" << endl;
    return 0;
}
