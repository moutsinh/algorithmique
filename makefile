maintri : main.o testtri.o tri.o util.o chrono.o
	gcc -Wall -pedantic -o maintri main.o tri.o testtri.o util.o chrono.o
main.o: main.c testtri.h
	gcc -Wall -pedantic -c main.c
testtri.o : testtri.c testtri.h tri.h util.h chrono.h 
	gcc -Wall -pedantic -c testtri.c
tri.o : tri.c tri.h
	gcc -Wall -pedantic -c tri.c
util.o: util.c util.h
	gcc -Wall -pedantic -c util.c
chrono.o: chrono.c chrono.h
	gcc -Wall -pedantic -c chrono.c
.PHONY : clean
clean :
	-rm *.o maintri