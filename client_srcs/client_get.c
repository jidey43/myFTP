
#include "client.h"

int		get_file(t_client *client, int file_fd)
{
  t_packet	packet;
  
  while (1)
    {
      if (read(client->socket_fd, &packet, sizeof(packet)) == -1)
        return (-1);
      if (write(file_fd, packet.data, packet.size) == -1)
        return (-1);
      if (packet.type == LAST_ONE)
        {
          bzero(&packet, sizeof(packet));
          packet.type = READY;
          if (write(client->socket_fd, &packet, sizeof(packet)) == -1)
            return (-1);
          return (0);
        }
      bzero(&packet, sizeof(packet));
      packet.type = READY;
      if (write(client->socket_fd, &packet, sizeof(packet)) == -1)
        return (-1);
      bzero(&packet, sizeof(packet));
    }
  return (0);
}

int		create_file(char **command)
{
  int		file_fd;

  file_fd = open(command[1], O_CREAT | O_RDWR, 00666);
  if (file_fd == -1)
    {
      puts("File can't be created clientside");
      return (-1);
    }
  return (file_fd);
}

int		get(t_client *client, char **command)
{
  t_packet	packet;
  int		file_fd;

  bzero(&packet, sizeof(packet));
  if (command[1] == NULL)
    return (0);
  puts("Download !");
  packet.type = CMD_GET;
  memcpy(packet.data, command[1], strlen(command[1]));
  if (write(client->socket_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  bzero(&packet, sizeof(packet));
  if (read(client->socket_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  if (packet.type != READY)
    return (0);
  bzero(&packet, sizeof(packet));
  packet.type = READY;
  if (write(client->socket_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  if ((file_fd = create_file(command)) == -1)
    return (0);
  get_file(client, file_fd);
  return (0);
}
