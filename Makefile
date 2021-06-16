all: compile link run 

compile:
	g++ -Iinclude -c *.cpp 

link:
	g++ *.o -o main -Llib -lsfml-graphics -lsfml-window -lsfml-system

run:
	main