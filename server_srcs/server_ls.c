
#include "server.h"

int			send_filename(int client_fd, char *name)
{
  t_packet		packet;

  bzero(&packet, sizeof(packet));
  packet.type = DATA_LS;
  memcpy(packet.data, name, strlen(name));
  if (write(client_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  bzero(&packet, sizeof(packet));
  if (read(client_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  if (packet.type != READY)
    return (-1);
  return (0);
}

int			send_end_of_ls(int client_fd)
{
  t_packet		packet;
  
  packet.type = LAST_ONE;
  if (write(client_fd, &packet, sizeof(packet)) == -1)
    return (-1);
  return  (0);
}

int			read_files(int client_fd)
{
  DIR			*currentdir;
  struct dirent		*currentfile;

  if ((currentdir = opendir(getcwd(0, 0))) == NULL)
    return (-1);
  while ((currentfile = readdir(currentdir)) != NULL)
    {
      send_filename(client_fd, currentfile->d_name);
    }
  if (send_end_of_ls(client_fd) == -1)
    return (-1);
  closedir(currentdir);
  return (0);
}

int		ls(int client_fd, t_packet packet)
{
  (void)packet;
  read_files(client_fd);
  return (0);
}
