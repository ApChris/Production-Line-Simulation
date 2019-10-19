CC = gcc # Compiler

main: main.o semaphores.o sharedMemory.o components_functions.o
	$(CC) -o main main.o semaphores.o sharedMemory.o components_functions.o

main.o: main.c
	$(CC) -c main.c

semaphores.o: semaphores.c
	$(CC) -c semaphores.c

sharedMemory.o: sharedMemory.c	
	$(CC) -c sharedMemory.c

components_functions.o: components_functions.c
	$(CC) -c components_functions.c

.Phony: clean

clean:
	rm -r main main.o semaphores.o sharedMemory.o components_functions.o