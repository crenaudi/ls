/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:29:52 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/31 16:55:43 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_lst			*mergelists(t_lst *first, t_lst *second, t_lst *head, t_env *e)
{
	t_lst	**tailp;

	tailp = &head;
	while (first != NULL && second != NULL)
	{
		if (e->f_sort(first, second) == 1)
		{
			*tailp = first;
			tailp = &first->next;
			first = first->next;
			if (first == NULL)
				*tailp = second;
		}
		else
		{
			*tailp = second;
			tailp = &second->next;
			second = second->next;
			if (second == NULL)
				*tailp = first;
		}
		if (first == NULL || second == NULL)
			return (head);
	}
	return (NULL);
}

t_lst			*topdownmergesort2(t_lst **headp, size_t n, t_env *e)
{
	t_lst	*first;
	t_lst	*second;

	first = *headp;
	if (n < 1 || first == NULL)
	{
		ft_putstr("pb n et:ou first = NULL\n");
		return (NULL);
	}
	if (n == 1)
	{
		*headp = first->next;
		first->next = NULL;
		return (first);
	}
	first = topdownmergesort2(headp, (n + 1) / 2, e);
	second = topdownmergesort2(headp, n / 2, e);
	return (mergelists(first, second, NULL, e));
}

t_lst			*topdownmergesort(t_env *e, t_lst *head, size_t n)
{
	t_lst *sorted;

	if (n == 0)
		sorted = head;
	else
		sorted = topdownmergesort2(&head, n, e);
	return (sorted);
}

struct stat		add_stat(t_lst *lst)
{
	struct stat	stt;
	char		*tmp;

	tmp = (lst->name[0] == '/') ?
		ft_strdup(lst->name) : ft_strjoin(lst->way, lst->name);
	lstat(tmp, &stt);
	ft_strdel(&tmp);
	return (stt);
}
