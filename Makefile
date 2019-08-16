headers= 

all: main.c
	touch main.c # make sure you compiling latest version of .c files! smart, huh?!
	clear
	gcc main.c -o main -Wall -Wextra -pedantic -std=c99
	./main
	# clear 	# COMMENT ME!!!

clean:
	rm *.o