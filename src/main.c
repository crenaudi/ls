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

static void		print_wrongORfile(char **str, int is_file)
{
	int i;

	i = -1;
	if (str[0][0] != 0)
	{
		sort_base(NULL, str, ln_tab(str));
		while (str[++i][0] != 0)
				(is_file == 0) ? ft_putendl(str[i]) : error(str[i], -1, ' ');
		clean(str);
	}
	ft_memdel((void **)(&str));
}

static void init(int index[4])
{
	index[0] = -1;
	index[1] = -1;
	index[2] = 0;
	index[3] = 0;
}

int check_argv(char **argv, t_env *e, int i, int len)
{
	char		*tmp;
	char		**wrong;
	char 		**file;
	int 		index[4];

	wrong = init_file();
	file = init_file();
	init(index);
	while (++i < len)
	{
		tmp = ft_strjoin((argv[i][0] == '/') ? NULL : "./", argv[i]);
		if (!(stat(tmp, &e->stat[index[2]])))
		{
			if (device(e->stat[index[2]]) == 'd' || device(e->stat[index[2]]) == 'l')
				ft_strcpy(e->current[index[3]++], argv[i]);
			else
				ft_strcpy(file[++index[0]], argv[i]);
			index[2]++;
		}
		else
			ft_strcpy(wrong[++index[1]], argv[i]);
		ft_strdel(&tmp);
	}
	print_wrongORfile(wrong, -1);
	print_wrongORfile(file, 0);
	return (index[1]);
}

void 	push_stack(t_env *e, char **argv, int start, int end)
{
	int 	only_wrong;
	int 	len;
	int 	i;

	i = 0;
	if (!(e->stat = (struct stat *)malloc(sizeof(struct stat) * (end))))
		return ;
	only_wrong = check_argv(argv, e, start - 1, end);
	len = ln_tab(e->current);
	e->f_sort(e->stat, e->current, len);
	while (i <= --len)
		(e->current[len][0] == '/') ? push(e->pile, e->current[len], NULL)
				: push(e->pile, e->current[len], "./");
	clean(e->current);
	if (e->pile->first == NULL && only_wrong == -1)
		push(e->pile, ".", NULL);
	ft_memdel((void **)&e->stat);
	ft_putchar('\n');
}

int				main(int ac, char **av)
{
	t_env		e;
	int 		i;
	char 		c;

	init_env(&e);
	if ((i = parse_flags(av, &e)) == ERROR)
		return (0);
	push_stack(&e, av, i, ac);
	afficher_pile(e.pile);
	//run(&e);
	clean_env(&e);
	read(0,&c,1);
	return (0);
}
