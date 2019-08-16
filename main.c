/** Sections
==============
- Include
- Data
- Functions
	> Terminal
- Init

*/


/*** Include ***/
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>

/*** Data ***/
struct termios orig_termios;

/*** Terminal ***/
// Raw mode functions
void enableRawMode();
void disableRawMode();
// Error handling
void die(const char *s);


/*** Init ***/
int main(int argc, char const *argv[])
{
	enableRawMode();

	char c;
	while (1) {
		
		c = '\0';

		if(read( STDIN_FILENO, &c, 1 ) == -1 && errno != EAGAIN)
			die("read");

		if (iscntrl(c))
		{
			printf("%d\r\n", c);
		} else {
			printf("%d (%c)\r\n", c, c);
		}
		if (c == 'q')	break;

	}
	return 0;
}

void enableRawMode()
{
	if(tcgetattr(STDIN_FILENO, &orig_termios) == -1)
		die("tcgetattr");
	atexit(disableRawMode);
	
	struct termios raw = orig_termios;

	raw.c_iflag 			&= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag 			&= ~(OPOST);
	raw.c_cflag 			|= (CS8);
	raw.c_lflag 			&= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] 		= 0;
	raw.c_cc[VTIME] 	= 1;

	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		die("tcsetattr");
}

void disableRawMode()
{
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
		die("tcsetattr");
}


/** Error Handling
=========================*/
void die(const char *s)
{
	perror(s);
	exit(1);
}










