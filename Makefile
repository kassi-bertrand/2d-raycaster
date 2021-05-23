build:
	gcc -Wall ./src/* -o main -lSDL2 -lm

run:
	./main

clean:
	rm main