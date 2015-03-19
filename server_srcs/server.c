/*
** server.c for ftp in /home/roman/Documents/dev/PSU_2014_myftp/server_srcs
** 
** Made by grout_r
** Login   <roman@epitech.net>
** 
** Started on  Thu Mar 19 13:30:22 2015 Roman
** Last update Thu Mar 19 13:39:52 2015 grout_r
*/

#include "server.h"

int		main(int ac, char **av)
{
  t_server	server;

  if (init_server(ac, av, &server) == -1)
    return (-1);
  if (loop(&server) == -1)
    return (-1);
  return (0);
}
