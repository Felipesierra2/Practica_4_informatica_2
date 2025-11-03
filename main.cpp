#include <iostream>
#include "Router.h"

using namespace std;

int main()
{
    Router A("A");
    Router B("B");

    A.agregarConexion("B", 5);
    A.agregarConexion("C", 7);

    A.mostrarConexciones();
    B.mostrarConexciones();


    cout << "Hello World!" << endl;
    return 0;
}
