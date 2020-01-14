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
		exit(EXIT_FAILURE);
	e->pile->first = NULL;
	return (pile);
}

void		init_env(t_env *e)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	pile = NULL;
	ft_bzero(e, sizeof(t_env));
	e->f_sort = &sort_base;
	e->f_print = &ls_simple;
	e->reccursive = 0;
	e->a = 0;
	e->l = 0;
	if (!(e->curr = (char **)malloc(sizeof(char *) * (BUF_SIZE))))
		return ;
	while (i < BUF_SIZE)
	{
		if (!(str = (char *)malloc(sizeof(char) * (PATH_MAX))))
			return ;
		str[0] = '\0';
		e->curr[i++] = str;
	}
	e->pile = init_pile;
}
