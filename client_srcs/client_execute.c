/*
** client_execute.c for ftp in /home/roman/Documents/dev/PSU_2014_myftp/client_srcs
** 
** Made by grout_r
** Login   <roman@epitech.net>
** 
** Started on  Thu Mar 19 13:41:37 2015 grout_r
** Last update Thu Mar 19 14:00:06 2015 grout_r
*/

#include "client.h"

int		execute(t_client * client, char **command)
{
  int		i;
  
  i = 0;
  while (client->db[i].str != NULL && strcmp(client->db[i].str, command[0]) != 0)
    i++;
  if (client->db[i].str == NULL)
    {
      printf("command '%s' not found.\n", command[0]);
      return (0);
    }
  return (client->db[i].funcptr(client, command));
}
