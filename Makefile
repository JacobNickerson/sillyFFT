build:
	g++ src/*.cpp -o test -lfftw3 -lm -lsfml-graphics -lsfml-window -lsfml-system  -std=c++11 

build-run:
	g++ src/*.cpp -o test -lfftw3 -lm -lsfml-graphics -lsfml-window -lsfml-system  -std=c++11 
	./test
