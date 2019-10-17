#include "../includes/ft_ls.h"

int   information(struct dirent *content)
{
      struct stat       buf;
      struct passwd     *pwd;
      struct group      *grp;


      if (lstat(content->d_name, &buf) != 0)
            printf("Error lstat\n");
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
/*
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
      if (lstat(".", &buf) != 0)
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
*/
