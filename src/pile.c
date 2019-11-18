/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:07:55 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/02 13:44:22 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	stack(t_pile *pile, char *name, char *way, struct stat *dir)
{
	t_elem	*new;
	//int		i;

	//i = -1;
	if (!(new = (t_elem *)malloc(sizeof(t_elem))) || pile == NULL)
		exit(EXIT_FAILURE);
	new->buf = dir;
	new->way = ft_strdup(way);
	ft_strcpy(new->name, name);
	/*while (name[++i])
		new->name[i] = name[i];*/
	new->next = pile->first;
	pile->first = new;
}

t_elem	*unstack(t_pile *pile)
{
	t_elem	*tmp;

	tmp = pile->first;
	printf("Dans ma pile il y a %s\n",pile->first->name);
	while(tmp != NULL)
	{
		printf("Dans ma pile il y a %s\n",tmp->name);
		tmp = tmp->next;
	}

	if (pile == NULL)
		exit(EXIT_FAILURE);
	tmp = pile->first;
	pile->first = tmp->next;
	printf("fini \n");
	return (tmp);
}

void	tri_reccursif(t_env *e, char *way, struct stat *buf, int i, int ln)
{
	if (++i < ln)
	{
		tri_reccursif(e, way, buf, i, ln);
		if (device_type(buf[i]) == 'd')
		{
			stack(e->pile, e->curr[i], way, buf);
		}
	}
}
