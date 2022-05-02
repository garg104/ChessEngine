GLIB=$(shell pkg-config --cflags --libs glib-2.0)

all: build

build: 
	g++ -std=c++11 Chess.cpp -Wall $(GLIB) -o Chess.exe
	
clean:
	rm Chess.exe *.txt
