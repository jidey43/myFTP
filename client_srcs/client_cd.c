
#include "client.h"

int		request_cd(t_client *client, char **command)
{
  t_packet	packet;
  
  bzero(&packet, sizeof(packet));
  packet.type = CMD_CD;
  memcpy(packet.data, command[1], strlen(command[1]));
  if (write(client->socket_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  return (0);
}

int		read_response(t_client *client)
{
  t_packet	packet;
  
  if (read(client->socket_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  if (packet.type == ABORT)
    puts("something went wrong ...");
  return (0);
}

int		cd(t_client *client, char **command)
{
  assert(client != NULL);
  if (command[1] == NULL)
    return (0);
  if (request_cd(client, command) == -1)
    return (-1);
  puts("Change directory !");
  return (read_response(client));
}
