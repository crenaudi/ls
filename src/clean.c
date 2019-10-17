#include "../includes/ft_ls.h"

void clean(char **tab)
{
      int   i;

      i = 0;
      while (i < BUF_SIZE)
      {
            ft_bzero(tab[i++], sizeof(256));
      }
}
