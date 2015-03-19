
#include "client.h"

int		quit(t_client *client, char **command)
{
  assert(client != NULL);
  assert(command != NULL);
  puts("Quit !");
  return (-1);
}

int		execute(t_client * client, char **command)
{
  int		i;
  
  i = 0;
  while (client->db[i].str != NULL && strcmp(client->db[i].str, command[0]) != 0)
    i++;
  if (client->db[i].str == NULL)
    {
      printf("command '%s' not found.\n", command[0]);
      return (0);
    }
  return (client->db[i].funcptr(client, command));
}
