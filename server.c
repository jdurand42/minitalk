#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

// int c;

void convert_char_to_binary(int *b, int c)
{
	unsigned int base_len;
	int len;
	unsigned int quotient;

	base_len = 2;
	len = 7;

	len -= 1;
	while (len >= 0)
	{
		//printf("%d\n", len);
		b[len] = c % base_len;
		c /= base_len;
		len--;
	}
}

void handle_sig(int param)
{
	//
	static int byte_len = 8;
	static int c = 0;

	if (byte_len > 1)
	{
		c = c << 1;
		if (param == SIGUSR1)
			;
		else
			c += 1;
	}

	byte_len--;
	if (byte_len == 0)
	{
		write(1, &c, 1);
		if (param == SIGUSR2)
			write(1, "\n", 1);
		c = 0;
		byte_len = 8;

	}

}

int main()
{
	pid_t pid;
	int b[7];

	//c = 0;
	// int b[7];
	//int i;

	pid = getpid();
	signal(SIGUSR1, handle_sig);
	signal(SIGUSR2, handle_sig);
	printf("PID: %d\n", pid);

	while (1);

	return (0);
}
