#include "Teclado.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

// constroi teclado com layout padrao
Teclado::Teclado() : num_linhas(4), num_colunas(13), varredura(LINHA_COLUNA), temporizador(2)
{
    teclas.push_back(" <XXXXXXXXXXX");
    teclas.push_back("aeosrindmutcl");
    teclas.push_back("pvghqbfzjxkwy");
    teclas.push_back("1234567890,.?");
}

// passa o layout do teclado na construção
Teclado::Teclado(std::vector<std::string> _teclas) : num_linhas(_teclas.size()), num_colunas(_teclas[0].size()), varredura(LINHA_COLUNA), temporizador(2), teclas(_teclas) {}

Teclado::~Teclado() {}

std::string Teclado::print_propriedades()
{
  std::ostringstream output;
  output << "\nCaracterísticas do teclado:\n";
  output << "Colunas:\t\t"      << num_colunas  << std::endl;
  output << "Linhas:\t\t\t"       << num_linhas   << std::endl;
  output << "Temporizador:\t\t"   << temporizador << " s" << std::endl;
  output << "Método varredura:\t";
  if (varredura == LINHA_COLUNA) output << "linha-coluna" << std::endl;
  if (varredura == SEQUENCIAL) output   << "sequencial"   << std::endl;
  return output.str();
}

void Teclado::set_metodo_varredura(std::string _metodo)
{
  if (_metodo.compare("sequencial") == 0) varredura = SEQUENCIAL;
  if (_metodo.compare("linha-coluna") == 0) varredura = LINHA_COLUNA;
}

// nao calcula tempo (tempo=0) para caracteres especiais(!@#$%,.;]{}) e acentos, ou seja,
// só funciona para letras e nuneros e espaços
float Teclado::tempo_digitacao_letra(char letra)
{
  if (!(letra >= 'a' && letra <= 'z') && !(letra >= 'A' && letra <= 'Z') && !(letra >= '0' && letra <= '9') && letra != ' ') return 0.0f;
  float tempo = 0.0f;
  if (varredura == SEQUENCIAL)
  {
    for (int lin=0; lin<num_linhas; ++lin)
    {
      for (int col=0; col<num_colunas; ++col)
      {
        if (teclas[lin][col] == 'X') break;
        tempo += temporizador;
        if (teclas[lin][col] == letra) return tempo;
      }
    }
  }
  else if (varredura == LINHA_COLUNA)
  {
    for (int lin=0; lin<2; ++lin)
    {
      for (int col=0; col<num_colunas; ++col)
      {
        if (teclas[lin][col] == 'X') break;
        //std::cout << teclas[lin][col] << std::endl;
        if (letra == ' ') return temporizador;
        tempo += temporizador;
        if (lin > 0)
        {
          for (int k=0; k<num_linhas-1; ++k) 
          {
            // falta adicionar algoritmo da negação de letras
            if (teclas[lin+k][col] == letra) return tempo + k*temporizador;
          }
        }
      }
    }
  }
  else if (varredura == BINARIA)
  {
    return -1;
  }
  else 
  {
    std::cerr << "Método de varredura inválido" << std::endl;
    std::exit(1);
  }

  return tempo;
}

float Teclado::tempo_digitacao_frase(std::string frase)
{
  float tempo = 0.0f;
  for (size_t j=0; j<frase.size(); ++j)
  {
    char letra = frase[j];
    tempo += tempo_digitacao_letra(letra);
  }
  return tempo;
}

void Teclado::set_layout(std::vector<std::string> layout)
{
  teclas.clear();
  for (size_t i=0; i<layout.size(); ++i)
  {
    teclas.push_back(layout[i]);
  }
  num_linhas = layout.size();
  num_colunas = layout[0].size();
}

void Teclado::le_arquivo_layout(std::string filename)
{
  std::ifstream arq_layout(filename);

  if (arq_layout.fail())
  {
    std::cout << "Erro abrindo arquivo de layout " << filename << std::endl;
    return;
  }

  std::vector<std::string> layout;
  while (!arq_layout.eof())
  {
    std::string line;
    std::getline(arq_layout, line);
    if (line[0] == '#' || line.size() == 0) continue;
    layout.push_back(line);    
  }
  set_layout(layout);
}
