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
# include <errno.h>
# include <limits.h>
# include "libft.h"


# define SUCCESS 		0
# define ERROR 		-1
# define NAME_MAX 	257

typedef struct s_file_cntr	t_file_cntr;
typedef struct s_pile			t_pile_cntr;
typedef struct s_lst			t_lst;

struct 					s_file_cntr
{
  	t_lst 				*lst;
  	size_t      			size;
};

struct					s_pile_containter
{
	t_lst					*first;
	mode_t    			      st_mode;
};

struct					s_lst
{
	char					name[NAME_MAX];
	char					way[PATH_MAX];
	mode_t        			mode;
	struct s_lst			*next;
};

t_file_cntr			*init_file_cntr();
t_pile_cntr			*init_pile_cntr();
t_lst					*new_elem();
size_t      			ft_lstlen(t_lst *lst);
void					ft_swap_elem(t_lst *elem1, t_lst *elem2);
int                           add2file(t_file_cntr *cntr, char name,
      char way, st_mode mode);
int					push(t_pile_cntr *pile, char *name,
	char *way, t_mode st_mode);
t_lst					*pop(t_pile_cntr *pile);
void					print_pile(t_pile_cntr *pile);
void					destroy_elem(t_lst *elem);
void					destroy_lst(t_lst *lst);
void					destroy_cntr_file(t_file_cntr *cntr);
void					destroy_cntr_pile(t_pile_cntr *cntr);

#endif
