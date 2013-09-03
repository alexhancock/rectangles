CC = g++

app:
	${CC} -framework Cocoa -framework GLUT -framework OpenGL -lGLEW lib/util/shaders.cpp lib/util/pipeline.cpp lib/app.cpp -o app
clean:
	rm -f app
br:
	make clean && make && ./app
