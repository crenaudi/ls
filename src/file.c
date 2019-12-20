/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:10 by crenaudi          #+#    #+#             */
/*   Updated: 2019/12/19 21:53:40 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		ln_files(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != '\0')
		i++;
	return (i);
}

void			all_file(struct stat *buf, char **file)
{
	int		i;
	int		ln;
	t_vec2	nb_max;
	t_vec2	str_max;

	i = -1;
	ln = ln_files(file);
	max_st_nb(buf, ln, &nb_max);
	max_st_str(buf, ln, &str_max);
	while (file[++i] != 0)
		ft_putinfo(buf[i], file[i], nb_max, str_max);
}

struct stat		*buf_tab2(char **tab, char *way)
{
	struct stat	*buf;
	char		*tmp;
	int			i;
	int			len;

	i = -1;
	buf = NULL;
	len = ln_files(tab);
	if (!(buf = (struct stat *)malloc(sizeof(struct stat) * (len))))
		return (NULL);
	while (++i < len)
	{
		tmp = ft_strjoin(way, tab[i]);
		lstat(tmp, &buf[i]);
		clean_ptr((void *)(&tmp));
	}
	return (buf);
}
