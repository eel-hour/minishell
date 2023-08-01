#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int x = 5;
	write(1, "da\n", 3);
	x = x >> 8;
	write(1, &x, sizeof(int));
	write(1, "\n", 1);
}

int fd[2] 