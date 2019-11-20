/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:43 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/19 15:53:21 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"


static void	sort_param(t_env *e, int size)
{
	int			i;
	int			ln;
	char		*abys;

	ln = size;
	size--;
	while (ln--)
	{
		i = -1;
		while (++i < size)
		{
			if (e->curr[i][0] > e->curr[i + 1][0])
			{
				abys = e->curr[i];
				e->curr[i] = e->curr[i + 1];
				e->curr[i + 1] = abys;
			}
		}
	}
}

int	main(int ac, char **av)
{
	t_env		e;
	int		i;
	int		j;

	init_env(&e);
	i = parse_flags(ac, av, &e);
	if (i == -1)
		error(NULL, -3);
	else if (av[i] == NULL)
	{
		empiler(&e, ".", NULL);
    run(depiler(e.pile), &e);
	}
	else
	{
		j = -1;
		while (av[i] != NULL)
			e.curr[++j]= ft_strdup(av[i++]);
	  sort_param(&e, ln_tab(e.curr));
		j++;
		while (j--)
	        empiler(&e, e.curr[j], "./");
		clean(e.curr);
		run(depiler(e.pile), &e);
	}
	clean_env(&e);
	return (0);
	}
