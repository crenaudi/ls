/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:20 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/18 18:24:08 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sort_base(struct stat *buf, t_env *e, int size)
{
	t_vec3 index;
	char		*abys;
	struct stat	tmp;

	index.z = size;
	size--;
	while (index.z--)
	{
		index.x = -1;
		while (++index.x < size)
		{
			index.y = 0;
			while (e->curr[index.x][index.y] == e->curr[index.x + 1][index.y])
				index.y++;
			if (e->curr[index.x][index.y] > e->curr[index.x + 1][index.y])
			{
				abys = e->curr[index.x];
				e->curr[index.x] = e->curr[index.x + 1];
				e->curr[index.x + 1] = abys;
				tmp = buf[index.x];
				buf[index.x] = buf[index.x + 1];
				buf[index.x + 1] = tmp;
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
