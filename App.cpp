#include "App.h"
#include "Layout_manager.h"
#include <vector>

int App::run(int argc, char* argv[])
{
  Layout_manager manager;
  std::vector<float> tempo;      // vector com tempo de digitação de cada frase
  std::vector<int> num_palavras; // vector com numero de palavras de cada frase
  std::vector<int> num_chars;    // vector com numero de palavras de cada frase

  // loop para executar uma função em todos os teclados da lista
  for (size_t i=0; i<manager.get_num_teclados(); ++i)
  {
    Teclado teclado = manager.get_teclado(i);
    std::cout << "\n------------------------------" << std::endl;
    std::cout << manager.layouts_filenames[i] << std::endl;
    std::cout << teclado.print_propriedades() << std::endl;
    tempo = manager.tempo_frases(teclado);
    num_palavras = manager.num_palavras_frases(teclado);
    num_chars = manager.num_chars_frases(teclado);
    // calculando media de tempo de digitacao pelo layout
    float soma = 0.0f;
    float pal_por_min_sum = 0.0f;
    float char_por_min_sum = 0.0f;
    for (size_t j=0; j<tempo.size(); ++j)
    {
      soma += tempo[j];
      pal_por_min_sum += num_palavras[j]/(tempo[j]/60.0f);
      char_por_min_sum += num_chars[j]/(tempo[j]/60.0f);


      //std::cout << j << ". " << num_chars[j] << std::endl;
    }
    // calculando palavra spor minuto

    std::cout << "-== Estatísticas ==-" << std::endl;
    std::cout << "Tempo total (m):       " << soma/60.0f << std::endl;
    std::cout << "Frases por minuto:     " << tempo.size()/(soma/60.0f) << std::endl;
    std::cout << "Palavras por minuto:   " << pal_por_min_sum/tempo.size() << std::endl;
    std::cout << "Caracteres por minuto: " << char_por_min_sum/tempo.size() << std::endl;
  }

  return 0;
}

App::App() {}
App::~App() {}
