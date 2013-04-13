all:
	gcc -Wall -Wextra -pedantic -std=c99 3.c mylib.c -o 3
clean:
	rm lab3
