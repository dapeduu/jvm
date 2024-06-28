# Máquina Virtual Java - Disciplina de Software Básico

## Introdução

Este documento descreve o trabalho da Máquina Virtual Java (JVM) desenvolvida para a disciplina de Software Básico. A JVM é responsável por interpretar e executar arquivos `.class` gerados a partir de códigos Java.

## Grupo:

- Bruno Fernandes Teixeira  
  Avaliação do grupo: 10  
  * 
- Maria Clara Mendes Gonçalves  
  Avaliação do grupo: 10  
  *
- Pedro Henrique Dos Santos  
  Avaliação do grupo: 10  
  *

## Estrutura

Diagrama lógico:

## Funcionamento

### Instalar dependências

```bash
sudo apt update
sudo apt install build-essential cppcheck gcc-multilib
```

### Como rodar

```bash
# Para rodar um arquivo especifico
make
./build/jvm.exe caminho/para/class

# Para rodar todos os arquivos
# - O comando busca todos os arquivos na pasta ./test
# - Depois executa o ./build/jvm passando cada um como argumento

make
find ./test -type f | xargs -I {} ./build/jvm "{}"

# Para leitor e exibidor: (a partir do diretório JVM)
make && ./build/jvm -r test/nome_da_classe.class

# Para interpretador: (a partir do diretório JVM)
make && ./build/jvm -e test/nome_da_classe

```

### Conteúdos úteis

- [Java Virtual Machine Architecture Explained for Beginners](https://www.youtube.com/watch?v=jnpuRvRdTgI)
- [Java Virtual Machine (JVM) Architecture](https://docs.oracle.com/javase/specs/jvms/se8/html/index.html)

