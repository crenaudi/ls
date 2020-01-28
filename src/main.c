/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:43 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/28 20:07:04 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		error(char *av, int error, char c)
{
	ft_putstr(LS);
	if (error != -3)
		ft_putstr(av);
	if (error == -1)
		ft_putendl(ERROR_01);
	if (error == -2)
		ft_putendl(ERROR_02);
	if (error == -3)
	{
		ft_putstr(ERROR_03);
		ft_putchar(c);
		ft_putchar('\n');
		ft_putstr(USAGE);
		ft_putendl(ERROR_06);
	}
	if (error == 1)
		ft_putendl(ERROR_04);
}

static void	excute_argv(t_env *e, char **av, int on, int to)
{
	char		*tmp;
	struct stat	stt;
	int			hav_wrg;

	hav_wrg = 0;
	while (on < to)
	{
		tmp = (av[on][0] == '/') ?
			ft_strdup(av[on]) : ft_strjoin("./", av[on]);
		if (!(stat(tmp, &stt)))
			addfl(e->file_cntr, av[on], (av[on][0] == '/') ? NULL : "./");
		else if (++hav_wrg)
			error(av[on], -1, ' ');
		ft_strdel(&tmp);
		on++;
	}
	if (e->file_cntr->lst == NULL)
		(hav_wrg == 0) ? push(e->pile_cntr, ".", NULL) : hav_wrg == 0;
	else
	{
		topdownmergesort(e, e->file_cntr->lst, e->file_cntr->size);
		push2stack(e, "./");
		destroy_lst(e->file_cntr->lst);
		e->file_cntr->size = 0;
	}
}

int			main(int ac, char **av)
{
	t_env		e;
	int			i;

	init_env(&e);
	if ((i = parse_flags(av, &e)) == ERROR)
		return (0);
	excute_argv(&e, av, i, ac);
	run(&e);
	clean_env(&e);
	return (0);
}
