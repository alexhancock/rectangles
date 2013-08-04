CC = g++

app:
	${CC} -framework Cocoa -framework GLUT -lGLEW -framework OpenGL lib/rectangle.cpp lib/app.cpp -o app
clean:
	rm -f app