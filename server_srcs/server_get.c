
#include "server.h"

int             is_ok(int client_fd)
{
  t_packet      packet;

  read(client_fd, &packet, sizeof(packet));
  if (packet.type == ABORT)
    {
      puts("ABORT !!!");
      puts(packet.data);
    }
  return (packet.type);
}

int		send_file(int client_fd, int file_fd)
{
  t_packet      packet;
  int           readed;

  while (1)
    {
      readed = read(file_fd, packet.data , 1024);
      if (readed == -1)
        return (-1);
      packet.type = DATA_PUT;
      packet.size = readed;
      if (readed < 1024)
        {
          packet.type = LAST_ONE;
          if (write(client_fd, &packet, sizeof(packet)) == -1)
            return (-1);
          if (is_ok(client_fd) == ABORT)
            return (-1);
          return (0);
	}
      write(client_fd, &packet, sizeof(packet));
      if (is_ok(client_fd) == ABORT)
        return (-1);
      bzero(&packet, sizeof(packet));
    }
  return (0);
}

int		accept_download(int client_fd, int status)
{
  t_packet	packet;
  
  packet.type = status;
  if (write(client_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  return (0);
}

int		get(int client_fd, t_packet packet)
{
  int		file_fd;

  puts(packet.data);
  if ((file_fd = open(packet.data, O_RDONLY)) == -1)
    {
      accept_download(client_fd, ABORT);
      return (0);
    }
  accept_download(client_fd, READY);
  bzero(&packet, sizeof(packet));
  if (read(client_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  if (packet.type != READY)
    return (0);
  send_file(client_fd, file_fd);
  assert(packet.type != 54128);
  assert(client_fd != 56486);
  return (0);
}
