#include <stdlib.h>
/**
 * new_av - allocate new string
 * @str: the input string
 * Return: New allocated str
 */
char *new_av(char *str)
{
	char *new_str = NULL;
	int i = 0, n = 0;

	while (str[i])
	{
		i++;
	}
	i++;
	new_str = malloc(sizeof(char) * i);
	while (n < i)
	{
		new_str[n] = str[n];
		n++;
	}
	return (new_str);
}
