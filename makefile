all: randfile.o
	gcc randfile.o

random.o: randfile.c
	gcc -c randfile.c

run:
	./a.out

clean:
	rm *.o
