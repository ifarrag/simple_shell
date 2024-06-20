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
	char **arrs;
	int gtline = 0;
	int pid = 0, w = 0;
	int access_f = 0;
	char *new_arr[] = {NULL, NULL};

	while (1)
	{
		if(isatty(STDIN_FILENO) != 0)
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
			arrs = new_av(str);
			if (access(arrs[0], X_OK) ==  -1)
			{
				write(STDOUT_FILENO, "./siri: No such file_or_directory\n", 34);
			}
			else
			{
				new_arr[0] = arrs[0];
exe_again:
				pid = fork();
				if (pid == 0)
				{
					execve(new_arr[0], new_arr, env);
				}
				else
				{
					wait(NULL);
					w++;
					if (arrs[w] != NULL)
					{
						new_arr[0] = arrs[w];
						goto exe_again;
					}
				}
			}
			w = 0;
			while (arrs[w] != NULL)
			{
				free(arrs[w]);
				w++;
			}
			free(arrs);
		}
	}
	return (0);
}
