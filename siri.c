#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
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
	char *svr;
	int gtline = 0;
	int pid = 0, w = 0, isfile = 0;
	char *new_arr[] = {NULL, NULL};
	struct stat st;

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
			str[gtline] = '\0';
			arrs = new_av(str, env);
			w = 0;
			while (arrs[w] != NULL)
			{
				if (arrs[w + 1] != NULL)
					isfile = stat(arrs[w + 1], &st);
				if (access(arrs[w], X_OK) ==  -1)
				{
					if (w == 0)
					{
					write(STDOUT_FILENO, "./siri: No such file_or_directory\n", 34);
					}
				}
				else
				{
					pid = fork();
					if (pid == 0)
					{
						if (isfile == 0)
						{
							if (S_ISREG(st.st_mode))
							{
								new_arr[0] = arrs[w];
								execve(new_arr[0], new_arr, env);
							}
							else
							{
								execve(arrs[w], arrs, env);
							}
						}
						else
						{
							execve(arrs[w], arrs, env);
						}
					}
					else
					{
						wait(NULL);
						if (arrs[w + 1] != NULL && isfile == 0 && str != NULL)
							if (!S_ISREG(st.st_mode))
								break;
					}
				}
				w++;
			}
			w = 0;
			while (arrs[w] != NULL)
			{
				free(arrs[w]);
				w++;
			}
			free(arrs);
		}
		if (isatty(STDIN_FILENO) == 0)
			break;
	}
	return (0);
}
