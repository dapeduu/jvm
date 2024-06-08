CC = gcc 
CFLAGS = -m32 -std=c99 -g -Wall
OBJECTS = main.o readers.o classfile.o display.o

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o build/jvm $(OBJECTS) 

main.o: src/main.c src/core/core.h
	$(CC) $(CFLAGS) -c src/main.c

readers.o: src/core/readers.c src/core/core.h
	$(CC) $(CFLAGS) -c src/core/readers.c

classfile.o: src/core/classfile.c src/core/core.h
	$(CC) $(CFLAGS) -c src/core/classfile.c

display.o: src/display.c src/core/core.h src/core/consts.h
	$(CC) $(CFLAGS) -c src/display.c

.PHONY: clean
clean:
	rm main.o readers.o classfile.o display.o