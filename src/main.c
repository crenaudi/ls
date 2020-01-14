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

static void		check_wrong_av(char **wrong)
{
	int i;

	i = 0;
	if (wrong[i][0] != 0)
	{
		sort_base(NULL, wrong, ln_tab(wrong));
		while (wrong[i][0] != 0)
				error(wrong[i++], -1, ' ');
		clean(wrong);
	}
	clean_ptr((void **)(&wrong));
}

void check_argv(char **argv, t_env *e, int i, int len)
{
	char		*tmp;
	char		**wrong;
	int			j;
	int			k;

	j = -1;
	k = 0;
	wrong = init_file();
	if (!(e->buf = (struct stat *)malloc(sizeof(struct stat) * (len))))
		return ;
	while (++i < len)
	{
		tmp = ft_strjoin((argv[i][0] == '/') ? argv[i] : "./", argv[i]);
		if (!(lstat(tmp, &e->buf[k])))
			ft_strcpy(e->current[k++], argv[i]);
		else
			ft_strcpy(wrong[++j], argv[i]);
		ft_strdel(&tmp);
	}
	check_wrong_av(wrong);
}

int 	push_stack(t_env *e, char **argv, int start, int len)
{
	int 	i;

	i = -1;
	check_argv(argv, e, start - 1, len);
	e->f_sort(e->buf, e->current, ln_tab(e->current));
	while (e->current[++i][0] != 0)
	{
			if (device(e->buf[i]) == 'l' && e->current[i][ft_strlen(e->current[i]) - 1] != '/')
				print_lnk(e->buf[i], e->current[i], e->pile);
			else if (e->current[i][0] != '-' && (device(e->buf[i]) == 'd' || device(e->buf[i]) == 'l'))
			{
				(e->current[i][0] == '/') ? push(e->pile, e->current[i], NULL)
					: push(e->pile, argv[i], "./");
			}
			else
				ft_putendl(e->current[i]);
	}
	clean(e->current);
	if (e->pile->first == NULL)
		push(e->pile, ".", NULL);
	ft_putchar('\n');
	return (i);
}

int				main(int ac, char **av)
{
	t_env		e;
	int 		i;
	char 		c;

	init_env(&e);
	if ((i = parse_flags(av, &e)) == ERROR)
		return (0);
	if (push_stack(&e, av, i, ac) == ERROR)
		printf("pb dans push stack\n");
	afficher_pile(e.pile);
	//run(&e);
	clean_env(&e);
	read(0,&c,1);
	return (0);
}
