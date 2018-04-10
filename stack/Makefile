
default: stack

stack: stack.o main.o
	gcc -o stack main.o stack.o

stack.o: stack.c stack.h
	gcc -c stack.c -Wall -Wextra -g -O2

main.o: main.c stack.h
	gcc -c main.c -Wall -Wextra -g -O2

clean:
	rm -f stack *.o
