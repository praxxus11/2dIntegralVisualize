name=main

all: compile link run clean

compile:
	g++ -Iinclude -c *.cpp 

link:
	g++ *.o -o ${name} -Llib -lsfml-graphics -lsfml-window -lsfml-system

run:
	${name}

clean:
	echo Success
	