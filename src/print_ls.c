/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:10 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/28 18:33:31 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_way(char *way, int rec)
{
	int		i;
	int		tmp;
	int		idx;

	idx = (rec == 1 || way[0] == '/') ? 0 : 2;
	tmp = ft_strlen(way) - 1;
	i = (way[tmp] == '/') ? tmp : tmp + 1;
	if (ft_strcmp(way, "./") != 0)
	{
		while (idx < i)
			ft_putchar(way[idx++]);
		ft_putendl(":");
	}
}

void	ft_putinfo(struct stat stat, char *name, unsigned int nb_max[2],
	unsigned int str_max[2])
{
	struct passwd	*pwd;
	struct group	*grp;

	pwd = getpwuid(stat.st_uid);
	grp = getgrgid(stat.st_gid);
	ft_putchar(device(stat.st_mode));
	st_mode_type(stat.st_mode);
	(device(stat.st_mode) == 'c') ? nb_patern(nb_max[0], stat.st_blksize) :
		nb_patern(nb_max[0], stat.st_nlink);
	(pwd == NULL) ? id_patern(str_max[0], stat.st_uid) :
		str_patern(str_max[0], pwd->pw_name);
	(grp == NULL) ? id_patern(str_max[0], stat.st_gid) :
		str_patern(str_max[1], grp->gr_name);
	nb_patern(nb_max[1], stat.st_size);
	time_patern(stat);
	ft_putchar(' ');
	if (device(stat.st_mode) == 'l')
	{
		ft_putstr(name);
		ft_putstr(" -> private");
	}
	ft_putendl(name);
}

void	ls_simple(t_env *e, char *way)
{
	int		i;
	t_lst	*lst;

	i = -1;
	lst = e->file_cntr->lst;
	if (e->recursive == 1)
		print_way(way, e->recursive);
	while (lst)
	{
		ft_putendl(lst->name);
		lst = lst->next;
	}
	if (e->pile_cntr->first != NULL)
		ft_putchar('\n');
}

void	ls_all(t_env *e, char *way)
{
	t_print_all	info;
	int			i;

	i = -1;
	info = init_info2print(e->file_cntr, way);
	if (e->recursive == 1)
		print_way(way, e->recursive);
	print_octet(info.stat, e->file_cntr->size);
	while (info.lst)
	{
		ft_putinfo(info.stat[++i], info.lst->name, info.nb_max, info.str_max);
		info.lst = info.lst->next;
	}
	if (e->pile_cntr->first != NULL)
		ft_putchar('\n');
	free(info.stat);
}
