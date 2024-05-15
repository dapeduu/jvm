CC = gcc 
CFLAGS = -std=c99 -g -Wall
OBJECTS = main.o

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o build/jvm $(OBJECTS) 

main.o: src/main.c src/dot_class.h
	$(CC) $(CFLAGS) -c src/main.c

.PHONY: clean
clean:
	rm main.o