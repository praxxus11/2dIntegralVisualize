all: compile link run

compile:
	g++ -Iinclude -IC:/Users/Eric/Documents/cpplibs/includes/SFML/include -c src/*.cpp

link:
	g++ *.o -o main -LC:/Users/Eric/Documents/cpplibs/libraries/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

run: 
	main