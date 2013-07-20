CC = g++

app:
	${CC} -framework Cocoa -framework GLUT -framework OpenGL -arch i386 lib/rectangle.cpp lib/app.cpp -o app
clean:
	rm -f app