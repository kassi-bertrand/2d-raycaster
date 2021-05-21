build:
	gcc -Wall ./src/* -o main -lSDL2

run:
	./main

clean:
	rm main