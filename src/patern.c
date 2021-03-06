/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:28:29 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/28 18:53:56 by crenaudi         ###   ########.fr       */
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

void		id_patern(int start, int id)
{
	int		i;

	i = start - ft_nblen(id);
	ft_putnbr(id);
	while (i-- > 0)
		ft_putchar(' ');
	ft_putstr("  ");
}

void		str_patern(int start, char *name)
{
	int		i;

	i = start - ft_strlen(name);
	ft_putstr(name);
	while (i-- > 0)
		ft_putchar(' ');
	ft_putstr("  ");
}

void		time_patern(struct stat stat)
{
	char	*tm;
	time_t	today;
	int		ret;
	int		i;

	tm = NULL;
	tm = ctime(&stat.st_mtime);
	time(&today);
	if (today < stat.st_mtimespec.tv_sec)
		ret = 1;
	else
		ret = ((today - stat.st_mtimespec.tv_sec) < 15778458) ? 1 : 0;
	i = 3;
	while (++i < 11)
		ft_putchar(tm[i]);
	if (ret == 0)
	{
		i += 8;
		ft_putchar(' ');
		while (tm[++i + 1] != '\0')
			ft_putchar(tm[i]);
	}
	else
		while (i < 16)
			ft_putchar(tm[i++]);
}
