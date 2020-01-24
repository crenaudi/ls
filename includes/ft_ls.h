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
# include <limits.h>
# include "libft.h"

# define BUF_SIZE		10500
# define SUCCESS 		0
# define ERROR 		-1
# define LS			"ls: "
# define USAGE		"usage: "
# define ERROR_01		": No such file or directory"
# define ERROR_02		": Permission denied"
# define ERROR_03		"illegal option -- "
# define ERROR_04		": error in flags"
# define ERROR_05		": usage flags"
# define ERROR_06		"ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]"

typedef struct s_env		t_env;
typedef struct s_file_cntr	t_file_cntr;
typedef struct s_pile_cntr	t_pile_cntr;
typedef struct s_lst		t_lst;
typedef struct s_print_all	t_print_all;
typedef void			(*t_fsrt)(t_file_cntr *files);
typedef void			(*t_fprt)(t_env *e, char *way);

struct					s_env
{
	t_fsrt				f_sort;
	t_fprt				f_print;
	int					a;
	int					l;
	int					recursive;
	t_file_cntr				*file_cntr;
	t_pile_cntr				*pile_cntr;
};

struct 					s_file_cntr
{
  	t_lst 				*lst;
  	size_t      			size;
};

struct					s_pile_cntr
{
	t_lst					*first;
	mode_t    			      st_mode;
};

struct					s_lst
{
	char					name[NAME_MAX];
	char					way[PATH_MAX];
	mode_t        			st_mode;
	struct s_lst			*next;
};

struct					s_print_all
{
	t_lst 				*lst;
	struct stat 			*stat;
	unsigned int			nb_max[2];
	unsigned int			str_max[2];
};

void					init_env(t_env *e);
void					error(char *av, int error, char c);
void					clean(char **tab);
void					clean_env(t_env *e);
int					parse_flags(char **av, t_env *e);
char					device(mode_t st_mode);
void					st_mode_type(mode_t st_mode);
void       				run(t_env *e);
void					print_way(char *way, int rec);
void					ls_simple(t_env *e, char *way);
void					ls_all(t_env *e, char *way);
void					ft_putinfo(struct stat stat, char *name,
	unsigned int nb_max[2], unsigned int str_max[2]);
struct stat 			add_stat(t_lst *lst);
void					sort_base(t_file_cntr *files);
void					sort_r(t_file_cntr *files);
void					sort_t(t_file_cntr *files);
void					sort_rt(t_file_cntr *files);
void					print_octet(struct stat *stat, int ln);
void					time_patern(struct stat stat);
void					nb_patern(int start, int nb);
void					id_patern(int start, int id);
void					str_patern(int start, char *name);
void					max_st_nb(struct stat *stat, int ln,
	unsigned int nb_max[2]);
void					max_st_str(struct stat *stat, int ln,
	unsigned int str_max[2]);
void 					push2stack(t_env *e);
t_file_cntr				*init_file_cntr();
t_pile_cntr				*init_pile_cntr();
t_print_all				init_info2print(t_file_cntr *cntr);
t_lst					*new_elem(char *name, char *way, mode_t *st_mode);
size_t      			ft_lstlen(t_lst *lst);
void					ft_swap_elem(t_lst *elem1, t_lst *elem2);
int                           add2file(t_file_cntr *cntr, char *name,
	char *way, mode_t *st_mode);
int					push(t_pile_cntr *pile, char *name,
	char *way, mode_t *st_mode);
t_lst					*pop(t_pile_cntr *pile);
void					print_pile(t_pile_cntr *pile);
void					destroy_elem(t_lst *elem);
void					destroy_lst(t_lst *lst);
void					destroy_cntr_file(t_file_cntr *cntr);
void					destroy_cntr_pile(t_pile_cntr *cntr);

#endif
