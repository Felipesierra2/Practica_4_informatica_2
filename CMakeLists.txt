cmake_minimum_required(VERSION 3.16)

project(Practica_4_informatica_ll LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Practica_4_informatica_ll main.cpp
    Router.h Router.cpp
    NetWork.h NetWork.cpp)

include(GNUInstallDirs)
install(TARGETS Practica_4_informatica_ll
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
