
#include "client.h"

int		pwd(t_client *client, char **command)
{
  t_packet	packet;

  (void)command;
  packet.type = CMD_PWD;
  if (write(client->socket_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  bzero(&packet, sizeof(packet));
  if (read(client->socket_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  if (packet.type == DATA_PWD)
    puts(packet.data);
   return (0);
}
