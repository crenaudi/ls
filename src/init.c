/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:56 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/18 18:58:27 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_pile	*init_pile()
{
	t_pile	*pile;

	if (!(pile = (t_pile *)malloc(sizeof(t_pile))))
		return (NULL);
	pile->first = NULL;
	return (pile);
}

char 	**init_file()
{
	char 	**current;
	char 	*str;
	int 	i;

	i = 0;
	if (!(current = (char **)malloc(sizeof(char *) * (BUF_SIZE))))
		return (NULL);
	while (i < BUF_SIZE)
	{
		if (!(str = (char *)malloc(sizeof(char) * (PATH_MAX))))
			return (NULL);
		str[0] = '\0';
		current[i++] = str;
	}
	return (current);
}

void		init_env(t_env *e)
{
	ft_bzero(e, sizeof(t_env));
	e->f_sort = &sort_base;
	e->f_print = &ls_simple;
	e->recursive = 0;
	e->a = 0;
	e->l = 0;
	e->pile = init_pile();
	e->current = init_file();
}
