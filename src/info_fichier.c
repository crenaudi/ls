#include "include/ft_ls.h"

int   main(int ac, char **av)
{
      struct stat       buf;
      struct passwd     *pwd;
      struct group      *grp;
      DIR               *dirp;
      struct dirent     *content;
      char              c;

      (void)ac;
      //quand j'ai -- stop lecture des flags
      if ((dirp = opendir("..")) == NULL)
            return(-1);
      while ((content = readdir(dirp)) != NULL)
            if (content->d_name[0] != '.')
                  break;
      printf("Nom : %s\n", ".");
      if (stat(av[1], &buf) != 0)
            printf("pb\n");
      pwd = getpwuid(buf.st_uid);
      grp = getgrgid(buf.st_gid);
      printf("Type : %c\n", device_type(buf));
      mode_type(buf);
      printf("Nombre de lien(s) : %hu\n", buf.st_nlink);
      printf("Proprietaire : %s\n",  pwd->pw_name);
      printf("Groupe : %s\n", grp->gr_name);
      printf("Taille : %lld\n", buf.st_size);
      printf("Date de derniere modif : %s\n", ctime(&buf.st_ctime));
      return (0);
}
