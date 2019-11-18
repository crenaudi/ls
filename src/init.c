/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:56 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/02 13:37:46 by crenaudi         ###   ########.fr       */
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
}

static int	ft_sizename(char **name)
{
	int		i;
	size_t	max;

	i = 0;
	max = ft_strlen(name[i]);
	while (name[++i][0] != '\0')
		if (ft_strlen(name[i]) > max)
			max = ft_strlen(name[i]);
	return (max);
}

t_imp		*init_size(t_env *e)
{
	t_imp*size;

	if (!(size = (t_imp *)malloc(sizeof(t_imp))))
		return (NULL);
	ft_bzero(size, sizeof(t_imp));
	size->name = ft_sizename(e->curr);
	return (size);
}
