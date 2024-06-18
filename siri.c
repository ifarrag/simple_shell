#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 * main - shell
 * @ac: number of command line items
 * @av: pointer to command line arguments
 * @env: strings of environmet variables
 * Return: 0
 */
int main(int ac, char **av __attribute__((unused)), char **env)
{
	char str[512];
	int gtline = 0;
	int pid = 0;
	char *arrs[] = {NULL, NULL};

	while (1)
	{
		write(STDOUT_FILENO, "[==>", 4);
		gtline = read(STDIN_FILENO, str, 512);
		if (gtline <= 0 || str[0] == '\n' || ac > 2)
		{
			if (gtline == 0)
				write(STDOUT_FILENO, "\n", 1);
			write(STDOUT_FILENO, "./siri: No such file or directory\n", 34);
		}
		else
		{
			str[gtline - 1] = '\0';
			arrs[0] = new_av(str);
			if (access(arrs[0], X_OK) == -1)
			{
				write(STDOUT_FILENO, "./siri: No such file or directory\n", 34);
			}
			else
			{
				pid = fork();
				if (pid == 0)
				{
					execve(arrs[0], arrs, env);
				}
				else
				{
					wait(NULL);
				}
			}
		}
		if (ac == 1)
			break;
	}
	return (0);
}
