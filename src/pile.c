#include "../include/ft_ls.h"

void stack(t_pile *pile, struct stat *dir)
{
      t_elem      *new;

      if (!(new = (t_elem *)malloc(sizeof(t_elem))) || pile == NULL)
            exit(EXIT_FAILURE);
      new->buf = dir;
      new->next = pile->first;
      pile->first = new;
}

struct stat *unstack(t_pile *pile)
{
      t_elem      *tmp;
      struct stat *ret;

      if (pile == NULL)
            exit(EXIT_FAILURE);
      tmp = pile->premier;
      if (tmp->first != NULL)
      {
            ret = tmp->buf;
            pile->first = tmp->next;
            free(tmp);
      }
      return (ret);
}
