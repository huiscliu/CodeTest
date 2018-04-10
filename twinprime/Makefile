
default: prime_pthread prime_mproc

CFLAGS=-Wall -Wextra -O3 -lm -Wall -Wshadow -Wunreachable-code -Wredundant-decls  \
	   -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
	   -Wdeclaration-after-statement -std=c99

prime_pthread: prime_pthread.o twinprime.o
	gcc -o prime_pthread  prime_pthread.o twinprime.o $(CFLAGS) -lpthread

prime_pthread.o: prime_pthread.c twinprime.h
	gcc -c prime_pthread.c $(CFLAGS)

prime_mproc: prime_mproc.o twinprime.o
	gcc -o prime_mproc  prime_mproc.o twinprime.o $(CFLAGS) -lrt 

prime_mproc.o: prime_mproc.c twinprime.h
	gcc -c prime_mproc.c $(CFLAGS) -D_POSIX_C_SOURCE=200809L

twinprime.o: twinprime.c twinprime.h
	gcc -c twinprime.c $(CFLAGS)

clean:
	rm -fr *.o prime_pthread prime_mproc
