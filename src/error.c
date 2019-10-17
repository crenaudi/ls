#include "../includes/ft_ls.h"

void  error(char *av, int error)
{
      ft_putstr("ls: ");
      if (error == -1)
      {
            ft_putstr(av);
            ft_putendl(": No such file or directory");
      }
      else
            ft_putendl("usage");
}
