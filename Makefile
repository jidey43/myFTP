##
## Makefile for ftp in /home/roman/Documents/dev/PSU_2014_myftp
## 
## Made by grout_r
## Login   <roman@epitech.net>
## 
## Started on  Thu Mar 19 13:49:44 2015 grout_r
## Last update Thu Mar 19 14:04:05 2015 grout_r
##

CC =		gcc

RM =		rm -f

CFLAGS =	-Wall -Werror -Wextra

LDFLAGS =	

SRC_SRV =	./server_srcs/server.c \
		./server_srcs/server_init.c \
		./server_srcs/server_core.c \
		./server_srcs/server_treat.c \
		./server_srcs/server_put.c \
		./server_srcs/server_get.c \
		./server_srcs/server_ls.c \
		./server_srcs/server_pwd.c \
		./server_srcs/server_cd.c \
		./server_srcs/server_user.c \

SRC_CLI = 	./client_srcs/client.c \
		./client_srcs/client_init.c \
		./client_srcs/client_core.c \
		./client_srcs/client_command.c \
		./client_srcs/client_execute.c \
		./client_srcs/client_put.c \
		./client_srcs/client_get.c \
		./client_srcs/client_ls.c \
		./client_srcs/client_pwd.c \
		./client_srcs/client_cd.c \
		./client_srcs/client_user.c \
		./client_srcs/client_quit.c

OBJ_SRV =	$(SRC_SRV:.c=.o)

OBJ_CLI = 	$(SRC_CLI:.c=.o)

NAME_SRV =	./bin/serveur

NAME_CLI = 	client

all:		$(NAME_CLI) $(NAME_SRV)

$(NAME_CLI):	$(OBJ_CLI)
		$(CC) $(LDFLAGS) $(OBJ_CLI) -o $(NAME_CLI)

$(NAME_SRV):	$(OBJ_SRV)
		$(CC) $(LDFLAGS) $(OBJ_SRV) -o $(NAME_SRV)

clean:
		$(RM) $(OBJ_SRV) $(OBJ_CLI)

fclean:		clean
		$(RM) $(NAME_SRV) $(NAME_CLI)

re: fclean all

.PHONY: re all clean fclean
