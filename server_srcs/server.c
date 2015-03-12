
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
