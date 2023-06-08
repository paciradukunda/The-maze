CC = gcc
CFLAGS = -Wall -Wextra

all: main

run:
	main.exe

main: main.o
	$(CC) $(CFLAGS) -o main main.o -L./lib -lmingw32 -lSDL2main -lSDL2 -mwindows

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	del main.exe main.o