/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:32 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/28 18:20:16 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	check_permission(t_elem *elem, t_pile *pile)
{
	char	*doc;

	doc = (elem->way == NULL) ? elem->name : ft_strjoin(elem->way, elem->name);
	lstat(doc, elem->buf);
	if (ft_strcmp(elem->name, ".") != 0 && ft_strcmp(elem->name, "..") != 0)
	{
		if ((elem->buf->st_mode & S_IRUSR) != S_IRUSR)
		{
			ft_putendl(doc = ft_strjoin(doc, " :"));
			error(elem->name, -2, NULL);
			if (pile == NULL && pile->first == NULL)
				clean_ptr((void **)(&doc));
			return (-1);
		}
		if (device_type(*elem->buf) != 'd')
		{
			if (pile == NULL && pile->first == NULL)
				clean_ptr((void **)(&doc));
			ft_putendl(elem->name);
			return (-1);
		}
	}
	if (pile == NULL && pile->first == NULL)
		clean_ptr((void **)(&doc));
	return (0);
}

static void	next_step(t_env *e, char *way, char *dir)
{
	struct stat	*buf;
	int			i;

	buf = NULL;
	i = ln_tab(e->curr);
	way = (way == NULL) ? dir : ft_strjoin(way, dir);
	buf = buf_tab(e, way);
	e->f_sort(buf, e, ln_tab(e->curr));
	if (e->reccursive == 1)
	{
		while (i--)
			if (device_type(buf[i]) == 'd' && ft_strcmp(e->curr[i], ".") != 0
				&& ft_strcmp(e->curr[i], "..") != 0)
				empiler(e, e->curr[i], way);
	}
	e->f_print(buf, way, e);
	if (e->pile == NULL && e->pile->first == NULL)
		clean_ptr((void **)(&way));
	clean_ptr((void **)(&buf));
	clean(e->curr);
}

static void	for_norme(DIR *dirp, t_env *e, t_elem *elem)
{
	struct dirent	*c;
	char					*tmp;
	int				i;

	tmp = NULL;
	c = NULL;
	if (check_permission(elem, e->pile) == 0)
	{

		i = -1;
		while ((c = readdir(dirp)) != NULL)
			if (e->a == 1 || c->d_name[0] != '.')
				ft_strcpy(e->curr[++i], c->d_name);
		tmp = (i >= 0) ? ft_strjoin(elem->name, "/") : ft_strjoin(elem->way, elem->name);
		if (i >= 0)
			next_step(e, elem->way, tmp);
		if (i == -1 && e->reccursive == 1)
			print_way(tmp);
		if (ft_strcmp(tmp, "./") != 0)
			clean_ptr((void **)(&tmp));
		clean_ptr((void **)(&c));
	}
}

void		run(t_elem *elem, t_env *e)
{
	DIR				*dirp;
	char 			*tmp;

	dirp = NULL;
	tmp = NULL;
	tmp = (elem->way == NULL) ? elem->name : ft_strjoin(elem->way, elem->name);
	if ((dirp = opendir(tmp)) == NULL)
		error(elem->name, -1, NULL);
	else
		for_norme(dirp, e, elem);
	if (dirp != NULL)
		closedir(dirp);
	clean_ptr((void **)(&elem));
	if (tmp[0] != '\0')
		clean_ptr((void **)(&tmp));
	if (e->pile != NULL && e->pile->first != NULL)
		run(depiler(e->pile), e);
}
