/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:43 by crenaudi          #+#    #+#             */
/*   Updated: 2019/12/10 14:19:38 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		norme_main(t_env *e, char **av, int i)
{
	int			j;
	struct stat	*buf;

	j = -1;
	buf = NULL;
	while (av[i] != NULL)
		 ft_strcpy(e->curr[++j], av[i++]);
	buf = buf_tab(e, "./");
	e->f_sort(buf, e, ln_tab(e->curr));
	//mettre les dossiers non existant en premier
	j++;
	while (j--)
		empiler(e, e->curr[j], ft_strdup("./"));
	clean(e->curr);
	clean_ptr((void **)(&buf));
	run(depiler(e->pile), e);
}

int				main(int ac, char **av)
{
	t_env		e;
	int			i;

	init_env(&e);
	i = parse_flags(ac, av, &e);
	if (i == -1)
		error(NULL, -3, &e.illegal);
	else if (av[i] == NULL)
	{
		empiler(&e, ".", NULL);
		run(depiler(e.pile), &e);
	}
	else
		norme_main(&e, av, i);
	clean_env(&e);
	while (1)
		i = 0;
	return (0);
}
