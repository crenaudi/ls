/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:15:37 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/22 20:58:48 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_elem		*add_new_elem(char *name, char *way, int is_R)
{
	t_elem	*new;
	int		i;

	i = 0;
	if (!(new = (t_elem *)malloc(sizeof(t_elem))))
		return (NULL);
	ft_bzero(new, sizeof(t_elem));
	while (name[i] != '\0')
	{
		new->name[i] = name[i];
		i++;
	}
	new->way = way;
	if (!(new->buf = (struct stat *)malloc(sizeof(struct stat))))
		return (NULL);
	if (is_R == 1 && lstat(ft_strjoin(way, name), new->buf) != 0)
		error(name, 0, NULL);
	return (new);
}

void		empiler(t_env *e, char *name, char *way)
{
	t_elem	*new;

	new = add_new_elem(name, way, e->reccursive);
	if (e->pile == NULL || new == NULL)
		exit(EXIT_FAILURE);
	new->next = e->pile->first;
	e->pile->first = new;
}

t_elem		*depiler(t_pile *pile)
{
	t_elem	*tmp;

	tmp = pile->first;
	if (pile == NULL)
		exit(EXIT_FAILURE);
	if (pile != NULL && pile->first != NULL)
		pile->first = tmp->next;
	return (tmp);
}

void		afficher_pile(t_pile *pile)
{
	t_elem	*tmp;

	tmp = pile->first;
	while (tmp != NULL)
	{
		printf("dans ma pile il y a %s\n", tmp->name);
		tmp = tmp->next;
	}
}

void		free_elem(t_elem *elem)
{
	char			*name;
	struct stat		*buf;

	name = elem->name;
	buf = elem->buf;
	free(name);
	free(buf);
}
