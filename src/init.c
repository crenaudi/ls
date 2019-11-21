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

void		init_env(t_env *e)
{
	int		i;
	char	*str;
	t_pile	*pile;

	i = 0;
	str = NULL;
	ft_bzero(e, sizeof(t_env));
	if (!(e->curr = (char **)malloc(sizeof(char *) * (BUF_SIZE))))
		return ;
	while (i < BUF_SIZE)
	{
		if (!(str = (char *)malloc(sizeof(char) * (256))))
			return ;
		ft_bzero(str, sizeof(256));
		e->curr[i++] = str;
	}
	if (!(pile = (t_pile *)malloc(sizeof(t_pile))))
		exit(EXIT_FAILURE);
	e->pile = pile;
	e->pile->first = NULL;
}
