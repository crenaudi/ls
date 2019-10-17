#include "../includes/ft_ls.h"

static int  ln_tab(char **tab)
{
      int i;

      i = 0;
      while (tab[i][0]!='\0')
            i++;
      return(i);
}

void sec_step(t_env *e, char *way, char *dir)
{
      struct stat *buf;
      int   i;
      int   len;

      i = -1;
      way = (way == NULL) ? dir : ft_strjoin(way, dir);
/*
      char      **tmpc;
      int         j;
      j = 0;
      tmpc = e->curr;
      while (tmpc[j][0] != '\0')
      {
            printf("Dans curr : %s\n", tmpc[j]);
            j++;
      }
      printf("fin\n");
*/
      len = ln_tab(e->curr);
      if (!(buf = (struct stat *)malloc(sizeof(struct stat) * (len))))
            return;
      while (++i < len)
            if (lstat(ft_strjoin(way, e->curr[i]), &buf[i]) != 0)
                  printf(".");
      tab2pile(e, way, buf, 0, len);
      if (FLG_T == (FLG_T & e->flags))
            (FLG_R == (FLG_R & e->flags)) ? sort_t(buf, e->curr, len, 1) : sort_t(buf, e->curr, len, 0);
/*
      t_elem      *tmp;
      tmp = e->pile->first;
      while (tmp != NULL)
      {
            printf("Dans ma pile : %s%s\n", tmp->way, tmp->name);
            tmp = tmp->next;
      }
      printf("fin\n");
*/
      print_ls(buf, way, e);
      free(buf);
      clean(e->curr);
      if (FLG_R_MAJ == (FLG_R_MAJ & e->flags) && e->pile->first != NULL)
            manage(unstack(e->pile), e);
      else
            return;
}

void manage(t_elem *dir, t_env *e)
{
      DIR               *dirp;
      struct dirent     *c;
      int               i;

      i = -1;
      if ((dirp = opendir((dir->way == NULL) ? dir->name
            : ft_strjoin(dir->way, dir->name))) == NULL)
      {
            error(dir->name, -1);
            return;
      }
      while ((c = readdir(dirp)) != NULL)
      {
            if (e->flags == FLG_NULL || e->flags == FLG_A)
            {
                  if ((e->flags == 0x10 && c->d_name[0] == '.')
                        || c->d_name[0] != '.')
                        ft_putendl(c->d_name);
            }
            else
                  e->curr[i++] = c->d_name;
      }
      if (i != -1)
            sec_step(e, dir->way, ft_strjoin(dir->name, "/"));
      free(dir);
}
