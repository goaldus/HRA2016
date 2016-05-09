#
# Projekt: ICP - HRA2016
# Autori:  Vilem Jelen,	 Ondrej Molnar
# Login:   xjelen09, 	 xmolna05
# Datum:   8.5.2016
#

export PATH := /usr/local/share/Qt-5.5.1/5.5/gcc_64/bin:$(PATH)
export LD_LIBRARY_PATH := /usr/local/share/Qt-5.5.1/5.5/gcc_64/lib:$(LD_LIBRARY_PATH)

CC = g++
CFLAGS = -Wall -Wextra -O2 -std=c++0x -s -pedantic
LOGIN =  xjelen09-xmolna05
CLI = src/ai.cpp src/cli.cpp src/core.cpp src/gameboard.cpp src/interface.cpp src/save.cpp
FILES = Makefile README.txt src/ai.cpp src/cli.cpp src/core.cpp src/gameboard.cpp src/interface.cpp src/save.cpp examples/ doc/

all: cli copysaves gui

cli:
	   $(CC) $(CFLAGS) $(CLI) -o HRA2016-cli

gui:
	@ cd src && qmake -o Makefile && make
	cp ./src/HRA2016 ./

clean:
	rm -f HRA2016-cli
	rm doc/* -rf
	rm -rf $(LOGIN).zip
	rm src/Makefile -rf
	rm saves -rf
	rm src/*.o
	rm src/HRA2016

pack:
	zip -r $(LOGIN) $(FILES)

run: all
	./HRA2016-cli
	./HRA2016

doxygen:
	-mkdir doc
	doxygen src/Doxyfile

copysaves:
	
	-mkdir -p saves
	cp examples/* saves
	



