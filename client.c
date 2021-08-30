#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

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

void print_binary(int *b)
{
	int i = 0;

	while (i < 8)
	{
		printf("%d ", b[i]);
		i++;
	}
	printf("\n");
}

void send_binary(int *b, int pid)
{
	int i = 0;

	while (i < 8)
	{
		if (b[i] == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		i++;
	}
}

int main(int ac, char **av)
{
	int pid;
	int b[8];
	int len;
	int i;

	if (ac != 3)
	{
		write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
		return (1);
	}
	pid = atoi(av[1]);
	if (pid <= 1)
	{
		write(2, "Error: wrong pid\n", strlen("Error: wrong pid\n"));
		return (1);
	}

	i = 0;
	printf("pid: %d\n", pid);
	len = strlen(av[2]);
	convert_char_to_binary(b, len);
	while (i < strlen(av[2]))
	{
		b[7] = 0;
		convert_char_to_binary(b, av[2][i]);
		i++;
		if (i == len)
			b[7] = 1;
		print_binary(b);
		send_binary(b, pid);
	}
	//sleep(1);
	//kill(pid, SIGUSR1);
	return (0);
}
