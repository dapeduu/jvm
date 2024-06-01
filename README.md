# JVM

## Como rodar

- Executar o make: `make`
- Executar o projeto: `build/jvm.exe caminho/para/class`

Para executar todos os arquivos de teste no linux:

- Executar o make: `make``
- Executar o comando: `find ./test -type f | xargs -I {} ./build/jvm "{}"`
  - O comando busca todos os arquivos na pasta ./test
  - Depois executa o ./build/jvm passando cada um como argumento