CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(analise_teclado_layout)

SET(CMAKE_CXX_STANDARD 11)
INCLUDE_DIRECTORIES(include/)

ADD_EXECUTABLE(app
  src/main.cpp
  src/App.cpp
  src/Layout_manager.cpp
  src/Teclado.cpp)
