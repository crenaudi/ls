/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:12:14 by crenaudi          #+#    #+#             */
/*   Updated: 2019/12/19 21:54:29 by crenaudi         ###   ########.fr       */
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
# include <errno.h>
#include <limits.h>
# include "libft.h"

# define BUF_SIZE		10500
# define SUCCESS 		0
# define ERROR 		-1

typedef struct s_env	t_env;
typedef struct s_pile	t_pile;
typedef struct s_elem	t_elem;
typedef int	t_vec3 __attribute__((ext_vector_type(3)));
typedef unsigned int	t_vec2 __attribute__((ext_vector_type(2)));
typedef void			(*t_fsrt)(struct stat *, char **, int);
typedef void			(*t_fprt)(char *, t_env *);

struct					s_env
{
	t_fsrt				f_sort;
	t_fprt				f_print;
	int						a;
	int						l;
	int						recursive;
	char					**current;
	char 					*wrong_argv;
	struct stat 	*buf;
	t_pile				*pile;
};

struct					s_elem
{
	char				name[PATH_MAX];
	char				*way;
	struct stat			*buf;
	struct s_elem		*next;
};

struct					s_pile
{
	t_elem				*first;
};

void					init_env(t_env *e);
char 					**init_file();
t_pile				*init_pile();

void					error(char *av, int error, char c);
void					clean(char **tab);
void					clean_elem(t_elem *elem);
void					clean_env(t_env *e);
void					clean_ptr(void **ptr);

t_elem				*add_new_elem(char *name, char *way);
int						push(t_pile *pile, char *name, char *way);
t_elem				*pop(t_pile *pile);
void					afficher_pile(t_pile *pile);
void					free_elem(t_elem *elem);

int						parse_flags(char **av, t_env *e);
int						ln_tab(char **tab);
char					device(struct stat buf);
void					mode_type(struct stat buf);

void					run(t_elem *elem, t_env *e);

void					print_way(char *way, int rec);
void					ls_simple(char *way, t_env *e);
void					ls_all(char *way, t_env *e);
void					print_lnk(struct stat buf, char *lnk, t_pile *pile);
void					ft_putinfo(struct stat buf, char *name, t_vec2 nb_max,
		t_vec2 str_max);

void 					buf_tab(char *way, t_env *e);

void					sort_base(struct stat *buf, char **s, int size);
void					sort_r(struct stat *buf, char **s, int size);
void					sort_t(struct stat *buf, char **s, int size);
void					sort_rt(struct stat *buf, char **s, int size);

void					print_way(char *way, int rec);

void					clean_strsplit(char **tab);
void					print_octet(struct stat *buf, int ln);
void					time_patern(struct stat buf);
void					nb_patern(int start, int nb);
void					id_patern(int start, int id);
void					str_patern(int start, char *name);
void					max_st_nb(struct stat *buf, int ln, t_vec2 *nb_max);
void					max_st_str(struct stat *buf, int ln, t_vec2 *str_max);


#endif
