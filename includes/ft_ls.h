/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:12:14 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/02 13:29:25 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include "libft.h"

# define BUF_SIZE		1000
# define FLG_NULL		0x00
# define FLG_R_MAJ		0x40
# define FLG_L			0x20
# define FLG_A			0x10
# define FLG_R			0x02
# define FLG_T			0x01

typedef struct s_env	t_env;
typedef struct s_pile	t_pile;
typedef struct s_elem	t_elem;
typedef struct s_imp	t_imp;
typedef struct s_time	t_time;
typedef void       	(*t_sortf)(struct stat *, t_env *, int);
typedef void       	(*t_printf)(struct stat *, char *, t_env *);

struct					s_env
{
	t_sortf				f_sort;
	t_printf				f_print;
	int					a;
	int					reccursive;
	char				**curr;
	t_pile				*pile;
};

struct					s_elem
{
	char				name[256];
	char				*way;
	struct stat			*buf;
	struct s_elem		*next;
};

struct					s_pile
{
	t_elem				*first;
};

struct					s_imp
{
	size_t				name;
	int					user;
	char				*tab_user[256];
	int					grp;
	char				*tab_grp[256];
	int					size;
	int					*tab_size;
	int					link;
};

void					init_env(t_env *e);
int        			parse_flags(int ac, char **av, t_env *e);
int         			ln_tab(char **tab);
struct stat 			*add_buf2pile(t_env *e, char *way);
void					stack(t_pile *pl, char *nm, char *w, struct stat *d);
t_elem				*unstack(t_pile *pile);
void					manage(t_elem *dir, t_env *e);
void					tri_reccursif(t_env *e, char *way,
	struct stat *buf, int i, int ln);
char					device_type(struct stat buf);
void					mode_type(struct stat buf);
void					sort_base(struct stat *buf, t_env *e, int size);
void					sort_r(struct stat *buf, t_env *e, int size);
void					sort_t(struct stat *buf, t_env *e, int size);
void					sort_rt(struct stat *buf, t_env *e, int size);
t_imp					*init_size(t_env *e);
void					print_way(char *way);
void					print_simple(struct stat *buf, char *way, t_env *e);
void					print_all(struct stat *buf, char *way, t_env *e);
void					error(char *av, int error);
void					clean(char **tab);
void					clean_env(t_env *e);

#endif
