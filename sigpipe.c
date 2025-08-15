#include <unistd.h>


int true = 1;
int main(void) {

	int b;
	char buff[11];
	while (true) {
	
		b = read(0, buff, 10);
		buff[b] = 0;
		write(1, buff, b);
	}

}
