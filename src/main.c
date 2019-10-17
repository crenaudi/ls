#include "../includes/ft_ls.h"

static void init_env(t_env *e)
{
      int         i;
      char        *str;
      t_pile      *pile;

      i = 0;
      ft_bzero(e, sizeof(t_env));
      if (!(e->curr = (char **)malloc(sizeof(char *) * (BUF_SIZE))))
            return ;
      while (i < BUF_SIZE)
      {
            if (!(str = (char *)malloc(sizeof(char) * (256))))
                  return ;
            ft_bzero(str, sizeof(256));
            e->curr[i++] = str;
      }
      if (!(pile = (t_pile *)malloc(sizeof(t_pile))))
            exit(EXIT_FAILURE);
      e->pile = pile;
}

static char add_flags(char c, char flags)
{
      int   i;
      char  cmp[7] = {'t', 'r', '\0', '\0', 'a', 'l', 'R'};

      i = 0;
      while (i < 7)
      {
            if (c == cmp[i])
                  flags |= 0xFF & (1 << i);
            i++;
      }
      return (flags);
}

static t_elem *add_elem(char *elem)
{
      t_elem      *new;
      int         i;

      i = -1;
      if (!(new = (t_elem *)malloc(sizeof(t_elem))))
            exit(EXIT_FAILURE);
      while (elem[++i])
            new->name[i] = elem[i];
      return(new);
}

int   main(int ac, char **av)
{
      t_env e;
      int   i;
      int   j;
      int   balance;

      i = 0;
      j = 0;
      balance = 0;
      init_env(&e);
      (void)ac;
      while (av[++i]!= NULL)
      {
            j = 0;
            if (av[i][j] == '-' && av[i][j + 1] != '-' && balance != 1)
                  while (av[i][j])
                        e.flags = add_flags(av[i][j++], e.flags);
            else if (av[i][j] != '-' && av[i][j + 1] != '-')
            {
                  balance = 1;
                  manage(add_elem(av[i]), &e);
            }
            else
                  error(av[i], -1);
      }
      if (balance == 0)
            manage(add_elem("."), &e);
      return (0);
}
