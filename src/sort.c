/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:20 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/28 18:36:12 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			sort_base(t_lst *first, t_lst *second)
{
	int i;

	i = 0;
	while (first->name[i] == second->name[i]
		&& first->name[i] != '\0' && second->name[i] != '\0')
		i++;
	if (first->name[i] <= second->name[i]
		&& first->name[i] != '\0' && second->name[i] != '\0')
		return (1);
	return (0);
}

int			sort_r(t_lst *first, t_lst *second)
{
	int		i;

	i = 0;
	while (first->name[i] == second->name[i]
		&& first->name[i] != '\0' && second->name[i] != '\0')
		i++;
	if (first->name[i] >= second->name[i]
		&& first->name[i] != '\0' && second->name[i] != '\0')
		return (1);
	return (0);
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

int			sort_t(t_lst *first, t_lst *second)
{
	if (cmpt(add_stat(first), add_stat(second), first->name,
		second->name) == 0)
		return (0);
	return (1);
}

int			sort_rt(t_lst *first, t_lst *second)
{
	if (cmpt(add_stat(first), add_stat(second), first->name,
			second->name) == 0)
		return (1);
	return (0);
}
