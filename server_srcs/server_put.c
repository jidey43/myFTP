
#include "server.h"

int		receive_file(int client_fd, int file_fd)
{
  t_packet	packet;
  
  if (read(client_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  if (write(file_fd, packet.data, strlen(packet.data)) == -1)
    return (-1);
  close(file_fd);
  return (0);
}

int		accept_file(int client_fd, int status)
{
  t_packet	packet;
  
  packet.type = status;
  if (write(client_fd, &packet, sizeof(packet)) == -1)
    return (-1);  
}

int		put(int client_fd, t_packet packet)
{
  int		file_fd;
  
  printf("Downloading %s\n", packet.data);
  if ((file_fd = open(packet.data, O_CREAT | O_RDWR,  00666)) == -1)
    {
      accept_file(client_fd, READY);
      return (-1);
    }
  if (accept_file(client_fd, ABORT) == -1)
    return (-1);
  if (receive_file(client_fd, file_fd) == -1)
    return (-1);
  return (0);
}
