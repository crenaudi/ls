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

static int	check_permission(t_lst *elem)
{
	char	*doc;

	//printf("PERMISSION\n");
	doc = ft_strjoin(elem->way, elem->name);
	if (ft_strcmp(elem->name, ".") != 0 && ft_strcmp(elem->name, "..") != 0)
	{
		if ((elem->st_mode & S_IRUSR) != S_IRUSR)
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

static void	sort_push_print(t_env *e, char *tmp)
{
	//printf("SORT PUSH PRINT\n");
	e->f_sort(e->file_cntr);
	if (e->recursive == 1)
	{
		push2stack(e);
		print_way(tmp, e->recursive);
	}
	e->f_print(e, tmp);
	ft_strdel(&tmp);
	destroy_lst(e->file_cntr->lst);
	e->file_cntr->size = 0;
}

static void	read_file(DIR *dirp, t_env *e, t_lst *file)
{
	struct dirent	*c;
	struct stat		stt;
	char			*tmp;
	char			*way;

	//printf("READ FILE\n");
	if (check_permission(file) == 0)
	{
		while ((c = readdir(dirp)) != NULL)
		{
			lstat(tmp = ft_strjoin(file->way, c->d_name), &stt);
			way = ft_strjoin(tmp, "/");
			if (e->a == 1 || c->d_name[0] != '.')
				add2file(e->file_cntr, c->d_name, file->way, &stt.st_mode);
			ft_strdel(&tmp);
			ft_strdel(&way);
		}
		if (e->file_cntr->lst != NULL)
			sort_push_print(e, ft_strjoin(file->way, file->name));
		ft_strdel(&way);
		ft_strdel(&tmp);
		free(c);
	}
}

static int is_var(t_env *e, t_lst *elem, char *s)
{
	struct stat		stt;
	unsigned int 	str[2];
	unsigned int 	nb[2];
	int			i;

	//printf("IS VAR\n");
	i = 0;
	lstat(s, &stt);
	if (device(stt.st_mode) == 99 && e->l == 1)
	{
		while (s[++i] != '\0')
			if (s[i] == '/')
				return (0);
		stt = add_stat(elem);
		max_st_nb(&stt, 1, &nb[2]);
		max_st_str(&stt, 1, &str[2]);
		ft_putinfo(stt, elem->name, nb, str);
		if (e->pile_cntr->first != NULL)
			ft_putchar('\n');
		return (1);
	}
	return (0);
}

void        run(t_env *e)
{
	t_lst	*elem;
	DIR 	*dirp;
	char	*tmp;

	while ((elem = pop(e->pile_cntr)))
	{
		//printf("RUN : %s\n", elem->name);
      	tmp = ft_strjoin(elem->way, elem->name); // tmtc tacompri, faut quand même free toussa
      	if (is_var(e, elem, tmp) == 0)
      	{
	    		if ((dirp = opendir(tmp)) == NULL)
		  		error(elem->name, -1, 'o');
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
