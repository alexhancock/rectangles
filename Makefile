CC = g++

app:
	${CC} -I /usr/local/include -L/usr/local/lib -framework Cocoa -framework GLUT -framework OpenGL -lGLEW lib/util/shaders.cpp lib/util/pipeline.cpp lib/app.cpp -o app
clean:
	rm -f app
br:
	make clean && make && ./app
