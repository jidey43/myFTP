
#include "client.h"

int		open_file(char **command)
{
  int		fd;

  fd = open(command[1], O_RDONLY);
  if (fd == -1)
    {
      printf("Le fichier '%s' est introuvable\n", command[1]);
      return (-1);
    }
  return (fd);
}

int		send_file(int file_fd, t_client *client)
{
  t_packet	packet;

  packet.type = DATA_PUT;
  read(file_fd,  packet.data , 1024);
  write(client->socket_fd, &packet, sizeof(packet));
  return (0);
}

int		put(t_client *client, char **command)
{
  assert(client != NULL);
  puts("Upload !");

  t_packet	packet;
  int		file_fd;

  packet.type = CMD_PUT;
  memcpy(packet.data, command[1], strlen(command[1]));
  packet.data[strlen(command[1])] = '\0';
  puts(packet.data);
  write(client->socket_fd, &packet, sizeof(packet));
  if ((file_fd = open_file(command)) == -1)
      return (-1);
  send_file(file_fd, client);
  return (0);
}
