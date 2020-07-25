#ifndef LAYOUT_MAN_H
#define LAYOUT_MAN_H

#include <iostream>
#include <vector>
#include <string>
#include "Teclado.h"

class Layout_manager
{
private:
  std::vector<Teclado> teclados;
  std::string config_file;

  void get_frases(std::string filename);
  void add_teclado(Teclado& teclado);

public:
  std::vector<std::string> frases;
  std::vector<std::string> layouts_filenames;
  std::string metodo_varredura;

  Layout_manager();

  //int run(int argc, char* argv[]);
  
  // tempo das frases da lista de frases do objeto
  std::vector<float> tempo_frases(Teclado& teclado);

  // tempo das frases de uma lista dada pelo usuario
  std::vector<float> tempo_frases(Teclado& teclado, std::vector<std::string>& frases);
  
  Teclado get_teclado(int i);
  size_t get_num_teclados();
  std::string get_frase(int i);
};

#endif // LAYOUT_MAN_H
