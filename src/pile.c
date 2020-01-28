/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile_cntr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:15:37 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/28 18:45:37 by crenaudi         ###   ########.fr       */
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

int		push(t_pile_cntr *pile_cntr, char *name, char *way)
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


int         addfl(t_file_cntr *cntr, char *name, char *way)
{
      t_lst	*new;

	if ((new = new_elem(name, way)) == NULL)
		return (ERROR);
	if (cntr->lst == NULL)
		cntr->lst = new;
	else
	{
		new->next = cntr->lst;
		cntr->lst = new;
	}
	cntr->size += 1;
	return (SUCCESS);
}

void 	push2stack(t_env *e, char *way)
{
	t_lst 	*lst;
	char 		*tmp[2];
	struct stat stt;
	size_t 	i;

	tmp[0] = NULL;
	lst = e->file_cntr->lst;
	i = 0;
	while (i < e->file_cntr->size)
	{
		tmp[1] = NULL;
		tmp[0] = (lst->name[0] == '/') ?
			ft_strdup(lst->name) : ft_strjoin(way, lst->name);
		stat(tmp[0], &stt);
		if ((ft_strcmp(lst->name, ".") != 0 && lst->name[1] != '.')
			&& (device(stt.st_mode) == 'd' || device(stt.st_mode) == 'l'))
			push(e->pile_cntr, lst->name, tmp[1] = (lst->name[0] == '/') ?
				NULL : ft_strdup(way));
		else
			(e->recursive != 1) ? ft_putendl(lst->name) : ft_putchar(' ');
		lst = lst->next;
		ft_strdel(&tmp[0]);
		ft_strdel(&tmp[1]);
		i++;
	}
}

void		print_pile_cntr(t_pile_cntr *pile_cntr)
{
	t_lst		*tmp;

	tmp = NULL;
	tmp = pile_cntr->first;
	while (tmp != NULL)
	{
		ft_putstr("dans ma pile_cntr il y a ");
		ft_putendl(tmp->name);
		tmp = tmp->next;
	}
}
