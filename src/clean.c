/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:09:22 by crenaudi          #+#    #+#             */
/*   Updated: 2019/12/17 23:11:55 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	clean_ptr(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	clean_elem(t_elem *elem)
{
	ft_bzero(elem->name, sizeof(char) * 256);
	clean_ptr((void *)(&elem->name));
	clean_ptr((void *)(&elem->way));
	clean_ptr((void *)(&elem->buf));
	elem->next = NULL;
	clean_ptr((void *)(&elem));
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
	tmp = NULL;
	while (i < BUF_SIZE)
	{
		ft_bzero(e->curr[i], sizeof(256));
		tmp = e->curr[i];
		clean_ptr((void **)(&tmp));
		i++;
	}
	clean_ptr((void *)(&e->pile->first));
	clean_ptr((void *)(&e->pile));
	clean_ptr((void *)(&e->curr));
	ft_bzero(e, sizeof(t_env));
}

int		ln_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i][0] != '\0')
		i++;
	return (i);
}
