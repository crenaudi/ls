#include "../includes/ft_ls.h"

char  device_type(struct stat buf)
{
      if ((buf.st_mode & S_IFIFO) == S_IFIFO)
            return ('p');
      if ((buf.st_mode & S_IFCHR) == S_IFCHR)
            return ('c');
      if ((buf.st_mode & S_IFDIR) == S_IFDIR)
            return ('d');
      if ((buf.st_mode & S_IFBLK) == S_IFBLK)
            return ('b');
      if ((buf.st_mode & S_IFREG) == S_IFREG)
            return ('-');//fichier ordinaire
      if ((buf.st_mode & S_IFLNK) == S_IFLNK)
            return ('l');
      return ('f');// S_IFMT type of file
}
