/*
** server_core.c for ftp in /home/roman/Documents/dev/PSU_2014_myftp/server_srcs
** 
** Made by grout_r
** Login   <roman@epitech.net>
** 
** Started on  Thu Mar 19 13:30:04 2015 Roman
** Last update Thu Mar 19 14:03:42 2015 grout_r
*/

#include "server.h"

int                     handle_client(int client_fd)
{
  t_packet		packet;

  while (42)
    {
      read(client_fd, &packet, sizeof(packet));
      if (packet.type == CMD_QUIT)
	return (0);
      if (treat(client_fd, packet) == -1)
	return (-1);
    }
}

int		loop(t_server *server)
{
  int                   client_fd;
  struct sockaddr_in    s_in_client;
  socklen_t             s_in_size;
  char			*client_ip;
  int			pid;

  s_in_size = sizeof(s_in_client);
  while (42)
    {
      client_fd = accept(server->socket_fd, (struct sockaddr *)&s_in_client, &s_in_size);
      if (client_fd == -1)
        {
          puts("accept failure");
          return (-1);
        }
      client_ip = inet_ntoa(s_in_client.sin_addr);
      pid = fork ();
      if (pid == 0)
        {
          printf("New connection from IP %s\n", client_ip);
          if (handle_client(client_fd) == -1)
	    return (-1);
          while (42);
          exit (0);
        }
    }
  return (0);
}
