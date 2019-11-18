/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:09:22 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/02 13:36:09 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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
	if (e->reccursive == 1)
	{
		free(e->pile->first);
		free(e->pile);
	}
	ft_bzero(e, sizeof(t_env));
}
