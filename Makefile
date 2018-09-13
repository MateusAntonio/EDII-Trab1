all:
	gcc *.c TADs/*.c -o trab1 -Wall -g -lm

clean:
	rm -f *.o trab1