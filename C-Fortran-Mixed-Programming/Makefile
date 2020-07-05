
default: main

main: main.o vec-sum.o
	gcc -O3 -fopenmp -o main main.o vec-sum.o

main.o: main.c
	gcc -c -O3 -fopenmp -Wall -Wextra main.c

vec-sum.o: vec-sum.for
	gfortran -c -O3 -fopenmp -Wall -Wextra vec-sum.for

clean:
	rm main vec-sum.o main.o -f 

