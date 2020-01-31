/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:43 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/31 18:56:14 by crenaudi         ###   ########.fr       */
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
	{
		ft_putendl(ERROR_02);
		if (c == 'r')
			ft_putchar('\n');
	}
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

int			addfl(t_file_cntr *cntr, char *name, char *way)
{
	t_lst	*new;

	if ((new = new_elem(name, way)) == NULL)
		return (ERROR);
	if (cntr->lst == NULL)
		cntr->lst = new;
	else
	{
		new->next = cntr->lst;
		cntr->lst = new;
	}
	cntr->size += 1;
	return (SUCCESS);
}

static void	check_argv(t_env *e, t_file_cntr *wrong_av_cntr)
{
	t_lst	*tmp;
	char	c;

	if (e->file_cntr->lst == NULL && wrong_av_cntr->lst == NULL)
		push(e->pile_cntr, ".", NULL);
	if (wrong_av_cntr->lst != NULL)
	{
		c = 33;
		while (c <= 126)
		{
			tmp = wrong_av_cntr->lst;
			while (tmp)
			{
				if (tmp->name[0] == c)
					error(tmp->name, -1, ' ');
				tmp = tmp->next;
			}
			c++;
		}
		destroy_cntr_file(wrong_av_cntr);
	}
	ft_memdel((void **)(&wrong_av_cntr));
}

static void	excute_argv(t_env *e, char **av, int on, int to)
{
	char		*tmp;
	struct stat	stt;
	t_file_cntr	*wrong_av_cntr;

	wrong_av_cntr = init_file_cntr();
	while (on < to)
	{
		tmp = (av[on][0] == '/') ?
			ft_strdup(av[on]) : ft_strjoin("./", av[on]);
		if (!(stat(tmp, &stt)) && e->need_way++ >= 0)
			addfl(e->file_cntr, av[on], (av[on][0] == '/') ? NULL : "./");
		else
			addfl(wrong_av_cntr, av[on], NULL);
		ft_strdel(&tmp);
		on++;
	}
	check_argv(e, wrong_av_cntr);
	if (e->file_cntr->lst != NULL)
	{
		e->file_cntr->lst = topdownmergesort(e, e->file_cntr->lst,
			e->file_cntr->size);
		push2stack(e, "./");
		destroy_lst(&e->file_cntr->lst);
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
