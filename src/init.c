/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:56 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/28 18:57:27 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

struct stat	add_stat_way(t_lst *lst, char *way)
{
	struct stat	stt;
	char		*tmp;

	tmp = (lst->name[0] == '/') ?
		ft_strdup(lst->name) : ft_strjoin(way, lst->name);
	lstat(tmp, &stt);
	ft_strdel(&tmp);
	ft_strdel(&way);
	return (stt);
}

t_print_all	init_info2print(t_file_cntr *cntr, char *way)
{
	t_print_all		info;
	struct stat		*stt;
	size_t			i;
	t_lst			*lst;

	i = -1;
	lst = cntr->lst;
	if (!(stt = (struct stat *)malloc(sizeof(struct stat) * cntr->size)))
		ft_putstr("ERROR MALLOC");
	while (++i < cntr->size)
	{
		stt[i] = add_stat_way(lst, ft_strjoin(way, "/"));
		lst = lst->next;
	}
	max_st_nb(stt, cntr->size, info.nb_max);
	max_st_str(stt, cntr->size, info.str_max);
	if (way[0] == '/')
	{
		info.str_max[0] = 12;
		info.str_max[1] = 12;
	}
	info.lst = cntr->lst;
	info.stat = stt;
	return (info);
}

t_pile_cntr	*init_pile_cntr(void)
{
	t_pile_cntr	*cntr;

	if (!(cntr = (t_pile_cntr *)malloc(sizeof(t_pile_cntr))))
		return (NULL);
	ft_bzero(cntr, sizeof(t_pile_cntr));
	cntr->first = NULL;
	return (cntr);
}

t_file_cntr	*init_file_cntr(void)
{
	t_file_cntr	*cntr;

	if (!(cntr = (t_file_cntr *)malloc(sizeof(t_file_cntr))))
		return (NULL);
	ft_bzero(cntr, sizeof(t_file_cntr));
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
	e->need_way = 0;
	e->a = 0;
	e->l = 0;
	e->pile_cntr = init_pile_cntr();
	e->file_cntr = init_file_cntr();
}
