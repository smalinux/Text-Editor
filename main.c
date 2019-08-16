#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

struct termios orig_termios;

// Raw mode functions
void enableRawMode();
void disableRawMode();

// ========================================================================

int main(int argc, char const *argv[])
{
	enableRawMode();

	char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
  	if (iscntrl(c))
  	{
  		printf("%d\n", c);
  	} else {
  		printf("%d (%c)\n", c, c);
  	}
  }
	return 0;
}

// ========================================================================

void enableRawMode()
{
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);
	struct termios raw = orig_termios;

	raw.c_lflag &= ~(ECHO | ICANON);		// turn off echo
	// Turn off canonical mode

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode()
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}