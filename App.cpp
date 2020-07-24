#include "App.h"
#include <fstream>
#include <string>

App::App() {}

int App::run(int argc, char* argv[])
{
  get_frases("frases.txt");
  
  int total_layouts = 3;
  std::vector<std::string> filenames = { 
    "qwerty.layout", 
    "mvp.layout", 
    "novo.layout" 
  };

  // loop para adicionar todos os teclados desejados
  // a listya de teclados está no vector filenames
  for (int i=0; i<total_layouts; ++i)
  {
    Teclado teclado;
    //teclado.set_metodo_varredura("linha-coluna");
    teclado.set_metodo_varredura("sequencial");
    teclado.le_arquivo_layout(filenames[i]);
    add_teclado(teclado);
  }

  // loop para executar uma função em todos os teclados da lista
  for (int i=0; i<total_layouts; ++i)
  {
    Teclado teclado = get_teclado(i);
    std::cout << "\n" << filenames[i] << std::endl;
    std::cout << teclado.print_propriedades() << std::endl;
    tempo_frases(teclado);
  }

  return 0;
}

void App::get_frases(std::string filename)
{
  std::ifstream arq_frases(filename);
  if (arq_frases.fail())
  {
    std::cerr << "Falha ao abrir arquivo de frases " << filename << std::endl;
    return;
  }
  while (!arq_frases.eof())
  {
    std::string line;
    std::getline(arq_frases, line);
    if (line.size() != 0) frases.push_back(line);
  }
}

void App::tempo_frases(Teclado& teclado)
{ 
  if (frases.size() == 0) 
  {
    std::cerr << "Carregue um arquivo de frases" << std::endl;
    return;
  }
  tempo_frases(teclado, this->frases); 
}

void App::tempo_frases(Teclado& teclado, std::vector<std::string>& frases)
{
  for (size_t i=0; i<frases.size(); ++i)
    std::cout << teclado.tempo_digitacao_frase(frases[i]) << std::endl;
}

void App::add_teclado(Teclado& teclado)
{
  teclados.push_back(teclado);
}

Teclado App::get_teclado(int i)
{
  return teclados[i];
}
