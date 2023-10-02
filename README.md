# Cifra-de-Vigenere
Programa com as funcionalidades de cifragem, decifragem e quebra da Cifra de VIgenere. Para cifragem e decifragem, um aqrquivo de entrada será lido com a mensagem em um formato e um arquivo de saída será criado com a mensagem no formato oposto. Para o modo de quebra de cifra é utilizada a análise de frequência e a análise de diferença média entre as distribuições de letras geradas pelas possíveis variações da mensagem cifrada e a distrubuição padrão de letras da linguagem escolhida.   

## Plataforma utilizada
20.04.2 LTS (Focal Fossa) (WSL)


## Funções:
- c : Cifra um arquivo de texto com uma senha especificada
- d : Decifra um arquivo de texto senha especificada
- q : Quebra a criptografia de arquivo de texto com a linguagem esperada (argumentos 'pt' ou 'en')



## Compilação e Execução
Para a compilação é necessário ter os arquivos main.c
source.c e header.h em uma mesmo diretório.

Comandos:
```
gcc -c source.c
```
```
gcc main.c source.o -lm
```

### Execução Linux:
```
./a.out <modo> <nome_arquivo_entrada> <nome_arquivo_saida> <chave/idioma>
```
### Execução Windows:
```
./a.exe <modo> <nome_arquivo_entrada> <nome_arquivo_saida> <chave/idioma>
```

substitua <modo> por "c", "d" ou "q". <br>
Digite os parâmetros sem <>. <br>

### Exemplo:
1. em uma pasta com o arquivo plaintext.txt

```
gcc -c source.c

gcc main.c source.o -lm

./a.out c plaintext.txt cyphertext.txt examplekey

./a.out q cyphertext.txt broken_plaintext.txt en

```

2. em uma pasta com o arquivo plaintext.txt

```
gcc -c source.c

gcc main.c source.o -lm

./a.out c plaintext.txt cyphertext.txt examplekey

./a.out q cyphertext.txt decypher_plaintext.txt examplekey

```

## Bibliotecas
- stdio.h
- stdlib.h
- string.h
- math.h






