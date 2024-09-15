
all: teste

teste: labirinto.o main.o
	gcc -o teste labirinto.o main.o

labirinto.o: labirinto.c labirinto.h
	gcc -c labirinto.c -Wall -Werror -Wextra

main.o: main.c labirinto.h
	gcc -c main.c -Wall -Werror -Wextra

clean:
	rm -rf *.o teste
	
