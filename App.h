#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector>
#include <string>
#include "Teclado.h"

class App
{
private:
  std::vector<Teclado> teclados;

public:
  std::vector<std::string> frases;

  App();

  int run(int argc, char* argv[]);
  
  void get_frases(std::string filename);
  void tempo_frases(Teclado& teclado);
  void tempo_frases(Teclado& teclado, std::vector<std::string>& frases);
  void add_teclado(Teclado& teclado);
  Teclado get_teclado(int i);
};

#endif // APP_H
