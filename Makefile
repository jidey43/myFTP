CC =		gcc

RM =		rm -f

CFLAGS =	-Wall -Werror -Wextra -g3

LDFLAGS =	

SRC_SRV =	./server_srcs/server.c \
		./server_srcs/server_init.c \
		./server_srcs/server_core.c \
		./server_srcs/server_treat.c \
		./server_srcs/server_put.c

SRC_CLI = 	./client_srcs/client.c \
		./client_srcs/client_init.c \
		./client_srcs/client_core.c \
		./client_srcs/client_command.c \
		./client_srcs/client_execute.c \
		./client_srcs/client_put.c

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
