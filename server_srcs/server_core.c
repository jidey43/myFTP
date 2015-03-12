
#include "server.h"

int                     handle_client(int client_fd)
{
  t_packet		packet;

  while (42)
    {
      puts("Connection etablished, waiting for request ...");
      read(client_fd, &packet, sizeof(packet));
      printf("%d\n", packet.type);
      if (treat(client_fd, packet) == -1)
	return (-1);
      //return (0);
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
