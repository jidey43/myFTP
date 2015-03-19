/*
** client.h for ftp in /home/roman/Documents/dev/PSU_2014_myftp/client_srcs
** 
** Made by grout_r
** Login   <roman@epitech.net>
** 
** Started on  Thu Mar 19 13:41:27 2015 grout_r
** Last update Thu Mar 19 13:55:19 2015 grout_r
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <assert.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

# define CMD_USER 0
# define CMD_LS 1
# define CMD_CD 2
# define CMD_GET 3
# define CMD_PUT 4
# define CMD_PWD 5
# define CMD_QUIT 6

# define DATA_PUT 7
# define DATA_LS 8
# define DATA_PWD 9

# define READY 10
# define ABORT 11

# define LAST_ONE 12

typedef struct s_client t_client;

typedef struct		s_match_fptr
{
  char			*str;
  int			(*funcptr)(t_client *client, char **command);
}			t_match_fptr;

typedef struct		s_client
{
  int			socket_fd;
  int			port;
  char			*server_ip;
  struct sockaddr_in    s_in;
  t_match_fptr		*db;
}			t_client;

typedef struct		s_packet
{
  int		type;
  int		size;
  char		data[1024];
}			t_packet;

int		init_client(int ac, char **av, t_client *client);
int		loop(t_client *client);
char		**add_word(char **command, char *str);
int		execute(t_client * client, char **command);
int		user(t_client *client, char **command);
int		ls(t_client *client, char **command);
int		cd(t_client *client, char **command);
int		get(t_client *client, char **command);
int		put(t_client *client, char **command);
int		pwd(t_client *client, char **command);
int		quit(t_client *client, char **command);

#endif	/* !_CLIENT_H_ */
