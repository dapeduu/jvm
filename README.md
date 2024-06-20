# JVM

## Instalar dependencias

```bash
sudo apt update
sudo apt install build-essential cppcheck gcc-multilib
```

## Como rodar

```bash
# Para rodar um arquivo especifico
make
./build/jvm.exe caminho/para/class

# Para rodar todos os arquivos
# - O comando busca todos os arquivos na pasta ./test
# - Depois executa o ./build/jvm passando cada um como argumento

make
find ./test -type f | xargs -I {} ./build/jvm "{}"

```