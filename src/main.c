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

void 	push2stack(t_env *e)
{
	t_lst 	*lst;
	char 		*tmp;
	size_t 	i;

	tmp = NULL;
	lst = e->file_cntr->lst;
	if (e->pile_cntr->first == NULL)
		tmp = "./";
	else
		tmp = e->pile_cntr->first->way;
	i = 0;
	printf("i = %zu, e->file_cntr->size = %zu\n", i, e->file_cntr->size);
	while (i < e->file_cntr->size)
	{
		printf("A\n");
		printf("device =  %c\n", device(lst->mode));
		if (device(lst->mode) == 'd' || device(lst->mode) == 'l')
			push(e->pile_cntr, lst->name, lst->way, &lst->mode);
		else
			ft_putendl(lst->name); //a prevoir si flag l
		i++;
	}
}

void		excute_argv(t_env *e, char **av, int start, int end)
{
	char *tmp;
	struct stat stt;

	while (start < end)
	{
		//stat = NULL;
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
		e->f_sort(e->file_cntr);
		push2stack(e);
	}
}

int				main(int ac, char **av)
{
	t_env		e;
	int 		i;
	char 		c;

	init_env(&e);
	if ((i = parse_flags(av, &e)) == ERROR)
		return (0);
	excute_argv(&e, av, i, ac);
	//run(&e);
	clean_env(&e);
	read(0,&c,1);
	return (0);
}
