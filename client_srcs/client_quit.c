/*
** client_quit.c for  in /home/roman/Documents/dev/PSU_2014_myftp/client_srcs
** 
** Made by grout_r
** Login   <roman@epitech.net>
** 
** Started on  Thu Mar 19 13:52:39 2015 grout_r
** Last update Thu Mar 19 13:59:43 2015 grout_r
*/

#include "client.h"

int		quit(t_client *client, char **command)
{
  t_packet	packet;
  
  packet.type = CMD_QUIT;
  if (write(client->socket_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  assert(client != NULL);
  assert(command != NULL);
  puts("Quit !");
  return (-1);
}

