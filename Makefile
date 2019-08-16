headers=  -lncurses -lpanel -lform -lmenu

all: main.c
	touch main.c # make sure you compiling alteast version of .c files! smart, huh?!
	clear
	gcc main.c -o main -Wall -Wextra -pedantic -std=c99
# 	clear 	# COMMENT ME!!!
# 	./main

clean:
	rm *.o