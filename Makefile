# Victor Picussa - GRR20163068

CFLAGS = -O3
CC = g++
FILES = src/main.cpp src/movements.cpp src/tabuleiro.c
HEADERS = hds/movements.h hds/tabuleiro.h
OUT = fox_goose

all: packages fox_goose clean

fox_goose: fox_goose.o
	$(CC) $(FILES) $(HEADERS) -o $(OUT) $(CFLAGS) -l cgraph

fox_goose.o:
	$(CC) $(FILES) $(HEADERS) -o fox_goose.o $(CFLAGS) -l cgraph

packages:
	sudo apt-get install libgraphviz-dev -y

clean:
	rm *.o

purge:
	rm fox_goose
