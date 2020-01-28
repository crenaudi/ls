/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:43 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/28 18:45:40 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		type_flags(char *tmp, t_env *e)
{
	e->a = (ft_strchr(tmp, 'a') != NULL) ? 1 : 0;
	e->recursive = (ft_strchr(tmp, 'R') != NULL) ? 1 : 0;
	e->f_print = (ft_strchr(tmp, 'l') != NULL) ? &ls_all : &ls_simple;
	e->l = (ft_strchr(tmp, 'l') != NULL) ? 1 : 0;
	if (ft_strchr(tmp, 'r') != NULL && ft_strchr(tmp, 't') != NULL)
		e->f_sort = &sort_rt;
	else if (ft_strchr(tmp, 'r') != NULL)
		e->f_sort = &sort_r;
	else
		e->f_sort = (ft_strchr(tmp, 't') != NULL) ? &sort_t : &sort_base;
}

char			*addflags(char **av, int *i)
{
	char	*sub;
	char	*tmp;
	char	*flg;

	sub = NULL;
	tmp = NULL;
	flg = NULL;
	while (av[*i] != NULL && av[*i][0] == '-' && av[*i][1] != '-'
		&& av[*i][1] != '\0')
	{
		sub = ft_strsub(av[*i], 1, ft_strlen(av[*i]));
		tmp = ft_strjoin(flg, sub);
		ft_strdel(&flg);
		flg = ft_strdup(tmp);
		ft_strdel(&tmp);
		ft_strdel(&sub);
		*i += 1;
	}
	return (flg);
}

int				parse_flags(char **av, t_env *e)
{
	char	*tmp;
	int		i;
	int		indx;

	i = -1;
	indx = 1;
	tmp = addflags(av, &indx);
	if (tmp != NULL)
	{
		type_flags(tmp, e);
		while (tmp[++i] != '\0')
			if (tmp[i] != 'a' && tmp[i] != 'R' && tmp[i] != 'r'
				&& tmp[i] != 'a' && tmp[i] != 't' && tmp[i] != 'l')
			{
				error(NULL, -3, tmp[i]);
				ft_strdel(&tmp);
				return (ERROR);
			}
	}
	ft_strdel(&tmp);
	return (indx);
}

size_t			ft_lstlen(t_lst *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
