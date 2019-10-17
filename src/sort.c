#include "../includes/ft_ls.h"

void sort_t(struct stat *buf, char **curr, int size, int r)
{
      int i;
      int ln;

      ln = size;
      (void)buf;
      (void)curr;
      while (ln--)
      {
            i = -1;
            while (i++ < size)
            {
                  if (r == 1 /*&& buf[i]->time > buf[i + 1]->time*/)
                  {
                        printf(" > ");
                        //ft_swap(cuur[i], curr[i + 1]);
                        //ft_swap(&buf[i], &buf[i + 1]);
                  }
                  else if (r == 0 /*&& buf[i]->time < buf[i + 1]->time*/)
                  {
                        printf(" < ");
                        //ft_swap(cuur[i], curr[i + 1]);
                        //ft_swap(&buf[i], &buf[i + 1]);
                  }
            }
      }
}
