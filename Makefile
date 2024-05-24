CC = gcc
CFLAGS = -Wno-unused-result -g -O3
LIBS = -lhunspell
DEPS = utils/hashtable.h utils/utils.h
OBJ = solver.o utils/hashtable.o utils/utils.o

all: solver

solver: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

solver.o: solver.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

hashtable.o: hashtable.c hashtable.h
	$(CC) $(CFLAGS) -c -o $@ $<

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o solver