#include "App.h"

App::App() {}

int App::run(int argc, char* argv[])
{
  std::vector<std::string> frases = 
  {
    "ola mundo",
    "estou com sede",
    "quero ligar a televisao",
    "o rato roeu a roupa do rei de roma,"
    "o sofrimento do jovem werner",
    "i dont know when you are at home"
  };

  Teclado teclado;
  teclado.set_metodo_varredura("linha-coluna");

  std::cout << "\nlayout: qwerty" << std::endl;
  teclado.le_arquivo_layout("qwerty.layout");
  std::cout << teclado.print_propriedades() << std::endl;
  tempo_frases(teclado, frases);

  std::cout << "\nlayout: MVP" << std::endl;
  teclado.le_arquivo_layout("mvp.layout");
  std::cout << teclado.print_propriedades() << std::endl;
  tempo_frases(teclado, frases);
  
  std::cout << "\nlayout: novo" << std::endl;
  teclado.le_arquivo_layout("novo.layout");
  std::cout << teclado.print_propriedades() << std::endl;
  tempo_frases(teclado, frases);

  return 0;
}

void App::tempo_frases(Teclado& teclado, std::vector<std::string>& frases)
{
  for (size_t i=0; i<frases.size(); ++i)
    std::cout << teclado.tempo_digitacao_frase(frases[i]) << std::endl;
}
