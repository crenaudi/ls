/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:10 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/25 20:51:04 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		print_octet(struct stat *stat, int ln)
{
	int		i;
	int		total;

	i = 0;
	total = 0;
	while (i < ln)
	{
		total += (stat[i].st_blocks);
		i++;
	}
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

void		max_st_nb(struct stat *stat, int ln, t_vec2 *nb_max)
{
	int		i;
	unsigned int	link_current;
	unsigned int	size_current;

	i = 0;
	nb_max->x = 0;
	nb_max->y = 0;
	while (i < ln)
	{
		link_current = ft_nblen(stat[i].st_nlink);
		if (nb_max->x < link_current)
			nb_max->x = link_current;
		size_current = ft_nblen(stat[i].st_size);
		if (nb_max->y < size_current)
			nb_max->y = size_current;
		i++;
	}
}

void		max_st_str(struct stat *stat, int ln, t_vec2 *str_max)
{
	int				i;
	struct passwd	*pwd;
	struct group	*grp;

	i = 0;
	str_max->x = 0;
	str_max->y = 0;
	while (i < ln)
	{
		if ((pwd = getpwuid(stat->st_uid)) == NULL)
			str_max->x = ((size_t)(str_max->x) < ft_nblen(stat->st_uid)) ?
				str_max->x : ft_nblen(stat->st_uid);
		else
			str_max->x = ((size_t)(str_max->x) < ft_strlen(pwd->pw_name)) ?
				str_max->x : ft_strlen(pwd->pw_name);
		if ((grp = getgrgid(stat->st_gid)) == NULL)
			str_max->y = ((size_t)(str_max->y) < ft_nblen(stat->st_uid)) ?
				str_max->y : ft_nblen(stat->st_uid);
		else
			str_max->y = ((size_t)(str_max->y) < ft_strlen(grp->gr_name)) ?
				str_max->y : ft_strlen(grp->gr_name);
		i++;
	}
}
