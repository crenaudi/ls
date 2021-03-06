/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:32 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/31 18:50:51 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		check_permission(t_lst *elem)
{
	char		*doc;
	struct stat	stt;

	doc = ft_strjoin(elem->way, elem->name);
	if (ft_strcmp(elem->name, ".") != 0 && ft_strcmp(elem->name, "..") != 0)
	{
		stat(doc, &stt);
		if ((stt.st_mode & S_IRUSR) != S_IRUSR)
		{
			ft_putstr(doc);
			ft_putendl(" :");
			error(elem->name, -2, 'o');
			ft_strdel(&doc);
			return (-1);
		}
	}
	ft_strdel(&doc);
	return (0);
}

static void		sort_push_print(t_env *e, char *tmp)
{
	t_lst	*lst;
	char	*way;

	lst = e->file_cntr->lst;
	way = NULL;
	if (ft_strcmp(tmp, "./") != 0)
		way = ft_strjoin(tmp, "/");
	else
		way = ft_strdup(tmp);
	while (lst)
	{
		ft_bzero(lst->way, sizeof(char) * PATH_MAX);
		ft_strcpy(lst->way, way);
		lst = lst->next;
	}
	e->file_cntr->lst = topdownmergesort(e, e->file_cntr->lst,
			e->file_cntr->size);
	if (e->recursive == 1)
		push2stack(e, way);
	e->f_print(e, tmp);
	ft_strdel(&tmp);
	ft_strdel(&way);
	destroy_lst(&e->file_cntr->lst);
	e->file_cntr->size = 0;
}

static void		read_file(DIR *dirp, t_env *e, t_lst *file)
{
	struct dirent	*c;
	struct stat		stt;
	char			*tmp;

	if (check_permission(file) == 0)
	{
		while ((c = readdir(dirp)) != NULL)
		{
			stat(tmp = ft_strjoin(file->way, c->d_name), &stt);
			if (e->a == 1 || c->d_name[0] != '.')
				addfl(e->file_cntr, c->d_name, file->way);
			ft_strdel(&tmp);
		}
		if (e->file_cntr->lst != NULL)
		{
			tmp = (file->name[0] == '/') ? ft_strdup(file->name)
				: ft_strdup("./");
			sort_push_print(e, (file->way[0] == 0) ? ft_strdup(tmp) :
				ft_strjoin(file->way, file->name));
		}
		ft_strdel(&tmp);
		free(c);
	}
}

static int		is_var(t_env *e, t_lst *elem, char *s)
{
	struct stat		stt;
	unsigned int	str[2];
	unsigned int	nb[2];
	int				i;

	i = 0;
	lstat(s, &stt);
	if (device(stt.st_mode) == 'l' && e->l == 1)
	{
		nb[0] = ft_nblen(stt.st_nlink);
		nb[1] = ft_nblen(stt.st_size);
		str[0] = 0;
		str[1] = 0;
		ft_putinfo(stt, elem->name, nb, str);
		if (e->pile_cntr->first != NULL)
			ft_putchar('\n');
		return (1);
	}
	return (0);
}

void			run(t_env *e)
{
	t_lst	*elem;
	DIR		*dirp;
	char	*tmp;

	tmp = NULL;
	elem = NULL;
	while ((elem = pop(e->pile_cntr)))
	{
		if (is_var(e, elem, tmp = ft_strjoin(elem->way, elem->name)) == 0)
		{
			if ((dirp = opendir(tmp)) == NULL)
			{
				if (e->recursive == 1)
					print_way(tmp, 1);
				error(elem->name, -2, 'r');
			}
			else
			{
				read_file(dirp, e, elem);
				closedir(dirp);
			}
		}
		ft_strdel(&tmp);
		destroy_elem(elem);
	}
}
