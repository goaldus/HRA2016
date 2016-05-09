#
# Projekt: ICP - HRA2016
# Autori:  Vilem Jelen,	 Ondrej Molnar
# Login:   xjelen09, 	 xmolna05
# Datum:   8.5.2016
#

CC = g++
CFLAGS = -Wall -Wextra -O2 -std=c++0x -s -pedantic
LOGIN =  xjelen09-xmolna05
CLI = src/ai.cpp src/cli.cpp src/core.cpp src/gameboard.cpp src/interface.cpp src/save.cpp
FILES = Makefile README.txt src/ai.cpp src/cli.cpp src/core.cpp src/gameboard.cpp src/interface.cpp src/save.cpp examples/

all: cli copysaves

cli:
	   $(CC) $(CFLAGS) $(CLI) -o HRA2016-cli

clean:
	rm -f HRA2016-cli
	rm doc/* -rf
	rm -rf $(LOGIN).zip
	rm src/Makefile -rf
	rm saves -rf

pack:
	zip -r $(LOGIN) $(FILES)

run: all
	./HRA2016-cli

doxygen:
	-mkdir doc
	doxygen src/Doxyfile

copysaves:
	-mkdir -p saves
	cp examples/* saves



