
#include "client.h"

int		is_ok(t_client *client)
{
  t_packet	packet;
  
  read(client->socket_fd, &packet, sizeof(packet));
  if (packet.type == ABORT)
    {
      puts("ABORT !!!");
      puts(packet.data);
    }
  return (packet.type);
}

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
  int		readed;

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
	  if (write(client->socket_fd, &packet, sizeof(packet)) == -1)
	    return (-1);
	  if (is_ok(client) == ABORT)
	    return (-1);
	  return (0);
	}
      write(client->socket_fd, &packet, sizeof(packet));
      if (is_ok(client) == ABORT)
	return (-1);
      bzero(&packet, sizeof(packet));
    }
  return (0);
}

int		put(t_client *client, char **command)
{
  t_packet	packet;
  int		file_fd;

  if (command[1] == NULL)
    return (0);
  if ((file_fd = open_file(command)) == -1)
      return (0);
  printf("Uploading %s !\n", command[1]);
  packet.type = CMD_PUT;
  memcpy(packet.data, command[1], strlen(command[1]));
  packet.data[strlen(command[1])] = '\0';
  if (write(client->socket_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  if (is_ok(client) == ABORT)
    return (-1);
  send_file(file_fd, client);
  return (0);
}
