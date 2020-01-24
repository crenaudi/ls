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

void		excute_argv(t_env *e, char **av, int start, int end)
{
	char *tmp;
	struct stat stt;

	while (start < end)
	{
		tmp = (av[start][0] == '/') ?
			ft_strdup(av[start]) : ft_strjoin("./", av[start]);
		if (!(stat(tmp, &stt)))
			add2file(e->file_cntr, av[start], (av[start][0] == '/') ?
				NULL : "./", &stt.st_mode);
		else
			error(av[start], -1, ' ');
		ft_strdel(&tmp);
		start++;
	}
	if (e->file_cntr->lst == NULL)
		push(e->pile_cntr, ".", NULL, NULL);
	else
	{
		TopDownMergeSort(e, e->file_cntr->lst, e->file_cntr->size);
		push2stack(e);
		destroy_lst(e->file_cntr->lst);
		e->file_cntr->size = 0;
	}
}

int				main(int ac, char **av)
{
	t_env		e;
	int 		i;
	char 		c;

	printf("MAIN\n");
	init_env(&e);
	if ((i = parse_flags(av, &e)) == ERROR)
		return (0);
	excute_argv(&e, av, i, ac);
	run(&e);
	clean_env(&e);
	read(0,&c,1);
	return (0);
}
