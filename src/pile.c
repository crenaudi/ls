/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:15:37 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/31 16:50:20 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_lst		*new_elem(char *name, char *way)
{
	t_lst			*new;

	if (!(new = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	ft_bzero(new, sizeof(t_lst));
	if (name != NULL)
		ft_strcpy(new->name, name);
	else
		ft_bzero(new->name, sizeof(char) * NAME_MAX);
	if (way != NULL)
		ft_strcpy(new->way, way);
	else
		ft_bzero(new->way, sizeof(char) * PATH_MAX);
	return (new);
}

int			push(t_pile_cntr *pile_cntr, char *name, char *way)
{
	t_lst	*new;

	if ((new = new_elem(name, way)) == NULL)
		return (ERROR);
	if (pile_cntr->first == NULL)
		pile_cntr->first = new;
	else
	{
		new->next = pile_cntr->first;
		pile_cntr->first = new;
	}
	return (SUCCESS);
}

t_lst		*pop(t_pile_cntr *pile_cntr)
{
	t_lst	*tmp;

	tmp = NULL;
	tmp = pile_cntr->first;
	if (pile_cntr == NULL)
		return (NULL);
	if (pile_cntr != NULL && pile_cntr->first != NULL)
		pile_cntr->first = tmp->next;
	return (tmp);
}

static void	push2stack_rec(t_env *e, t_lst *lst, char *way, size_t n)
{
	char		*tmp[2];
	struct stat	stt;

	if (--n)
		push2stack_rec(e, lst->next, way, n);
	tmp[1] = NULL;
	tmp[0] = NULL;
	tmp[0] = (lst->name[0] == '/') ?
	ft_strdup(lst->name) : ft_strjoin(way, lst->name);
	stat(tmp[0], &stt);
	if ((ft_strcmp(lst->name, ".") != 0 && lst->name[1] != '.')
		&& (device(stt.st_mode) == 'd' || device(stt.st_mode) == 'l'))
		push(e->pile_cntr, lst->name, tmp[1] = (lst->name[0] == '/') ?
			NULL : ft_strdup(way));
	else
		(e->recursive != 1) ? ft_putendl(lst->name) : NULL;
	ft_strdel(&tmp[0]);
	ft_strdel(&tmp[1]);
}

void		push2stack(t_env *e, char *way)
{
	t_lst	*lst;
	size_t	size;

	lst = e->file_cntr->lst;
	size = e->file_cntr->size;
	push2stack_rec(e, lst, way, size);
}
