/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:32 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/19 20:18:40 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	check_permission(t_elem *elem)
{
	const char	*doc;

	doc = (elem->way == NULL) ? elem->name : ft_strjoin(elem->way, elem->name);
	if (elem->name[0] != '.' && (elem->buf->st_mode & S_IRUSR) != S_IRUSR)
	{
		ft_putendl(ft_strjoin(doc, " :"));
		error(elem->name, -2);
		return (-1);
	}
	if (elem->name[0] != '.' && device_type(*elem->buf) != 'd')
	{
			ft_putendl(elem->name);
			return (-1);
	}
	return (0);
}

static void	next_step(t_env *e, char *way, char *dir)
{
	struct stat	*buf;
	int			i;

	i = ln_tab(e->curr);
	way = (way == NULL) ? dir : ft_strjoin(way, dir);
	buf = buf_tab(e, way);
	e->f_sort(buf, e, ln_tab(e->curr));
	if (e->reccursive == 1)
	{
    while (i--)
			if (device_type(buf[i]) == 'd')
        empiler(e->pile, e->curr[i], way);
	}
	e->f_print(buf, way, e);
	free(buf);
	clean(e->curr);
}

void		run(t_elem *elem, t_env *e)
{
	DIR				*dirp;
	struct dirent	*c;
	int				i;

	if (check_permission(elem) == 0)
	{
		if ((dirp = opendir((elem->way == NULL) ? elem->name
			: ft_strjoin(elem->way, elem->name))) == NULL)
			error(elem->name, -1);
		else
		{
			i = -1;
			while ((c = readdir(dirp)) != NULL)
				if (e->a == 1 || c->d_name[0] != '.')
					ft_strcpy(e->curr[++i], c->d_name);
			if (i >= 0)
				next_step(e, elem->way, ft_strjoin(elem->name, "/"));
			if (i == -1 && e->reccursive == 1)
				print_way(ft_strjoin(elem->way, elem->name));
		}
	}
	free_elem(elem);
	if (e->pile != NULL && e->pile->first != NULL)
		run(depiler(e->pile), e);
}
