# Simulación de red de enrutadores

Compilar:
  g++ -std=c++17 main.cpp Router.cpp Network.cpp -o red

Uso (CLI):
  ./red
  help  # lista comandos

Formato archivo topología:
  Cada línea: <A> <B> <cost>
  Comentarios con '#'

Funcionalidades:
 - Agregar / eliminar routers
 - Agregar / eliminar enlaces
 - Cargar topología desde archivo
 - Generar red aleatoria
 - Consultar costo y camino más corto (Dijkstra)
 - Tablas de enrutamiento actualizan tras cambios
