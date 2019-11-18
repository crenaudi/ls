/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:43 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/02 13:32:42 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	add_flags(char *flags, t_env *e)
{
	if (flags == NULL)
	{
		e->f_sort = &sort_base;
		e->f_print = &print_simple;
		return ;
	}
	e->a = (ft_strchr(flags, 'a') != NULL) ? 1 : 0;
	e->reccursive = (ft_strchr(flags, 'R') != NULL) ? 1 : 0;
	e->f_print = (ft_strchr(flags, 'l') != NULL) ? &print_all : &print_simple;
	if (ft_strchr(flags, 'r') != NULL && ft_strchr(flags, 't') != NULL)
		e->f_sort = &sort_rt;
	else if (ft_strchr(flags, 'r') != NULL)
		e->f_sort = &sort_r;
	else if (ft_strchr(flags, 't') != NULL)
		e->f_sort = &sort_t;
	else
		e->f_sort = &sort_base;
}

int        parse_flags(int ac, char **av, t_env *e)
{
	char	*flg;
	int	i;

	i = 1;
	flg = NULL;
	if (ac != 1 && av[i][0] == '-' && av[i][1] != '-')
	{
		while (av[i] != NULL && (av[i][0] == '-' && av[i][1] != '-'))
            {
			flg = (flg == NULL) ? ft_strdup(av[i]) : ft_strjoin(flg, av[i]);
                  i++;
            }
		add_flags(flg, e);
	}
	else
		add_flags(NULL, e);
	return (i);
}

int         ln_tab(char **tab)
{
      int i;

      i = 0;
      while (tab[i][0]!='\0')
            i++;
      return(i);
}

struct stat *add_buf2pile(t_env *e, char *way, int had_param)
{
	struct stat *buf;
	int   i;
	int   len;

	i = -1;
	len = ln_tab(e->curr);
	if (!(buf = (struct stat *)malloc(sizeof(struct stat) * (len))))
		return (NULL);
	while (++i < len)
	{
		if (lstat(ft_strjoin(way, e->curr[i]), &buf[i]) != 0)
			error(e->curr[i], 0);
	}

      if (e->reccursive == 1 ou had_param == 1)
	     tri_reccursif(e, way, buf, 0, len);

     	printf("Dans ma pile il y a %s\n", e->pile->first->name);
	return (buf);
}
