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

static void		test_argv(char *wrg, struct stat buf, char **file, char **none)
{
	char	*add_slash;
	char	*tmp;

	tmp = NULL;
	add_slash = ft_strjoin(wrg, "\n");
	if (device_type(buf) != 102)
	{
		tmp = *file;
		*file = ft_strjoin(add_slash, tmp);
	}
	else
	{
		tmp = *none;
		*none = ft_strjoin(add_slash, tmp);
	}
	clean_ptr((void *)(&add_slash));
	clean_ptr((void *)(&tmp));
}

static void		print_argv_error(char **none)
{
	char	**tab;
	int		i;

	i = -1;
	tab = NULL;
	if (none != NULL)
	{
		tab = ft_strsplit(*none, '\n');
		while (tab[++i] != NULL)
			error(tab[i], -1, NULL);
		clean_ptr((void *)(none));
	}
}

static void		print_argv_file(t_env *e, char **file)
{
	char		**tab2;
	struct stat	*buf;
	int			i;

	i = -1;
	tab2 = NULL;
	if (e->l == 1)
	{
		tab2 = ft_strsplit(*file, '\n');
		buf = buf_tab2(tab2, "./");
		all_file(buf, tab2);
		clean_ptr((void *)(&buf));
	}
	else
		ft_putstr(*file);
	clean_ptr((void *)(file));
	if (e->pile->first != NULL)
		ft_putchar('\n');
}

static void		norme_main(t_env *e, int j)
{
	char		*file;
	char		*none;
	struct stat	*buf;

	buf = NULL;
	file = NULL;
	none = NULL;
	buf = buf_tab(e, "./");
	e->f_sort(buf, e, ln_tab(e->curr));
	while (j--)
	{
		if (device_type(buf[j]) == 100 || device_type(buf[j]) == 99)
			empiler(e, e->curr[j],
					(e->curr[j][0] == '/') ? NULL : ft_strdup("./"));
		else
			test_argv(e->curr[j], buf[j], &file, &none);
	}
	clean(e->curr);
	clean_ptr((void **)(&buf));
	if (none != NULL)
		print_argv_error(&none);
	if (file != NULL)
		print_argv_file(e, &file);
	if (e->pile->first != NULL)
		run(depiler(e->pile), e);
}

void		add_pile_stack(t_pile *pile, char **argv)
{

	int i;
	struct stat	*buf;

	i = 0;
	buf = buf_tab(argv, way);
	while (argv[++i] != NULL)
		if (buf[0] != '-')
			(argv[i][0] == '/') ? empiler(init, argv[i], "./")
				: empiler(init, argv[i], NULL);
	if (pile == NULL)
		empiler(init, ".", NULL);
}

int				main(int ac, char **av)
{
	t_env		e;
	t_pile 	*init;
	/*int			i;
	int			j;*/
	char c;

	//j = -1;
	i = 0;
	init_env(&e);
	init = init_pile;
	if (parse_flags(ac, av, &e) == 0 && ac != 1)
		add_first_stack(init, av);
	else
		empiler(init, ".", NULL);

/*
	else
	{
		while (av[i] != NULL)
			ft_strcpy(e.curr[++j], av[i++]);
		norme_main(&e, j + 1);
	}*/
	clean_env(&e);
	read(0,&c,1);
	return (0);
}
