/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile_cntr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:15:37 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/28 18:45:37 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_lst		*new_elem(char *name, char *way, mode_t *st_mode)
{
	t_lst			*new;
	//mode_t		mod;

	if (!(new = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	if (name != NULL)
		ft_strcpy(new->name, name);
	if (way != NULL)
		ft_strcpy(new->way, way);/*
	if (!(mod = (mode_t)malloc(sizeof(mode_t))))
		return (NULL);*/
	//mod = *st_mode;
	new->st_mode = st_mode;
	return (new);
}

int		push(t_pile_cntr *pile_cntr, char *name, char *way, mode_t *st_mode)
{
	t_lst	*new;

	//printf("PUSH\n");
	if ((new = new_elem(name, way, st_mode)) == NULL)
		return (ERROR);
	if (pile_cntr->first == NULL)
		pile_cntr->first = new;
	else
	{
		new->next = pile_cntr->first;
		pile_cntr->first = new;
	}
	if (st_mode != NULL)
		pile_cntr->st_mode = st_mode;
	return (SUCCESS);
}

t_lst		*pop(t_pile_cntr *pile_cntr)
{
	t_lst	*tmp;

	//printf("POP\n");
	tmp = NULL;
	tmp = pile_cntr->first;
	if (pile_cntr == NULL)
		return (NULL);
	if (pile_cntr != NULL && pile_cntr->first != NULL)
		pile_cntr->first = tmp->next;
	return (tmp);
}


int         add2file(t_file_cntr *cntr, char *name, char *way, mode_t *st_mode)
{
      t_lst	*new;

	printf("add2file ----- >> %s, %zu\n", name, cntr->size);
	if ((new = new_elem(name, way, st_mode)) == NULL)
		return (ERROR);
	if (cntr->lst == NULL)
		cntr->lst = new;
	else
	{
		new->next = cntr->lst;
		cntr->lst = new;
	}
	//print_file(cntr);
	cntr->size += 1;
	return (SUCCESS);
}

void 	push2stack(t_env *e)
{
	t_lst 	*lst;
	char 		*tmp;
	size_t 	i;

	//printf("push2stack\n");
	tmp = NULL;
	lst = e->file_cntr->lst;
	if (e->pile_cntr->first == NULL)
		tmp = "./";
	else
		tmp = e->pile_cntr->first->way;
	i = 0;
	while (i < e->file_cntr->size)
	{
		if (device(*lst->st_mode) == 'd' || device(*lst->st_mode) == 'l')
			push(e->pile_cntr, lst->name, lst->way, lst->st_mode);
		else
			ft_putendl(lst->name); //a prevoir si flag l
		i++;
	}
}

void		print_pile_cntr(t_pile_cntr *pile_cntr)
{
	t_lst		*tmp;

	tmp = NULL;
	tmp = pile_cntr->first;
	while (tmp != NULL)
	{
		printf("dans ma pile_cntr il y a %s\n", tmp->name);
		tmp = tmp->next;
	}
}
