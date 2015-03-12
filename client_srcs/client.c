
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
