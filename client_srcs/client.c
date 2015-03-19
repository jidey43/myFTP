/*
** client.c for ftp in /home/roman/Documents/dev/PSU_2014_myftp/client_srcs
** 
** Made by grout_r
** Login   <roman@epitech.net>
** 
** Started on  Thu Mar 19 13:27:50 2015 grout_r
** Last update Thu Mar 19 13:41:59 2015 grout_r
*/

#include "client.h"

int		main(int ac, char **av)
{
  t_client	client;

  if (init_client(ac, av, &client) == -1)
    return (-1);
  if (connect(client.socket_fd, (struct sockaddr *)&(client.s_in), sizeof(client.s_in)) == -1)
    {
      puts("connect failure");
      close (client.socket_fd);
      return (-1);
    } 
  if (loop(&client) == -1)
    return (-1);

  if (close(client.socket_fd) == -1)
    {
      puts("Error when closing socket");
    }
  return (0);
}
