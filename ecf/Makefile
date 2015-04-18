
shellex: shellex.o csapp.o
	gcc -o shellex shellex.o csapp.o -lpthread 

shellex.o: shellex.c
	gcc -c shellex.c

csapp.o: csapp.c
	gcc -c csapp.c

clean:
	rm shellex.o csapp.o shellex
