/*
** client_command.c for ftp in /home/roman/Documents/dev/PSU_2014_myftp/client_srcs
** 
** Made by grout_r
** Login   <roman@epitech.net>
** 
** Started on  Thu Mar 19 13:41:46 2015 grout_r
** Last update Thu Mar 19 13:41:47 2015 grout_r
*/

#include "client.h"

int		size_of_command(char **command)
{
  int		i;

  i = 0;
  if (command == NULL)
    return (0);
  while (command[i++] != NULL);
  return (i);
}

char		**add_word(char **command, char *str)
{
  int		i;
  
  if (command == NULL)
    {
      command = malloc(sizeof(char *) *  2);
      command[0] = str;
      command[1] = NULL;
      return (command);
    }
  i = size_of_command(command);
  command = realloc(command, sizeof(char *) * ( size_of_command(command) + 2));
  command[i - 1] = str;
  command[i] = NULL; 
  return (command);
}
