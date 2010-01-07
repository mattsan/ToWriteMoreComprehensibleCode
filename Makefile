# for Mac OS X

moreComprehensible: *.cpp *.h
	g++ -framework OpenGL -framework GLUT -framework Foundation -ansi -Wall -o moreComprehensible *.cpp 