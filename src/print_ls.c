#include "../includes/ft_ls.h"

void print_ls(struct stat *buf, char *way, t_env *e)
{
      int   i;

      i = -1;
      (void)buf;
      way[ft_strlen(way) - 1] = ':';
      ft_putchar('\n');
      ft_putendl(ft_strjoin("\nDossier ", way));
      ft_putchar('\n');
      if (FLG_L == (FLG_L & e->flags))
            printf("\nimp tout\n");
      else
            while (e->curr[++i][0] != '\0')
                  if (e->flags != (FLG_A & e->flags) && e->curr[i][0] != '.')
                        ft_putstr(e->curr[i]);
}
