/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:09:22 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/18 18:51:09 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	clean_elem(t_elem *elem)
{
	//free(elem->name);
	free(elem->way);
	//free(elem->buf);
	elem->next = NULL;
	free(elem);
}

void	clean(char **tab)
{
	int	i;

	i = 0;
	while (i < BUF_SIZE)
		ft_bzero(tab[i++], sizeof(256));
}

void	clean_env(t_env *e)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < BUF_SIZE)
	{
		ft_bzero(e->curr[i], sizeof(256));
		tmp = e->curr[i];
		free(tmp);
		i++;
	}
	free(e->curr);
	/*
	if (e->pile != NULL && e->pile->first != NULL)
		free(e->pile->first);
	printf("hey\n");
	if (e->pile != NULL)
		free(e->pile);
	*/
	ft_bzero(e, sizeof(t_env));
}
