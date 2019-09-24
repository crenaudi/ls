#include "include/ft_ls.h"

int   main(int ac, char **av)
{
      DIR               *dirp;
      struct dirent     *content;

      (void)ac;
      if ((dirp = opendir(av[1])) == NULL)
            return(-1);
      while ((content = readdir(dirp)) != NULL)
            if (content->d_name[0] != '.')//et len - 1 != '~'
                  printf("%s\n", content->d_name);
      closedir(dirp);
      return (0);
}
