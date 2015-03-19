/*
** server_pwd.c for ftp in /home/roman/Documents/dev/PSU_2014_myftp/server_srcs
** 
** Made by grout_r
** Login   <roman@epitech.net>
** 
** Started on  Thu Mar 19 13:28:29 2015 Roman
** Last update Thu Mar 19 13:50:42 2015 grout_r
*/

#include "server.h"

int		pwd(int client_fd, t_packet packet)
{
  t_packet	packet_s;
  char		*cwd;

  (void)packet;
  cwd = getcwd(0, 0);
  packet_s.type = DATA_PWD;
  if (cwd == NULL)
    packet_s.type = ABORT;
  else
    memcpy(packet_s.data, cwd, strlen(cwd));
  if (write(client_fd, &packet_s, sizeof(packet_s)) == -1)
    return (-1);
  return (0);
}
