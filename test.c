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
	printf("\n*****************************\n");
	for (int i = 0; i < 8; i++)
		printf("%d", get_bit(i, num));
	printf("*****************************\n");
	printf("1 << 0 = %d, 1 << 2 = %d, 1 | 1 << 2 = %d\n", 1 << 0, 1 << 2,
		1 | 1 << 2);
	return (0);
}
