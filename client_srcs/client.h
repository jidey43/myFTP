
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

# define DATA_PUT 6

# define READY 7
# define ABORT 8

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
