/*
** server_init.c for ftp in /home/roman/Documents/dev/PSU_2014_myftp/server_srcs
** 
** Made by grout_r
** Login   <roman@epitech.net>
** 
** Started on  Thu Mar 19 13:29:32 2015 Roman
** Last update Thu Mar 19 13:38:44 2015 Roman
*/

#include "server.h"

int			get_port(int ac, char **av)
{
  int			port;

  if (ac != 2)
    {
      puts("Usage : ./serveur port");
      return (-1);
    }
  port = atoi(av[1]);
  if (port < 0 || port >  65535)
    {
      puts("Port have to be between 0 and 65535");
      return (-1);
    }
  return (port);
}

void			init_sockaddr(t_server *server)
{
  server->s_in.sin_family = AF_INET;
  server->s_in.sin_port = htons(server->port);
  server->s_in.sin_addr.s_addr = INADDR_ANY;
}

int			init_server(int ac, char **av, t_server *server)
{
  struct protoent	*pe;

  if ((server->port = get_port(ac, av)) == -1)
    return (-1);
  pe = getprotobyname("TCP");
  if (pe == NULL)
    return (-1);
  init_sockaddr(server);
  if ((server->socket_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
      return (-1);
  if (bind(server->socket_fd, (const struct sockaddr *)&(server->s_in), sizeof(server->s_in)) == -1)
    {
      close(server->socket_fd);
      return (-1);
    }  
  if (listen(server->socket_fd, 42) == -1)
    {
      close(server->socket_fd);
      return (-1);
    }
  return (0);
}
