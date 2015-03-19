/*
** client_ls.c for ftp in /home/roman/Documents/dev/PSU_2014_myftp/client_srcs
** 
** Made by grout_r
** Login   <roman@epitech.net>
** 
** Started on  Thu Mar 19 13:41:15 2015 grout_r
** Last update Thu Mar 19 13:41:15 2015 grout_r
*/

#include "client.h"

int		ls(t_client *client, char **command)
{
  t_packet	packet;

  (void)command;
  packet.type  = CMD_LS;
  write(client->socket_fd, &packet, sizeof(packet));
  bzero(&packet, sizeof(packet));
  while (1)
    {
      if (read(client->socket_fd, &packet, sizeof(packet)) == -1)
	return (-1);
      if (packet.type == DATA_LS)
	puts(packet.data);
      if (packet.type == LAST_ONE)
	return (0);
      bzero(&packet, sizeof(packet));
      packet.type = READY;
      if (write(client->socket_fd, &packet, sizeof(packet)) == -1)
	return (-1);
    }
  return (0);
}
