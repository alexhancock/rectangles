CC = g++

app:
	${CC} lib/rectangle.cpp lib/app.cpp -o app

clean:
	rm -f app
