CC = gcc
OPTIONS = -Wall -Wextra -std=c11
EXE = motcache

motcache: motcache.c motcache.h
	$(CC) $(OPTIONS) motcache.c -o $(EXE)

test: motcache
	bats check.bats

compile:
	$(CC) $(OPTIONS) -c motcache.c

link: compile
	$(CC) motcache.o -o $(EXE)

clean:
	rm *.o -f
	rm $(EXE) -f
