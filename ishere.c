#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/**
 * ishere - search the path
 * @env: Environment vars
 * @str: pointer to string
 * Return: string or NULL
 */
char *ishere(char *str, char **env)
{
	int i = 0, ii = 0, n = 0, m = 0, e = 0;
	char *s = "PATH=";
	char *arr;

	while (env[i])
	{
		ii = 0;
		for (m = 0; env[i][ii] == s[m];)
		{
			m++;
			ii++;
		}
		if (s[m] == '\0')
			break;
		i++;
	}
	n = ii;
	while (env[i][ii])
	{
		if (env[i][ii] == ':' && env[i][ii + 1] != (':'))
		{
			e = 0;
			m = 0;
			while (env[i][n] == ':')
				n++;
			arr = malloc(sizeof(char) * (ii - n + strlen(str) + 2));
			while (n != ii)
			{
				arr[m] = env[i][n];
				n++;
				m++;
			}
			arr[m] = '/';
			m++;
			while (str[e])
			{
				arr[m] = str[e];
				m++;
				e++;
			}
			arr[m] = '\0';
			if (access(arr, X_OK) == 0)
			{
				return (arr);
			}
			free(arr);
		}
		ii++;
	}
	return (NULL);
}
