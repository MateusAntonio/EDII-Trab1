all:
	gcc *.c TADs/*.c -o trab1 -Wall -g -lm -O2 -w

clean:
	rm -f *.o trab1