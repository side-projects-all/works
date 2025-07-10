#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	struct termios old, raw;
	tcgetattr(0, &old);
	raw = old;
	raw.c_lflag &= ~(ICANON | ECHO);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &raw);
	printf("Type keys (q to quit): \n");

	while (1) {
		char c;
		if (read(0, &c, 1) == 1) {
			if (c == 'q') {
				break;
			}

			write(1, &c, 1);
		}
	}

	tcsetattr(0, TCSANOW, &old);
	printf("\nBye!\n");
	return 0;
}
