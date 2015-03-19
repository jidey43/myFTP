
#include "client.h"

int		request_user(t_client *client, char **command)
{
  t_packet	packet;
  
  packet.type = CMD_USER;
  memcpy(packet.data, command[1], strlen(command[1]));
  if (write(client->socket_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  return (0);
  bzero(&packet, sizeof(packet));
  if (read(client->socket_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  if (packet == AUTHENT_OK)
    return (0);
  if (packet == AUTHENT_PASS)
    return (1);
}

int		user(t_client *client, char **command)
{
  if (command[1] == NULL)
    return (0);
  if (request_user(client, command) == -1)
    return (-1);
  puts("Login !");
  return (0);
}
