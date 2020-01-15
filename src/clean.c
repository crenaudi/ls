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
	ft_bzero(elem->name, sizeof(char) * PATH_MAX);
	ft_memdel((void **)(&elem->name));
	ft_strdel(&elem->way);
	ft_memdel((void **)(&elem->stat));
	elem->next = NULL;
	clean_ptr((void *)(&elem));
}

void	clean(char **tab)
{
	int	i;

	i = 0;
	while (i < BUF_SIZE)
		ft_bzero(tab[i++], sizeof(PATH_MAX));
}

void	clean_env(t_env *e)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (i < BUF_SIZE)
	{
		ft_bzero(e->current[i], sizeof(PATH_MAX));
		tmp = e->current[i];
		clean_ptr((void **)(&tmp));
		i++;
	}
	clean_ptr((void **)(&e->pile->first));
	clean_ptr((void **)(&e->pile));
	clean_ptr((void **)(&e->current));
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
