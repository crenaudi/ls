/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:43 by crenaudi          #+#    #+#             */
/*   Updated: 2019/12/18 00:34:28 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		test_argv(char *wrong, struct stat buf)
{
	if (device_type(buf) != 102)
		ft_putendl(wrong);
	else
		error(wrong, -1, NULL);
	ft_putchar('\n');
}

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
	j++;
	while (j--)
	{
		if (device_type(buf[j]) != 100)
			test_argv(e->curr[j], buf[j]);
		else
			empiler(e, e->curr[j], ft_strdup("./"));
	}
	clean(e->curr);
	clean_ptr((void **)(&buf));
	run(depiler(e->pile), e);
}

int				main(int ac, char **av)
{
	t_env		e;
	int			i;
	char		c;

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
	read(0, &c, 1);
	return (0);
}
