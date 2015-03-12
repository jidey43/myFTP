
#include "client.h"

void			fill_db(t_match_fptr *db)
{
  assert(db != NULL);
  db[0] = (t_match_fptr){"user", &user};
  db[1] = (t_match_fptr){"ls", &ls};
  db[2] = (t_match_fptr){"cd", &cd};
  db[3] = (t_match_fptr){"get", &get};
  db[4] = (t_match_fptr){"put", &put};
  db[5] = (t_match_fptr){"pwd", &pwd};
  db[6] = (t_match_fptr){"quit", &quit};
  db[7] = (t_match_fptr){NULL, NULL};
}

t_match_fptr		*init_db(t_client *client)
{
  if((client->db = malloc(sizeof(t_match_fptr) * 8)) == NULL)
    return (NULL);
  fill_db(client->db);
  return (client->db);
}

int		get_ip_and_port(int ac, char **av, t_client *client)
{
  if (ac != 3)
    {
      puts("usage : ./client machine port");
      return (-1);
    }
  client->server_ip = av[1];
  client->port = atoi(av[2]);
  if (client->port < 0 || client->port > 65536)
    {
      puts("Port have to be between 0 and 65535");
      return (-1);
    }
  return (0);
}

void		init_sockaddr(t_client *client)
{
  client->s_in.sin_family = AF_INET;
  client->s_in.sin_port = htons(client->port);
  client->s_in.sin_addr.s_addr = inet_addr(client->server_ip);
}

int		init_client(int ac, char **av, t_client *client)
{
  struct protoent       *pe;

  if (get_ip_and_port(ac, av, client) == -1)
    return (-1);
  pe = getprotobyname("TCP");
  if (pe == NULL)
    return (-1);
  init_sockaddr(client);
  client->socket_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (client->socket_fd == -1)
    return (-1);
  if (init_db(client) == NULL)
    return (-1);
  return (0);
}
