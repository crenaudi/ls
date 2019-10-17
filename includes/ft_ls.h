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
#include "libft.h"

# define BUF_SIZE       1000
# define FLG_NULL       0x00
# define FLG_R_MAJ      0x40
# define FLG_L          0x20
# define FLG_A          0x10
# define FLG_R          0x02
# define FLG_T          0x01

typedef struct s_env    t_env;
typedef struct s_pile   t_pile;
typedef struct s_elem   t_elem;

struct s_env
{
      char              flags;
      //char              *way;
      char              **curr;
      t_pile            *pile;
      t_elem            **lst;
};

struct s_elem
{
      char              name[256];
      char              *way;
      struct stat       *buf;
      struct s_elem     *next;
};

struct s_pile
{
      t_elem            *first;
};

void        error(char *av, int error);
void        stack(t_pile *pile, char *name, char *way, struct stat *dir);
t_elem      *unstack(t_pile *pile);
void        manage(t_elem *dir, t_env  *e);
void        tab2pile(t_env *e, char *way, struct stat *buf, int i, int len);
char        device_type(struct stat buf);
//void  mode_type(struct stat buf);
void        sort_t(struct stat *buf, char **curr, int size, int r);
void        clean(char **tab);
void        print_ls(struct stat *buf, char *way, t_env *e);

#endif
