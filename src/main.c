/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:43 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/09 20:13:41 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		excute_argv(t_env *e, char **av, int on, int to)
{
	char 		*tmp;
	struct stat stt;
	int 		hav_wrg;

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
		TopDownMergeSort(e, e->file_cntr->lst, e->file_cntr->size);
		push2stack(e, "./");
		destroy_lst(e->file_cntr->lst);
		e->file_cntr->size = 0;
	}
}

int			main(int ac, char **av)
{
	t_env		e;
	int 		i;
	char 		c;

	init_env(&e);
	if ((i = parse_flags(av, &e)) == ERROR)
		return (0);
	excute_argv(&e, av, i, ac);
	run(&e);
	clean_env(&e);
	read(0,&c,1);
	return (0);
}
