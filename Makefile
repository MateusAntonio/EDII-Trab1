all:
	gcc *.c TADs/*.c -o trab1 -Wall -g

clean:
	rm -f *.o trab1