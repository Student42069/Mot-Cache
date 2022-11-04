CC = gcc
OPTIONS = -Wall -Wextra -std=c11
EXE = motcache
FILENAME = motcache

motcache: $(FILENAME).c $(FILENAME).h
	$(CC) $(OPTIONS) $(FILENAME).c -o $(EXE)

test: motcache
	bats check.bats

compile: $(FILENAME).c $(FILENAME).h
	$(CC) $(OPTIONS) -c $(FILENAME).c

link: compile
	$(CC) $(FILENAME).o -o $(EXE)

clean:
	rm *.o -f
	rm $(EXE) -f
