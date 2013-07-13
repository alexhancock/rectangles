CC = g++

app: rectangle.cpp app.cpp
	${CC} rectangle.cpp app.cpp -o app

clean:
	rm -f app
