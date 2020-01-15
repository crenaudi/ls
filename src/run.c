/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:32 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/09 20:19:02 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	check_permission(t_elem *elem)
{
	char	*doc;

	doc = NULL;
	doc = ft_strjoin(elem->way, elem->name);
	lstat(doc, elem->stat);
	if (ft_strcmp(elem->name, ".") != 0 && ft_strcmp(elem->name, "..") != 0)
	{
		if ((elem->stat->st_mode & S_IRUSR) != S_IRUSR)
		{
			ft_putstr(doc);
			ft_putendl(" :");
			error(elem->name, -2, NULL);
			ft_strdel(&doc);
			return (-1);
		}/*
		if (device_type(*elem->stat) != 'd')
		{
			if (device_type(*elem->stat) != 'c')
				clean_ptr((void *)(&doc));
				ft_putendl(elem->name);
				return (-1);
		}*/
	}
	ft_strdel(&doc);
	return (0);
}

static void	next_step(t_env *e, char *way)
{
	struct stat	*stat;
	int			i;

	stat = NULL;
	i = ln_tab(e->current);
	stat = stat_tab(e, way);
	e->f_sort(stat, e, ln_tab(e->current));
	if (e->recursive == 1)
	{
		while (i--)
			if (device_type(stat[i]) == 'd' && ft_strcmp(e->current[i], ".") != 0
				&& ft_strcmp(e->current[i], "..") != 0)
				empiler(e, e->current[i], ft_strdup(way));
	}
	e->f_print(stat, way, e);
	clean_ptr((void *)(&stat));
	clean(e->current);
}

static void	for_norme(DIR *dirp, t_env *e, t_elem *elem)
{
	struct dirent	*c;
	char			*tmp;
	char			*way;
	int				i;

	tmp = NULL;
	way = NULL;
	if (check_permission(elem) == 0)
	{
		i = -1;
		while ((c = readdir(dirp)) != NULL)
		{
			if (e->a == 1 || c->d_name[0] != '.')
				ft_strcpy(e->current[++i], c->d_name);
		}
		printf("i = %d\n", i);
		if (i >= 0)
		{
			tmp = ft_strjoin(elem->name, "/");
			next_step(e, way = ft_strjoin(elem->way, tmp));
			clean_ptr((void *)(&tmp));
		}
		if (i == -1 && e->recursive == 1)
		{
			print_way(tmp = ft_strjoin(elem->way, elem->name), e->recursive);
		}
		ft_strdel(&way);
		ft_strdel(&tmp);
		ft_strdel(&c);
	}
}

static int is_var(t_env *e, char *s)
{
	struct stat	stat;
	int		i;

	i = 0;
	lstat(s, &stat);
	if (device_type(stat) == 99)
	{
		while (s[++i] != '\0')
			if (s[i] == '/')
				return (0);
		print_c(stat, s, e);
		return (1);
	}
	return(0);
}
/*
void		run(t_elem *elem, t_env *e)
{
	DIR		*dirp;
	char	*tmp;

	dirp = NULL;
	tmp = NULL;
	tmp = ft_strjoin(elem->way, elem->name);
	if (is_var(e, tmp) == 0)
	{
		if ((dirp = opendir(tmp)) == NULL)
			error(elem->name, -1, NULL);
		else
			for_norme(dirp, e, elem);
		if (dirp != NULL)
			closedir(dirp);
	}
	clean_ptr((void *)(&tmp));
	clean_elem(elem);
	if (e->pile != NULL && e->pile->first != NULL)
		run(depiler(e->pile), e);
}*/
void        run(t_env *e)
{
    t_elem    *elem;
    DIR        *dirp;
    char    	*tmp;


    while ((elem = pop(e->pile)))
  {
      if ((tmp = ft_strjoin(elem->way, elem->name))
	    return FATAL_ERROR; // tmtc tacompri, faut quand même free toussa
      if (is_var(e, tmp) == 0)
      {
	    if ((dirp = opendir(tmp)) == NULL)
		  error(elem->name, -1, NULL);
	    else
	   {
		  for_norme(dirp, e, elem);
		  closedir(dirp);
	  }
      }
      ft_strdel(&tmp);
      clean_elem(elem);
  }
}
