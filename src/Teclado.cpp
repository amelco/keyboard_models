#include "Teclado.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

// constroi teclado com layout padrao
Teclado::Teclado(std::string _varredura) : num_linhas(4), num_colunas(13), temporizador(2)
{
  set_metodo_varredura(_varredura);
  teclas_vetorizadas = " <aeosrindmutclpvghqbfzjxkwy1234567890,.?";
  teclas.push_back(" <XXXXXXXXXXX");
  teclas.push_back("aeosrindmutcl");
  teclas.push_back("pvghqbfzjxkwy");
  teclas.push_back("1234567890,.?");
}

// passa o layout do teclado na construção
Teclado::Teclado(std::vector<std::string> _teclas, std::string _varredura) : num_linhas(_teclas.size()), num_colunas(_teclas[0].size()), varredura(varredura), temporizador(2), teclas(_teclas) {}

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
  if (varredura == BINARIA_SEM_RAIZ) output   << "binaria_sem_raiz"   << std::endl;
  if (varredura == BINARIA_COM_RAIZ) output   << "binaria_com_raiz"   << std::endl;
  if (varredura == TERNARIA_SEM_RAIZ) output   << "ternaria_sem_raiz"   << std::endl;
  if (varredura == TERNARIA_COM_RAIZ) output   << "ternaria_com_raiz"   << std::endl;
  return output.str();
}

void Teclado::set_metodo_varredura(std::string _metodo)
{
  if (_metodo.compare("sequencial") == 0) varredura = SEQUENCIAL;
  if (_metodo.compare("linha-coluna") == 0) varredura = LINHA_COLUNA;
  if (_metodo.compare("binaria_com_raiz") == 0) varredura = BINARIA_COM_RAIZ;
  if (_metodo.compare("binaria_sem_raiz") == 0) varredura = BINARIA_SEM_RAIZ;
  if (_metodo.compare("ternaria_com_raiz") == 0) varredura = TERNARIA_COM_RAIZ;
  if (_metodo.compare("ternaria_sem_raiz") == 0) varredura = TERNARIA_SEM_RAIZ;
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
            if (teclas[lin+k][col] == letra) return tempo + (k + 1)*temporizador;
          }
        }
      }
    }
  }
  else if (varredura == BINARIA_SEM_RAIZ)
  {
     // teclas vetorizadas tem nosso espaco de busca na ordem desejada
     int left = 0;
     int right = ((int) teclas_vetorizadas.size()) - 1;
     // tamanho do intervalo sera sempre right - left + 1
     while(right - left + 1 > 1){
         // precondicao: a letra sempre ta dentro do intervalo teclas[left...right]
         tempo += temporizador;

         // tem q ver se a tecla ta na primeira metade ou na segunda metade
         // como a gnt define a metade?
         // o tamanho do intervalo eh right - left + 1
         // o intervalo comeca em left
         // logo, a metade sera em left + (right - left + 1) / 2

         int middle = left + (right - left + 1) / 2;

         // operacao que seria so num piscar de olhos, descobrir em qual das
         // metades nossa letra alvo esta
         bool is_on_first_half = false;
         for(int pos = left; pos < middle; ++pos){
             if(teclas_vetorizadas[pos] == letra){
                 is_on_first_half = true; break;
             }
         }

         if(is_on_first_half){
             // left = left;
             right = middle - 1; // chear se isso da ok qnd tam = 2 ou 3
         }else{
             // se tiver na segunda metade, conto o temporizador dnv
             tempo += temporizador;
             left = middle;
             // right = right;
         }
     }
  }
  else if (varredura == TERNARIA_SEM_RAIZ)
  {
     // teclas vetorizadas tem nosso espaco de busca na ordem desejada
     int left = 0;
     int right = ((int) teclas_vetorizadas.size()) - 1;
     // tamanho do intervalo sera sempre right - left + 1
     while(right - left + 1 > 1){
         // precondicao: a letra sempre ta dentro do intervalo teclas[left...right]
         tempo += temporizador;

         // tem q ver se a tecla ta na primeira metade ou na segunda metade
         // como a gnt define a metade?
         // o tamanho do intervalo eh right - left + 1
         // o intervalo comeca em left
         // logo, a metade sera em left + (right - left + 1) / 2

         int size = (right - left + 1);

         if(size == 2){
             if(letra == teclas_vetorizadas[right]){
                 left = right; tempo += temporizador;
             }
             break;
         }

         // se size == 3
         int first_third = left + (size / 3);
         int second_third = first_third + (size / 3);


         // operacao que seria so num piscar de olhos, descobrir em qual das
         // metades nossa letra alvo esta
         bool is_on_first_third = false;
         for(int pos = left; pos < first_third; ++pos){
             if(teclas_vetorizadas[pos] == letra){
                 is_on_first_third = true; break;
             }
         }

         if(is_on_first_third){
             // left = left;
             right = first_third - 1; // chear se isso da ok qnd tam = 2 ou 3
         }else{
             tempo += temporizador;
             bool is_on_second_third = false;
             for(int pos = first_third; pos < second_third; ++pos){
                 if(teclas_vetorizadas[pos] == letra){
                     is_on_second_third = true; break;
                 }
             }

             if(is_on_second_third){
                 left = first_third;
                 right = second_third - 1;
             }else{
                 tempo += temporizador;
                 left = second_third;
             }
         }
     }
  }
  else if (varredura == BINARIA_COM_RAIZ)
  {
     // teclas vetorizadas tem nosso espaco de busca na ordem desejada
     int left = 0;
     int right = ((int) teclas_vetorizadas.size()) - 1;
     // tamanho do intervalo sera sempre right - left + 1
     while(right - left + 1 > 1){
         // precondicao: a letra sempre ta dentro do intervalo teclas[left...right]
         tempo += temporizador;

         int size = (right - left + 1) - 1;

         // tem q ver se a tecla ta na primeira metade ou na segunda metade
         // como a gnt define a metade?

         int middle = (left + 1) + size / 2;

         // operacao que seria so num piscar de olhos, descobrir em qual das
         // metades nossa letra alvo esta

         if(teclas_vetorizadas[left] == letra){
             left = right;
             continue;
         }

         bool is_on_first_half = false;
         for(int pos = left + 1; pos < middle; ++pos){
             if(teclas_vetorizadas[pos] == letra){
                 is_on_first_half = true; break;
             }
         }

         tempo += temporizador;
         if(is_on_first_half){
             // left = left;
             right = middle - 1; // chear se isso da ok qnd tam = 2 ou 3
         }else{
             // se tiver na segunda metade, conto o temporizador dnv
             tempo += temporizador;
             left = middle;
             // right = right;
         }
     }
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
