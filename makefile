CC = gcc 
CFLAGS = -m32 -std=c99 -g -Wall
OBJECTS = main.o class_loader.o display.o

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o build/jvm $(OBJECTS) 

main.o: src/main.c src/display.h src/class_loader.h 
	$(CC) $(CFLAGS) -c src/main.c

class_loader.o: src/class_loader.c src/core.h src/class_loader.h 
	$(CC) $(CFLAGS) -c src/class_loader.c

display.o: src/display.c src/core.h
	$(CC) $(CFLAGS) -c src/display.c

.PHONY: clean
clean:
	rm main.o class_loader.o display.o build/jvm