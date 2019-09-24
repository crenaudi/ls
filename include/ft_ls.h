#ifndef     FT_LS_H
#define     FT_LS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
typedef struct s_ls     t_ls;
typedef struct s_pile   t_pile;
typedef struct s_elem   t_elem;

struct t_ls
{
      char              *flags;
      char              *way;
      t_pile            pile;

      //struct stat **tab
      t_elem            **lst;
};

struct t_elem
{
      struct stat       *buf;
      struct t_elem     *next;
};

struct t_pile
{
      t_elem            *first;
};

//void init_env();
//void init_lst();
//void init_pile();
void stack(t_pile *pile, struct stat **dir);
void unstack(t_pile *pile);
void  add_stat(struct stat **tab, struct stat new);
char  device_type(struct stat buf);
void  mode_type(struct stat buf);
void  short_lst(char c, t_elem **lst);
void  add_way(char *way, char *new);
void  print_all(t_elem **lst);

#endif
