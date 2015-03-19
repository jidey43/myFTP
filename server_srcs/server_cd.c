/*
** server_cd.c for ftp in /home/roman/Documents/dev/PSU_2014_myftp/server_srcs
** 
** Made by grout_r
** Login   <roman@epitech.net>
** 
** Started on  Thu Mar 19 13:30:18 2015 Roman
** Last update Thu Mar 19 13:50:18 2015 grout_r
*/

#include "server.h"

int		send_status(int client_fd, int status)
{
  t_packet	packet;

  packet.type = status;
  if (write(client_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  return (0);
}

int		cd(int client_fd, t_packet packet)
{
  static ino_t	rootinode = 0;
  struct stat	buff;

  (void)client_fd;
  if (rootinode == 0)
    {
      stat(".", &buff);
      rootinode = buff.st_ino;
    }
  bzero(&buff, sizeof(buff));
  stat(packet.data, &buff);
  if (buff.st_ino < rootinode)
    return (send_status(client_fd, ABORT));
  if (chdir(packet.data) == -1)
    return (send_status(client_fd, ABORT));
  return (send_status(client_fd, READY));
}
