# Victor Picussa - GRR20163068

CFLAGS = -O3 -Wno-unused-result
LDLIBS = -l cgraph -l hiredis -l readline
CC = gcc
FILES = src/fox_goose.c src/movements.c src/tabuleiro.c
HEADERS = hds/fox_goose.h hds/tabuleiro.h
OUT = fox_goose

all: fox_goose clean

fox_goose: fox_goose.o
	$(CC) $(FILES) $(HEADERS) -o $(OUT) $(CFLAGS) $(LDLIBS)

fox_goose.o:
	$(CC) $(FILES) $(HEADERS) -o fox_goose.o $(CFLAGS) $(LDLIBS)

packages:
	sudo apt-get install libgraphviz-dev -y

clean:
	rm *.o

purge:
	rm fox_goose
