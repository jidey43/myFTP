/*
** server_ls.c for ftp in /home/roman/Documents/dev/PSU_2014_myftp/server_srcs
** 
** Made by grout_r
** Login   <roman@epitech.net>
** 
** Started on  Thu Mar 19 13:29:09 2015 Roman
** Last update Thu Mar 19 13:39:32 2015 grout_r
*/

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
