CC = gcc -std=c99 -g -Wall
SRC_FILES = src/main.c
EXEC = main
OUTPUT = jvm

$(EXEC) : $(SRC_FILES)
	$(CC) $(SRC_FILES) -o build/$(OUTPUT)

.PHONY: clean
clean:
	rm main