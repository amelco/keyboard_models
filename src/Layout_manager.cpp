#include "Layout_manager.h"
#include "Utils.h"
#include <fstream>
#include <string>

Layout_manager::Layout_manager() : config_file("app.conf")
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
    ofile << "# A ordem dos atributos não importa\n";
    ofile << "# As frases devem estar entre FRASES=ini e FRASES=end\n\n";
    ofile << "# nome dos arquivos contendo layouts\n";
    ofile << "layouts = qwerty.layout, default.layout\n\n";
    ofile << "# método de varredura padrão [linha-coluna, sequencial, binaria]\n";
    ofile << "varredura = linha-coluna\n\n";
    ofile << "FRASES = ini\n";
    ofile << "ola mundo\n";
    ofile << "estou com sede\n";
    ofile << "quero ligar a televisao\n";
    ofile << "o rato roeu a roupa do rei de roma\n";
    ofile << "o sofrimento do jovem werner\n";
    ofile << "i dont know when you are at home\n";
    ofile << "FRASES = end\n";
    ofile.close();
    file.open(config_file);
  }

  // lê arquivo de configuração
  bool bFrases = false;
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
      std::string atributo = trim(line.substr(0, pos_sep));
      std::string value = trim(line.substr(pos_sep+1));
      if (atributo.compare("layouts") == 0)
      {
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
        metodo_varredura = value;
      }
      else if (atributo.compare("FRASES") == 0)
      {
        if (value.compare("ini") == 0)
        { 
          bFrases = true;
          continue;
        }
        else if (value.compare("end") == 0) bFrases = false;
        else
        {
          std::cerr << "Erro no arquivo de configuração. Verifique se as FRASES obedecem o padrao." << std::endl;
        }
      }
      else
      {
        std::cerr << "Opção " << atributo << " desconhecida. Verifique o arquivo de configuração.\n";
      }
    }
    // adiciona frases na lista
    if (bFrases)
    {
      frases.push_back(line);
    }
  }
  // adiciona os teclados da lista do arquivo de configuração
  for (size_t i=0; i<layouts_filenames.size(); ++i)
  {
    Teclado teclado(metodo_varredura);
    teclado.le_arquivo_layout(layouts_filenames[i]);
    add_teclado(teclado);
  }

}

void Layout_manager::get_frases(std::string filename)
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

std::vector<float> Layout_manager::tempo_frases(Teclado& teclado)
{ 
  std::vector<float> result;
  if (frases.size() == 0) 
  {
    std::cerr << "Carregue um arquivo de frases" << std::endl;
    return result;
  }
  result = tempo_frases(teclado, this->frases); 
  return result;
}

std::vector<float> Layout_manager::tempo_frases(Teclado& teclado, std::vector<std::string>& frases)
{
  std::vector<float> result;
  for (size_t i=0; i<frases.size(); ++i)
    result.push_back(teclado.tempo_digitacao_frase(frases[i]));
  return result;
}

std::vector<int> Layout_manager::num_palavras_frases(Teclado& teclado)
{ 
  std::vector<int> result;
  if (frases.size() == 0) 
  {
    std::cerr << "Carregue um arquivo de frases" << std::endl;
    return result;
  }
  result = num_palavras_frases(teclado, this->frases); 
  return result;
}

std::vector<int> Layout_manager::num_palavras_frases(Teclado& teclado, std::vector<std::string>& frases)
{
  std::vector<int> result;
  for (size_t i=0; i<frases.size(); ++i) 
  {
    // Retornar número de palavras da frase atual
    // Faz isso contando o numero de espaçoes e adicionando 1 (simple por enquanto)
    int count = 1;
    for (size_t j=0; j<frases[i].length(); ++j)
    {
      if (frases[i][j] == ' ') count++;
    }
    //std::cout << count << std::endl;
    result.push_back(count);
  }
  return result;
}

std::vector<int> Layout_manager::num_chars_frases(Teclado& teclado)
{ 
  std::vector<int> result;
  if (frases.size() == 0) 
  {
    std::cerr << "Carregue um arquivo de frases" << std::endl;
    return result;
  }
  result = num_chars_frases(teclado, this->frases); 
  return result;
}

std::vector<int> Layout_manager::num_chars_frases(Teclado& teclado, std::vector<std::string>& frases)
{
  std::vector<int> result;
  for (size_t i=0; i<frases.size(); ++i) 
  {
    // Retornar número de caracteres da frase atual
    // Só conta letras e números
    int count = 0;
    for (size_t j=0; j<frases[i].length(); ++j)
    {
      char letra = frases[i][j];
      if ((letra >= 'a' && letra <= 'z') || (letra >= 'A' && letra <= 'Z') || (letra >= '0' && letra <= '9') || letra == ' ')
      {
        count++;
      }
    }
    //std::cout << count << std::endl;
    result.push_back(count);
  }
  return result;
}

void Layout_manager::add_teclado(Teclado& teclado)
{
  teclados.push_back(teclado);
}

Teclado Layout_manager::get_teclado(int i)
{
  return teclados[i];
}

size_t Layout_manager::get_num_teclados()
{
  return teclados.size();
}
