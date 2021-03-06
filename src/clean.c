/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:09:22 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/28 18:58:26 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	destroy_elem(t_lst *elem)
{
	ft_bzero(elem->name, sizeof(char) * NAME_MAX);
	ft_bzero(elem->way, sizeof(char) * PATH_MAX);
	ft_memdel((void **)(&elem->name));
	ft_memdel((void **)(&elem->way));
	elem->next = NULL;
	ft_memdel((void **)(&elem));
	elem = NULL;
}

void	destroy_lst(t_lst **lst)
{
	t_lst	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		destroy_elem(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	destroy_cntr_file(t_file_cntr *cntr)
{
	if (cntr->lst != NULL)
		destroy_lst(&cntr->lst);
	cntr->size = 0;
}

void	destroy_cntr_pile(t_pile_cntr *cntr)
{
	if (cntr->first != NULL)
		destroy_lst(&cntr->first);
}

void	clean_env(t_env *e)
{
	ft_memdel((void **)(&e->file_cntr));
	destroy_cntr_pile(e->pile_cntr);
	ft_memdel((void **)(&e->pile_cntr));
	ft_bzero(e, sizeof(t_env));
}
