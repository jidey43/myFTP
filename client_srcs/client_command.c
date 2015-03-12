
#include "client.h"

int		size_of_command(char **command)
{
  int		i;

  i = 0;
  if (command == NULL)
    return (0);
  while (command[i++] != NULL);
  return (i);
}

char		**add_word(char **command, char *str)
{
  int		i;
  
  if (command == NULL)
    {
      command = malloc(sizeof(char *) *  2);
      command[0] = str;
      command[1] = NULL;
      return (command);
    }
  i = size_of_command(command);
  command = realloc(command, sizeof(char *) * ( size_of_command(command) + 2));
  command[i - 1] = str;
  command[i] = NULL; 
  return (command);
}
