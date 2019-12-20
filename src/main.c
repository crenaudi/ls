/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:43 by crenaudi          #+#    #+#             */
/*   Updated: 2019/12/20 15:28:46 by crenaudi         ###   ########.fr       */
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
		if (device_type(buf[j]) != 100)
			test_argv(e->curr[j], buf[j], &file, &none);
		else
			empiler(e, e->curr[j], ft_strdup("./"));
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

int				main(int ac, char **av)
{
	t_env		e;
	int			i;
	int			j;

	j = -1;
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
	{
		while (av[i] != NULL)
			ft_strcpy(e.curr[++j], av[i++]);
		norme_main(&e, j + 1);
	}
	clean_env(&e);
	return (0);
}
