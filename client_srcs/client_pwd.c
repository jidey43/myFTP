/*
** client_pwd.c for ftp in /home/roman/Documents/dev/PSU_2014_myftp/client_srcs
** 
** Made by grout_r
** Login   <roman@epitech.net>
** 
** Started on  Thu Mar 19 13:40:49 2015 grout_r
** Last update Thu Mar 19 13:40:49 2015 grout_r
*/

#include "client.h"

int		pwd(t_client *client, char **command)
{
  t_packet	packet;

  (void)command;
  packet.type = CMD_PWD;
  if (write(client->socket_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  bzero(&packet, sizeof(packet));
  if (read(client->socket_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  if (packet.type == DATA_PWD)
    puts(packet.data);
   return (0);
}
