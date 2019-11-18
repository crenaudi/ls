/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:20 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/02 13:56:09 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sort_base(struct stat *buf, t_env *e, int size)
{
	int			i;
	int			ln;
	char		*abys;
	struct stat	tmp;

	ln = size;
	size--;
	while (ln--)
	{
		i = -1;
		while (++i < size)
		{
			if (e->curr[i][0] > e->curr[i + 1][0])
			{
				abys = e->curr[i];
				e->curr[i] = e->curr[i + 1];
				e->curr[i + 1] = abys;
				tmp = buf[i];
				buf[i] = buf[i + 1];
				buf[i + 1] = tmp;
			}
		}
	}
}

void	sort_r(struct stat *buf, t_env *e, int size)
{
	int			i;
	char		*abys;
	struct stat	tmp;

	i = -1;
	sort_base(buf, e, size);
	while (++i < --size)
	{
		abys = e->curr[i];
		e->curr[i] = e->curr[size];
		e->curr[size] = abys;
		tmp = buf[i];
		buf[i] = buf[size];
		buf[size] = tmp;
	}
}

static int	cmpt(struct stat b1, struct stat b2, char *s1, char *s2)
{
	if (b1.st_mtimespec.tv_sec > b2.st_mtimespec.tv_sec
	|| (b1.st_mtimespec.tv_sec == b2.st_mtimespec.tv_sec
	&& b1.st_mtimespec.tv_nsec > b2.st_mtimespec.tv_nsec)
	|| (b1.st_mtimespec.tv_sec == b2.st_mtimespec.tv_sec
	&& b1.st_mtimespec.tv_nsec == b2.st_mtimespec.tv_nsec
	&& ft_strcmp(s1, s2) < 0))
		return (1);
	return (0);
}

void	sort_t(struct stat *buf, t_env *e, int size)
{
	int			i;
	int			ln;
	char		*abys;
	struct stat	tmp;

	ln = size;
	size--;
	while (ln--)
	{
		i = -1;
		while (++i < size)
		{
			if (cmpt(buf[i], buf[i + 1], e->curr[i], e->curr[i + 1]) == 0)
			{
				abys = e->curr[i];
				e->curr[i] = e->curr[i + 1];
				e->curr[i + 1] = abys;
				tmp = buf[i];
				buf[i] = buf[i + 1];
				buf[i + 1] = tmp;
			}
		}
	}
}

void	sort_rt(struct stat *buf, t_env *e, int size)
{
	int			i;
	char		*abys;
	struct stat	tmp;

	i = -1;
	sort_t(buf, e, size);
	while (++i < --size)
	{
		abys = e->curr[i];
		e->curr[i] = e->curr[size];
		e->curr[size] = abys;
		tmp = buf[i];
		buf[i] = buf[size];
		buf[size] = tmp;
	}
}
