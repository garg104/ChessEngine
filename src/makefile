GLIB=$(shell pkg-config --cflags --libs glib-2.0)

all: build

build: 
	g++ Chess.cpp -Wall -O1 $(GLIB) -o chess.out
	
clean:
	rm chess.out -f
