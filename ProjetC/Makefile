CC=gcc
CFLAGS=-Wall
EXEC=exe

all: $(EXEC)

parser.o : parser.c parser.h
	$(CC) $(CFLAGS) -g -c parser.c

fondement.o : fondement.c fondement.h
	$(CC) $(CFLAGS) -g -c fondement.c

util.o : util.c util.h parser.h fondement.h 
	$(CC) $(CFLAGS) -g -c util.c

chemin.o : chemin.c chemin.h util.h parser.h fondement.h 
	$(CC) $(CFLAGS) -g -c chemin.c

projet.o : projet.c projet.h fondement.h chemin.h util.h parser.h
	$(CC) $(CFLAGS) -g -c projet.c

exe.o : exe.c projet.h fondement.h chemin.h util.h parser.h
	$(CC) $(CFLAGS) -g -c exe.c

exe : parser.o fondement.o chemin.o util.o projet.o exe.o
	$(CC) $(CFLAGS) -o exe parser.o fondement.o chemin.o util.o projet.o exe.o

clean :
	rm -rf $(EXEC) *.o