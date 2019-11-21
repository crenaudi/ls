/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:43 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/19 15:21:58 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	add_flags(char *flags, t_env *e)
{
	char 	c;
	int 	i;

	c = 32;/*
	if (flags == NULL)
	{
		e->f_sort = &sort_base;
		e->f_print = &ls_simple;
		return (0);
	}*/
	e->a = (ft_strchr(flags, 'a') != NULL) ? 1 : 0;
	e->reccursive = (ft_strchr(flags, 'R') != NULL) ? 1 : 0;
	e->f_print = (ft_strchr(flags, 'l') != NULL) ? &ls_all : &ls_simple;
	if (ft_strchr(flags, 'r') != NULL && ft_strchr(flags, 't') != NULL)
		e->f_sort = &sort_rt;
	else if (ft_strchr(flags, 'r') != NULL)
		e->f_sort = &sort_r;
	else if (ft_strchr(flags, 't') != NULL)
		e->f_sort = &sort_t;
	else
		e->f_sort = &sort_base;
	while (++c <= '~')
	{
		i = -1;
		while (flags[++i] != '\0')
			if (flags[i] == c && flags[i] != 'a' && flags[i] != 'R' && flags[i] != 'l'
				&& flags[i] != 't' && flags[i] != 'r' && flags[i] != '-')
				{
					e->illegal = c;
					return (-1);
				}
	}
	return (0);
}

int			parse_flags(int ac, char **av, t_env *e)
{
	char	*flg;
	int	i;

	i = 1;
	flg = NULL;
	if (ac != 1 && av[i][0] == '-' && av[i][1] != '-')
	{
		while (av[i] != NULL && (av[i][0] == '-' && av[i][1] != '-'))
		{
			if (ft_strchr(ft_strsub(av[i], 1, ft_strlen(av[i])), '-') != NULL)
			{
				e->illegal = '-';
				return (-1);
			}
			flg = (flg == NULL) ? ft_strdup(av[i]) : ft_strjoin(flg, av[i]);
			i++;
		}
		if (add_flags(flg, e) == -1)
			return (-1);
	}
	else
	{
		e->f_sort = &sort_base;
		e->f_print = &ls_simple;
	}
	return (i);
}

int			ln_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i][0]!='\0')
		i++;
	return(i);
}

struct stat	*buf_tab(t_env *e, char *way)
{
	struct stat	*buf;
	int			i;
	int			len;

	i = -1;
	len = ln_tab(e->curr);
	if (!(buf = (struct stat *)malloc(sizeof(struct stat) * (len))))
		return (NULL);
	while (++i < len)
	{
		if (lstat(ft_strjoin(way, e->curr[i]), &buf[i]) != 0)
			error(e->curr[i], 0, NULL);
	}
	return (buf);
}
