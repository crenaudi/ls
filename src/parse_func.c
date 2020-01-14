/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:43 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/09 19:28:50 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void			type_flags(char *tmp, t_env *e)
{
	e->a = (ft_strchr(tmp, 'a') != NULL) ? 1 : 0;
	e->reccursive = (ft_strchr(tmp, 'R') != NULL) ? 1 : 0;
	e->f_print = (ft_strchr(tmp, 'l') != NULL) ? &ls_all : &ls_simple;
	e->l = (ft_strchr(tmp, 'l') != NULL) ? 1 : 0;
	if (ft_strchr(tmp, 'r') != NULL && ft_strchr(tmp, 't') != NULL)
		e->f_sort = &sort_rt;
	else if (ft_strchr(tmp, 'r') != NULL)
		e->f_sort = &sort_r;
	else
		e->f_sort = (ft_strchr(tmp, 't') != NULL) ? &sort_t : &sort_base;
}

int			parse_flags(char **av, t_env *e)
{
	char	**argv;
	char	*tmp;
	int 	i;
	int 	index;

	i = -1;
	index = 0;
	argv = av;
	tmp = NULL;
	while (argv[++index] != NULL && argv[index][0] == '-' && argv[index][1] != '-')
		tmp = ft_strjoin(tmp, argv[index]);
	type_flags(tmp, e);
	while (tmp[++i] != '\0')
		if (tmp[i] != 'a' && tmp[i] != 'R' && tmp[i] != 'r' && tmp[i] != 'a'
			&& tmp[i] != 't' && tmp[i] != 'l')
		{
					free(tmp);
					error(NULL, -3, &tmp[i]);
					return(ERROR);
		}
		free(tmp);
		return(SUCCESS);
}

/*
int			add_flags(char *flg, t_env *e, char c)
{
	int		i;

	e->a = (ft_strchr(flg, 'a') != NULL) ? 1 : 0;
	e->reccursive = (ft_strchr(flg, 'R') != NULL) ? 1 : 0;
	e->f_print = (ft_strchr(flg, 'l') != NULL) ? &ls_all : &ls_simple;
	e->l = (ft_strchr(flg, 'l') != NULL) ? 1 : 0;
	if (ft_strchr(flg, 'r') != NULL && ft_strchr(flg, 't') != NULL)
		e->f_sort = &sort_rt;
	else if (ft_strchr(flg, 'r') != NULL)
		e->f_sort = &sort_r;
	else
		e->f_sort = (ft_strchr(flg, 't') != NULL) ? &sort_t : &sort_base;
	while (++c <= '~')
	{
		i = -1;
		while (flg[++i] != '\0')
			if (flg[i] == c && flg[i] != 'a' && flg[i] != 'R' && flg[i] != 'l'
			&& flg[i] != 't' && flg[i] != 'r' && flg[i] != '-')
			{
				clean_ptr((void *)(&flg));
				e->illegal = c;
				return (-1);
			}
	}
	return (0);
}

static int	norme(t_env *e, int i, char **av, char *flg)
{
	char *tmp;

	tmp = ft_strsub(av[i], 1, ft_strlen(av[i]));
	if (ft_strchr(tmp, '-') != NULL)
	{
		e->illegal = '-';
		clean_ptr((void *)(&flg));
		clean_ptr((void *)(&tmp));
		return (-1);
	}
	clean_ptr((void *)(&tmp));
	return (0);
}

static void	name_funct(t_env *e)
{
	e->f_sort = &sort_base;
	e->f_print = &ls_simple;
	e->l = 0;
}

int			parse_flags(int ac, char **av, t_env *e)
{
	char	*flg;
	int		i;

	i = 1;
	flg = NULL;
	if (ac != 1 && av[i][0] == '-' && ft_strcmp(av[i], "--") != 0
			&& ft_strcmp(av[i], "-") != 0)
	{
		while (av[i] != NULL && av[i][0] == '-' && ft_strcmp(av[i], "--") != 0
				&& ft_strcmp(av[i], "-") != 0)
		{
			if (norme(e, i, av, flg) == -1)
				return (-1);
			flg = ft_strjoin(flg, av[i++]);
		}
		if (flg != NULL && add_flags(flg, e, 32) == -1)
			return (-1);
	}
	else
		name_funct(e);
	if (ft_strcmp(av[i], "--") == 0)
		i++;
	clean_ptr((void *)(&flg));
	return (i);
}
*/
struct stat	*buf_tab(char **argv, char *way)
{
	struct stat	*buf;
	char		*tmp;
	int			i;
	int			len;

	i = -1;
	buf = NULL;
	len = ln_tab(argv);
	if (!(buf = (struct stat *)malloc(sizeof(struct stat) * (len))))
		return (NULL);
	while (++i < len)
	{
		tmp = ft_strjoin((argv[i][0] == '/') ? NULL : way, argv[i]);
		lstat(tmp, &buf[i]);
		clean_ptr((void *)(&tmp));
	}
	return (buf);
}
