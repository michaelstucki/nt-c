all: nt

nt: book.o current_time.o random.o nt.o
	gcc -std=c11 -g book.o current_time.o random.o nt.o -o nt

book.o: book.h book.c
	gcc -std=c11 -c -Wall -g book.c

current_time.o: current_time.h current_time.c
	gcc -std=c11 -c -Wall -g current_time.c

random.o: random.h random.c
	gcc -std=c11 -c -Wall -g random.c

nt.o: book.h nt.c
	gcc -std=c11 -c -Wall -g nt.c

clean:
	rm nt *.o
