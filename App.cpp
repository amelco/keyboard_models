#include "App.h"
#include "Layout_manager.h"
#include <vector>

int App::run(int argc, char* argv[])
{
  Layout_manager manager;
  std::vector<float> tempo;

  // loop para executar uma função em todos os teclados da lista
  for (size_t i=0; i<manager.get_num_teclados(); ++i)
  {
    Teclado teclado = manager.get_teclado(i);
    std::cout << "\n------------------------------" << std::endl;
    std::cout << manager.layouts_filenames[i] << std::endl;
    std::cout << teclado.print_propriedades() << std::endl;
    tempo = manager.tempo_frases(teclado);
    // calculando media de tempo de digitacao pelo layout
    float soma = 0.0f;
    for (size_t j=0; j<tempo.size(); ++j)
    {
      soma += tempo[j];
    }

    std::cout << "-== Estatísticas ==-" << std::endl;
    std::cout << "Tempo total (m):     " << soma/60.0f << std::endl;
    std::cout << "Frases por minuto:   " << tempo.size()/(soma/60.0f) << std::endl;
    std::cout << "Palavras por minuto: " << "TODO" << std::endl;
  }

  return 0;
}

App::App() {}
App::~App() {}
