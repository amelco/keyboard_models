# Test Keyboard layouts

Programa feito para testar diferentes tipos de layout de teclados para diferentes métodos de escaneamento.

Os layouts de teclados são definidos por arquivos de texto e carregados no arquivo de configuração do programa `app.conf`.

O teste é feito simulando a utilização do teclado na digitação das frases listadas no arquivode configuração `app.conf`.



## Compilando e executando o programa

```
$ cd build
$ cmake ..
$ make
$ ./app
```


## TODO

[ ] Adicionar novo sistema de varredura: busca binária (idéia de Paulo)  
[ ] Refatoração para separar os métodos de varredura em uma classe isolada
