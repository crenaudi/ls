/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:32 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/02 13:35:30 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	check_permission(t_elem *elem)
{
	const char	*doc;
	struct stat	buff;

	doc = (elem->way == NULL) ? elem->name : ft_strjoin(elem->way, elem->name);
	if (elem->buf == NULL)
	{
		if (lstat(doc, &buff) != 0)
			error(elem->name, -2);
	}
	else
		buff = *elem->buf;
	if ((buff.st_mode & S_IFDIR) == S_IFDIR
			&& (buff.st_mode & S_IRUSR) != S_IRUSR)
	{
		ft_putendl(ft_strjoin(doc, " :"));
		error(elem->name, -2);
		return (-1);
	}
	return (0);
}

static void flag_step(t_env *e, char *way, char *dir)
{
      struct stat *buf;
/*
      i = -1;
      way = (way == NULL) ? dir : ft_strjoin(way, dir);
      len = ln_tab(e->curr);
      if (!(buf = (struct stat *)malloc(sizeof(struct stat) * (len))))
            return;
      while (++i < len)
      {

            if (lstat(ft_strjoin(way, e->curr[i]), &buf[i]) != 0)
                  error(e->curr[i], 0);
      }

      tab2pile(e, way, buf, 0, len);
      */
	way = (way == NULL) ? dir : ft_strjoin(way, dir),
      buf = add_buf2pile(e, way, 0);
      e->f_sort(buf, e, ln_tab(e->curr));
      e->f_print(buf, way, e);
      free(buf);
      clean(e->curr);
}

void		manage(t_elem *dir, t_env *e)
{
	DIR				*dirp;
	struct dirent	*c;
	int				i;

	printf("%s \n", dir->name);
	if ((dirp = opendir((dir->way == NULL) ? dir->name
		: ft_strjoin(dir->way, dir->name))) == NULL)
	{
		error(dir->name, -1);
		return ;
	}
	printf("open dirp ok \n");
	if (check_permission(dir) == 0)
	{
		printf("check_permission ok \n");
		i = -1;
		while ((c = readdir(dirp)) != NULL)
			if (e->a == 1 || c->d_name[0] != '.')
				ft_strcpy(e->curr[++i], c->d_name);
		if (i > 0)
			flag_step(e, dir->way, ft_strjoin(dir->name, "/"));
		if (i == -1 && e->reccursive == 1)
			print_way(ft_strjoin(dir->way, dir->name));
	}
	free(dir);
	if (e->reccursive == 1 && e->pile->first != NULL)
		manage(unstack(e->pile), e);
}
