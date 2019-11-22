/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:10 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/22 20:53:49 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		nb_patern(int start, int nb)
{
	int		i;

	i = start - ft_nblen(nb);
	while (i-- > 0)
		ft_putchar(' ');
	ft_putnbr(nb);
	ft_putchar(' ');
}

void		str_patern(int start, char *str)
{
	int		i;

	i = start - ft_strlen(str);
	ft_putstr(str);
	while (i-- > 0)
		ft_putchar(' ');
	ft_putstr("  ");
}

int			max_st_nlink(struct stat *buf, int ln)
{
	int		i;
	int		max;
	int		current;

	i = 0;
	max = 0;
	while (i < ln)
	{
		current = ft_nblen(buf[i].st_nlink);
		if (max < current)
			max = current;
		i++;
	}
	return (max);
}

int			max_st_size(struct stat *buf, int ln)
{
	int		i;
	int		max;
	int		current;

	i = 0;
	max = 0;
	while (i < ln)
	{
		current = ft_nblen(buf[i].st_size);
		if (max < current)
			max = current;
		i++;
	}
	return (max);
}

int			max_user(struct stat *buf, int ln)
{
	int				i;
	int				max;
	int				current;
	struct passwd	*pwd;

	i = 0;
	max = 0;
	while (i < ln)
	{
		pwd = getpwuid(buf->st_uid);
		current = ft_strlen(pwd->pw_name);
		if (max < current)
			max = current;
		i++;
	}
	return (max);
}

int			max_grp(struct stat *buf, int ln)
{
	int				i;
	int				max;
	int				current;
	struct group	*grp;

	i = 0;
	max = 0;
	while (i < ln)
	{
		grp = getgrgid(buf->st_gid);
		current = ft_strlen(grp->gr_name);
		if (max < current)
			max = current;
		i++;
	}
	return (max);
}
