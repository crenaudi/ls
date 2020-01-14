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

int			parse_flags(char **av, t_env *e)
{
	char	*tmp;
	int 	i;
	int 	index;

	i = -1;
	index = 1;
	tmp = NULL;
	while (av[index] != NULL && av[index][0] == '-' && av[index][1] != '-' && av[index][1] != '\0')
	{
		tmp = ft_strjoin(tmp, ft_strsub(av[index], 1, ft_strlen(av[index])));
		index++;
	}
	if (tmp != NULL)
	{
		type_flags(tmp, e);
		while (tmp[++i] != '\0')
			if (tmp[i] != 'a' && tmp[i] != 'R' && tmp[i] != 'r' && tmp[i] != 'a'
				&& tmp[i] != 't' && tmp[i] != 'l')
			{
						error(NULL, -3, tmp[i]);
						ft_strdel(&tmp);
						return (ERROR);
			}
			ft_strdel(&tmp);
	}
	return (index);
}

void buf_tab(char *way, t_env *e)
{
	char		*tmp;
	int			i;
	int			len;

	i = -1;
	len = ln_tab(e->current);
	if (!(e->buf = (struct stat *)malloc(sizeof(struct stat) * (len))))
		return;
	while (++i < len)
	{
		tmp = ft_strjoin((e->current[i][0] == '/') ? e->current[i] : way, e->current[i]);
		while (!(lstat(tmp, &e->buf[i])))
		{
			ft_strdel(&tmp);
			i++;
			tmp = ft_strjoin((e->current[i][0] == '/') ? e->current[i] : way, e->current[i]);
		}
		ft_strdel(&tmp);
	}
}
