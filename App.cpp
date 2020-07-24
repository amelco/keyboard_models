#include "App.h"
#include "Utils.h"
#include <fstream>
#include <string>

App::App() : config_file("app.conf")
{
  // verifica existencia de arquivo de configuração
  std::ifstream file(config_file);
  if (!file) 
  {
    // arquivo de configuração não existe. Criando um default
    std::ofstream ofile(config_file);
    ofile << "# Arquivo de configuração\n";
    ofile << "# Isso é um comentário\n";
    ofile << "# Os valores devem estar na mesma linha do atributo\n";
    ofile << "#   atributo = valor1, valor2, valor3, ...\n";
    ofile << "# A ordem dos atributos não importa\n\n";
    ofile << "# nome dos arquivos contendo layouts\n";
    ofile << "layouts = qwerty.layout, default.layout\n\n";
    ofile << "# método de varredura padrão\n";
    ofile << "varredura = linha-coluna\n";
    ofile.close();
    file.open(config_file);
  }

  // lê arquivo de configuração
  while(!file.eof())
  {
    std::string line;
    std::getline(file, line);
    // desconsidera comentários e linhas vazias
    if (line[0] == '#' || line.size() == 0) continue;
    size_t  pos_sep = line.find('=');
    if (pos_sep != std::string::npos)
    {
      // existe = na linha. É um atributo
      std::string atributo = line.substr(0, pos_sep);
      atributo = trim(atributo);
      if (atributo.compare("layouts") == 0)
      {
        std::string value;
        size_t pos_next_sep = line.find(',', pos_sep);
        while (pos_next_sep != std::string::npos)
        {
          value = trim(line.substr(pos_sep+1, pos_next_sep-pos_sep-1));
          layouts_filenames.push_back(value);
          pos_sep = pos_next_sep+1;
          pos_next_sep = line.find(',', pos_sep);
        }
        value = trim(line.substr(pos_sep+1));
        layouts_filenames.push_back(value);
      }
      else if (atributo.compare("varredura") == 0)
      {
        std::string value = trim(line.substr(pos_sep+1));
        metodo_varredura = value;
      }
      else
      {
        std::cerr << "Opção " << atributo << " desconhecida. Verifique o arquivo de configuração.\n";
      }
    }

  }

}

int App::run(int argc, char* argv[])
{
  get_frases("frases.txt");
  
  int total_layouts = 3;

  // loop para adicionar todos os teclados desejados
  // a listya de teclados está no vector filenames
  for (int i=0; i<total_layouts; ++i)
  {
    Teclado teclado;
    teclado.set_metodo_varredura(metodo_varredura);
    teclado.le_arquivo_layout(layouts_filenames[i]);
    add_teclado(teclado);
  }

  // loop para executar uma função em todos os teclados da lista
  for (int i=0; i<total_layouts; ++i)
  {
    Teclado teclado = get_teclado(i);
    std::cout << "\n" << layouts_filenames[i] << std::endl;
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
