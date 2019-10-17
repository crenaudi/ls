#include "../includes/ft_ls.h"

void stack(t_pile *pile, char *name, char *way, struct stat *dir)
{
      t_elem      *new;
      int         i;

      i = -1;
      if (!(new = (t_elem *)malloc(sizeof(t_elem))) || pile == NULL)
            exit(EXIT_FAILURE);
      new->buf = dir;
      new->way = ft_strdup(way);
      while (name[++i])
            new->name[i] = name[i];
      new->next = pile->first;
      pile->first = new;
}

t_elem  *unstack(t_pile *pile)
{
      t_elem      *tmp;

      //ft_bzero(way, sizeof(char) * 256);
      //way = ft_strdup(pile->first->way);
      if (pile == NULL)
            exit(EXIT_FAILURE);
      tmp = pile->first;
      pile->first = tmp->next;
      return(tmp);
}

void tab2pile(t_env *e, char *way, struct stat *buf, int i, int len)
{
      if (++i < len)
      {
            tab2pile(e, way, buf, i, len);
            if (device_type(buf[i]) == 'd')
            {
                  stack(e->pile, e->curr[i], way, buf);
            }
      }
}
