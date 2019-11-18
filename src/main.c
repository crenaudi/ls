/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:43 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/02 13:32:42 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	main(int ac, char **av)
{
	t_env		e;
	int		i;
	int		j;
	struct stat	*buf;
	t_elem	*one;

	init_env(&e);
	i = parse_flags(ac, av, &e);
	if (av[i] == NULL)
	{
		if (!(one = (t_elem *)malloc(sizeof(t_elem))))
			exit(EXIT_FAILURE);
		one->name[0] = '.';

		manage(one, &e);
		//free(one);
	}
	else
	{
		j = -1;
		while (av[i] != NULL)
		{
			e.curr[++j]= ft_strdup(av[i++]);
			printf("%s\n", e.curr[j]);
		}
		buf = add_buf2pile(&e, "./", 1);
		free(buf);
		clean(e.curr);
		manage(unstack(e.pile), &e);
	}
	clean_env(&e);
	return (0);
}
