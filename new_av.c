#include <stdlib.h>
#include <stdio.h>
/**
 * new_av - allocate new string
 * @str: the input string
 * Return: New allocated str
 */
char **new_av(char *str)
{
	char **arrs;
	int i = 0, n = 0, w = 0, e = 1, h = 0;

	while (str[i])
	{
		if (str[i] != 10 && str[i] != 32)
			w = 1;
		if ((str[i] == 10 || str[i] == 32) && w == 1)
		{
			w = 0;
			e++;
		}
		i++;
	}
	arrs = malloc(sizeof(char*) * (e));
	e = 0;
	w = 0;
	for (n = 0; str[n] != '\0'; n++)
	{
		if (str[n] != 10 && str[n] != 32)
			h = 1;
		if ((str[n] == 10 || str[n] == 32) && h == 1)
		{
			arrs[e] = malloc(sizeof(char) * (w + 1));
			arrs[e][w] = 0;
			e++;
			h = 0;
			w = 0;
		}
		if (str[n] != 10 && str[n] != 32)
			w++;
	}
	arrs[e] = NULL;
	n = 0;
	e = 0;
	w = 0;
	h = 0;
	while (n < i)
	{
		if (str[n] != 10 && str[n] != 32)
		{
			arrs[w][e] = str[n];
			e++;
			h = 1;
		}
		if ((str[n] == 10 || str[n] == 32) && h == 1)
		{
			w++;
			h = 0;
			e = 0;
		}
		n++;
	}
	return (arrs);
}
