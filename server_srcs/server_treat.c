
#include "server.h"

typedef int (*funcptr)(int client_fd, t_packet packet);

int		user(int client_fd, t_packet packet)
{
  assert(packet.type != 54128);
  assert(client_fd != 56486);
  return (0);
}

int		ls(int client_fd, t_packet packet)
{
  assert(packet.type != 54128);
  assert(client_fd != 56486);
  return (0);
}

int		cd(int client_fd, t_packet packet)
{
  assert(packet.type != 54128);
  assert(client_fd != 56486);
  return (0);
}

int		get(int client_fd, t_packet packet)
{
  assert(packet.type != 54128);
  assert(client_fd != 56486);
  return (0);
}

int		pwd(int client_fd, t_packet packet)
{
  assert(packet.type != 54128);
  assert(client_fd != 56486);
  return (0);
}

funcptr		*init_funcptr()
{
  funcptr	*tab;
  
  if ((tab = malloc(sizeof(funcptr) * 8)) == NULL)
    return NULL;
  tab[0] = &user;
  tab[1] = &ls;
  tab[2] = &cd;
  tab[3] = &get;
  tab[4] = &put;
  tab[5] = &pwd;
  return (tab);
}

int		treat(int client_fd, t_packet packet)
{ 
  funcptr	*tab;
  
  if ((tab = init_funcptr()) == NULL)
    return (-1);
  tab[packet.type](client_fd, packet);
  return (0);
}
