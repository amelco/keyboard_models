#ifndef TECLADO_H
#define TECLADO_H

#include <vector>
#include <string>

class Teclado
{
private:
  char null_char = 'X';
  enum metodo {LINHA_COLUNA, SEQUENCIAL, BINARIA};

public:
  // -=== atributos ===-
  int num_linhas;
  int num_colunas;
  metodo varredura;
  int temporizador;
  std::vector<std::string> teclas;

  // -=== construtores / destrutor ===-
  Teclado();
  Teclado(std::vector<std::string> teclas);
  ~Teclado();

  // -===  métodos ===-
  std::string print_propriedades();

  // metodos podem ser: "sequencial" ou "linha-coluna"
  void set_metodo_varredura(std::string _metodo);
  float tempo_digitacao_letra(char letra);
  float tempo_digitacao_frase(std::string frase);

  // le arquivo contendo layout do teclado: armazena-o em teclas e seta num_colunas e num_linhas
  void le_arquivo_layout(std::string filename);

  // padrão do layout:
  // cada linha do arquivo é uma linha do teclado
  // cada caractere da linha é uma tecla do teclado
  // obs.: todas as linhas DEVEM ter a mesma quantidade de carcateres
  // use o caractere X para indicar teclas não existentes para aquela linha
  // o uso de X implica que a tecla anterior irá ocupar o espaço da tecla X no frontend
  void set_layout(std::vector<std::string> layout);
};

#endif // TECLADO_H
