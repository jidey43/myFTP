/*
** client_core.c for ftp in /home/roman/Documents/dev/PSU_2014_myftp/client_srcs
** 
** Made by grout_r
** Login   <roman@epitech.net>
** 
** Started on  Thu Mar 19 13:41:41 2015 grout_r
** Last update Thu Mar 19 13:41:42 2015 grout_r
*/

#include "client.h"

int		treat(t_client *client, char **command)
{
  if (execute(client, command) == -1)
    return (-1);
  return (0);
}

void		dump_command(char **command)
{
  int		i;
  
  i = 0;
  while (command[i] != NULL)
    printf("%s ", command[i++]);
  printf("\n");
}

int		loop(t_client *client)
{
  char		**command;
  char		*str;
  int		quit;
  char		c;

  command = NULL;
  str = malloc(sizeof(char *) * 1024);
  quit = 0;
  c = 0;
  while (quit != 1)
    {
      write(1, "$> ", strlen("$> "));
      while (c != '\n')
	{
	  str = malloc(sizeof(char) * 1024);
	  if (scanf("%s", str) == EOF)
	    return (-1);
	  command = add_word(command, str);
	  c = getchar();
	}
      if (treat(client, command) == -1)
	return (-1);
      //free each element !
      free(command);
      command = NULL;
      c = 0;
    }
  return (0);
}
