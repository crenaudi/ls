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

int		sort_base(t_lst *first, t_lst *second)
{
      int i;

      i = 0;
	while (first->name[i] == second->name[i])
		i++;
	if (first->name[i] <= second->name[i])
		return (1);
	return (0);
}

int		sort_r(t_lst *first, t_lst *second)
{
      int i;

      i = 0;
	while (first->name[i] == second->name[i])
		i++;
	if (first->name[i] >= second->name[i])
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

int		sort_t(t_lst *first, t_lst *second)
{
	if (cmpt(add_stat(first), add_stat(second), first->name,
		second->name) == 0)
		return (1);
	return (0);
}

int		sort_rt(t_lst *first, t_lst *second)
{
	if (cmpt(add_stat(first), add_stat(second), first->name,
            second->name) == 1)
            return (1);
	return (0);
}
/*
void		sort_base(t_file_cntr *files)
{
	size_t 	size;
	t_lst		*lst;
	int 		i;

	size = files->size;
	lst = files->lst;
	while (size--)
	{
		lst = files->lst;
		while (lst && lst->next != NULL)
		{
			i = 0;
			while (lst->next != NULL && lst->name[i] == lst->next->name[i])
				i++;
			if (lst->next != NULL && lst->name[i] > lst->next->name[i])
				ft_swap_elem(lst, lst->next);
			lst = lst->next;
		}
		print_file(files);
	}
	//printf("FINI\n");
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
*/
