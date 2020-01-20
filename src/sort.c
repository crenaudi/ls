/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:20 by crenaudi          #+#    #+#             */
/*   Updated: 2019/12/10 14:34:42 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		sort_base(t_file_cntr *files)
{
	size_t 	size;
	t_lst		*lst;
	int 		i;

	printf("sort_base\n");
	size = files->size;
	lst = files->lst;
	while (size--)
	{
		printf("size = %zu\n", size);
		lst = files->lst;
		while (lst)
		{
			i = 0;
			while (lst->name[i] == lst->next->name[i])
				i++;
			if (lst->name[i] > lst->next->name[i])
				ft_swap_elem(lst, lst->next);
			lst = lst->next;
		}
	}
	printf("FINI\n");
}

void		sort_r(t_file_cntr *files)
{
	size_t 	size;
	t_lst		*start;
	t_lst 	*end;
	size_t	i;

	i = -1;
	printf("sort_r\n");
	sort_base(files);
	start = files->lst;
	size = files->size;
	while (++i < --size)
	{
		end = files->lst;
		while (end->next != NULL)
			end = end->next;
		ft_swap_elem(start, end);
		start = start->next;
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

void		sort_t(t_file_cntr *files)
{
	size_t 	size;
	t_lst		*lst;

	printf("sort_t\n");
	size = files->size;
	while (size--)
	{
		lst = files->lst;
		while (lst)
		{
			if (cmpt(add_stat(lst), add_stat(lst->next), lst->name,
				lst->next->name) == 0)
				ft_swap_elem(lst, lst->next);
			lst = lst->next;
		}
	}
}

void		sort_rt(t_file_cntr *files)
{
	printf("sort_rt\n");
	sort_t(files);
	sort_r(files);
}
/*

void		sort_base(struct stat *stat, char **s, int size)
{
	t_vec3		index;
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
			while (s[index.x][index.y] == s[index.x + 1][index.y])
				index.y++;
			if (s[index.x][index.y] > s[index.x + 1][index.y])
			{
				abys = s[index.x];
				s[index.x] = s[index.x + 1];
				s[index.x + 1] = abys;
				if (stat != NULL)
				{
					tmp = stat[index.x];
					stat[index.x] = stat[index.x + 1];
					stat[index.x + 1] = tmp;
				}
			}
		}
	}
}

void		sort_r(struct stat *stat, char **s, int size)
{
	int			i;
	char		*abys;
	struct stat	tmp;

	i = -1;
	abys = NULL;
	sort_base(stat, s, size);
	while (++i < --size)
	{
		abys = s[i];
		s[i] = s[size];
		s[size] = abys;
		if (stat != NULL)
		{
			tmp = stat[i];
			stat[i] = stat[size];
			stat[size] = tmp;
		}
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

void		sort_t(struct stat *stat, char **s, int size)
{
	int			i;
	int			ln;
	char		*abys;
	struct stat	tmp;

	abys = NULL;
	ln = size;
	size--;
	while (ln-- && stat != NULL)
	{
		i = -1;
		while (++i < size)
		{
			if (cmpt(stat[i], stat[i + 1], s[i], s[i + 1]) == 0)
			{
				abys = s[i];
				s[i] = s[i + 1];
				s[i + 1] = abys;
				tmp = stat[i];
				stat[i] = stat[i + 1];
				stat[i + 1] = tmp;
			}
		}
	}
}

void		sort_rt(struct stat *stat, char **s, int size)
{
	int			i;
	char		*abys;
	struct stat	tmp;

	i = -1;
	abys = NULL;
	sort_t(stat, s, size);
	while (++i < --size)
	{
		abys = s[i];
		s[i] = s[size];
		s[size] = abys;
		if (stat != NULL)
		{
			tmp = stat[i];
			stat[i] = stat[size];
			stat[size] = tmp;
		}
	}
}
*/
