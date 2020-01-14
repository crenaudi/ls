/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:15:37 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/28 18:45:37 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_elem		*add_new_elem(char *name, char *way)
{
	t_elem			*new;
	struct stat	*buf;
	char 				*tmp;
	int					i;

	i = -1;
	if (!(new = (t_elem *)malloc(sizeof(t_elem))))
		return (NULL);
	ft_bzero(new, sizeof(t_elem));
	ft_strcpy(new->name, name);
	new->way = ft_strdup(way);
	if (!(buf = (struct stat *)malloc(sizeof(struct stat))))
		return (NULL);
	tmp = ft_strjoin(way, name);
	lstat(tmp, buf);
	new->buf = buf;
	ft_strdel(&tmp);
	return (new);
}

int		push(t_pile *pile, char *name, char *way)
{
	t_elem	*new;

	new = add_new_elem(name, way);
	if (new == NULL)
		return (ERROR);
	if (pile->first == NULL)
		pile->first = new;
	else
	{
		new->next = pile->first;
		pile->first = new;
	}
	return (SUCCESS);
}

t_elem		*pop(t_pile *pile)
{
	t_elem	*tmp;

	tmp = NULL;
	tmp = pile->first;
	if (pile == NULL)
		return (NULL);
	if (pile != NULL && pile->first != NULL)
		pile->first = tmp->next;
	return (tmp);
}

void		afficher_pile(t_pile *pile)
{
	t_elem	*tmp;

	tmp = NULL;
	tmp = pile->first;
	while (tmp != NULL)
	{
		printf("dans ma pile il y a %s\n", tmp->name);
		tmp = tmp->next;
	}
}
