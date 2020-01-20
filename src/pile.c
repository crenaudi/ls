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

t_lst		*new_elem(char *name, char *way, mode_t *st_mode)
{
	t_lst			*new;
	mode_t		mode;

	if (!(new = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	if (name != NULL)
		ft_strcpy(new->name, name);
	if (way != NULL)
		ft_strcpy(new->way, way);
	if (!(mode = (mode_t)malloc(sizeof(mode_t))))
		return (NULL);
	if (st_mode != NULL)
	{
		mode = *st_mode;
		new->mode = mode;
	}
	return (new);
}

int		push(t_pile_cntr *pile_cntr, char *name, char *way, mode_t *mode)
{
	t_lst	*new;

	if ((new = new_elem(name, way, mode)) == NULL)
		return (ERROR);
	if (pile_cntr->first == NULL)
		pile_cntr->first = new;
	else
	{
		new->next = pile_cntr->first;
		pile_cntr->first = new;
	}
	if (mode != NULL)
		pile_cntr->mode = *mode;
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

int         add2file(t_file_cntr *cntr, char *name, char *way, mode_t *mode)
{
      t_lst	*new;

	if ((new = new_elem(name, way, mode)) == NULL)
		return (ERROR);
	if (cntr->lst == NULL)
		cntr->lst = new;
	else
	{
		new->next = cntr->lst;
		cntr->lst = cntr->lst;
	}
	cntr->size += 1;
	return (SUCCESS);
}

void		print_pile_cntr(t_pile_cntr *pile_cntr)
{
	t_lst		*tmp;

	tmp = NULL;
	tmp = pile_cntr->first;
	while (tmp != NULL)
	{
		printf("dans ma pile_cntr il y a %s\n", tmp->name);
		tmp = tmp->next;
	}
}
