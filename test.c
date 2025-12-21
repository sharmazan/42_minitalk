#include <stdio.h>
#include <stdlib.h>

char	get_bit(int pos, unsigned char c)
{
	if (((1 << pos) & c) > 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	int	num;

	if (ac == 1)
	{
		for (int i = 0; i < 8; i++)
			printf("%d\n", 1 << i);
		exit(0);
	}
	num = atoi(av[1]);
	for (int i = 0; i < 8; i++)
		printf("%d\n", (1 << i) & num);
	printf("*****************************\n");
	for (int i = 0; i < 8; i++)
		printf("%d", get_bit(i, num));
	return (0);
}
