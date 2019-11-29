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

void		print_octet(struct stat *buf, int ln)
{
	int		i;
	int		total;

	i = 0;
	total = 0;
	while (i < ln)
	{
		total += (buf[i].st_blocks);
		i++;
	}
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

void		max_st_nb(struct stat *buf, int ln, t_vec2 *nb_max)
{
	int		i;
	int		link_current;
	int		size_current;

	i = 0;
	nb_max->x = 0;
	nb_max->y = 0;
	while (i < ln)
	{
		link_current = ft_nblen(buf[i].st_nlink);
		if (nb_max->x < link_current)
			nb_max->x = link_current;
		size_current = ft_nblen(buf[i].st_size);
		if (nb_max->y < size_current)
			nb_max->y = size_current;
		i++;
	}
}

void		max_st_str(struct stat *buf, int ln, t_vec2 *str_max)
{
	int				i;
	int				pwd_current;
	int				grp_current;
	struct passwd	*pwd;
	struct group	*grp;

	i = 0;
	str_max->x = 0;
	str_max->y = 0;
	while (i < ln)
	{
		pwd = getpwuid(buf->st_uid);
		pwd_current = ft_strlen(pwd->pw_name);
		if (str_max->x < pwd_current)
			str_max->x = pwd_current;
		grp = getgrgid(buf->st_gid);
		grp_current = ft_strlen(grp->gr_name);
		if (str_max->y < grp_current)
			str_max->y = grp_current;
		i++;
	}
}
