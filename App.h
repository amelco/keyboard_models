#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector>
#include <string>
#include "Teclado.h"

class App
{
public:
  App();
  int run(int argc, char* argv[]);
  void tempo_frases(Teclado& teclado, std::vector<std::string>& frases);
};

#endif // APP_H
