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

t_lst		*new_elem(char *name, char *way)
{
	t_lst			*new;

	if (!(new = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	if (name != NULL)
		ft_strcpy(new->name, name);
	if (way != NULL)
		ft_strcpy(new->way, way);
	return (new);
}

int		push(t_pile_cntr *pile_cntr, char *name, char *way)
{
	t_lst	*new;

	//printf("PUSH\n");
	if ((new = new_elem(name, way)) == NULL)
		return (ERROR);
	if (pile_cntr->first == NULL)
		pile_cntr->first = new;
	else
	{
		new->next = pile_cntr->first;
		pile_cntr->first = new;
	}
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


int         add2fil(t_file_cntr *cntr, char *name, char *way)
{
      t_lst	*new;

	if ((new = new_elem(name, way)) == NULL)
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
	struct stat stt;
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
		stt = add_stat(lst);
		if (device(stt.st_mode) == 'd' || device(stt.st_mode) == 'l')
			push(e->pile_cntr, lst->name, lst->way);
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
