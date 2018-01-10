CC=gcc
CFLAGS=-I"C:\SDL2\include\SDL2\"
LDFLAGS=-L"C:\SDL2\lib" -lmingw32 -lSDL2main -lSDL2 -lopengl32

main.exe:
	$(CC) $(CFLAGS) -o main.exe main.c $(LDFLAGS)

run: main.exe
	main.exe