/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:56 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/18 18:58:27 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

struct stat add_stat(t_lst *lst)
{
	struct stat stt;
	char 		*tmp;

	tmp = (lst->name[0] == '/') ?
		ft_strdup(lst->name) : ft_strjoin(lst->way, lst->name);
	stat(tmp, &stt);
	ft_strdel(&tmp);
	return (stt);

}

t_print_all	init_info2print(t_file_cntr *cntr)
{
	t_print_all		info;
	struct stat 	*stat;
	size_t		i;
	t_lst			*lst;

	i = -1;
	lst = cntr->lst;
	if (!(stat = (struct stat *)malloc(sizeof(struct stat) * cntr->size)))
		ft_putstr("ERROR MALLOC");
	while (++i < cntr->size)
	{
		stat[i] = add_stat(lst);
		lst = lst->next;
	}
	max_st_nb(stat, cntr->size, info.nb_max);
	max_st_str(stat, cntr->size, info.str_max);
	info.lst = cntr->lst;
	return (info);
}

t_pile_cntr	*init_pile_cntr()
{
	t_pile_cntr	*cntr;

	if (!(cntr = (t_pile_cntr *)malloc(sizeof(t_pile_cntr))))
		return (NULL);
	cntr->first = NULL;
	ft_bzero(cntr, sizeof(t_pile_cntr));
	return (cntr);
}

t_file_cntr	*init_file_cntr()
{
	t_file_cntr	*cntr;

	if (!(cntr = (t_file_cntr *)malloc(sizeof(t_file_cntr))))
		return (NULL);
	cntr->lst = NULL;
	cntr->size = 0;
	return (cntr);
}

void		init_env(t_env *e)
{
	ft_bzero(e, sizeof(t_env));
	e->f_sort = &sort_base;
	e->f_print = &ls_simple;
	e->recursive = 0;
	e->a = 0;
	e->l = 0;
	e->pile_cntr = init_pile_cntr();
	e->file_cntr = init_file_cntr();
}
