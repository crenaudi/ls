/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:10 by crenaudi          #+#    #+#             */
/*   Updated: 2019/12/19 21:52:43 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_way(char *way, int rec)
{
	int	i;
	int tmp;
	int	idx;

	idx = (rec == 1 || way[0] == '/') ? 0 : 2;
	tmp = ft_strlen(way) - 1;
	i = (way[tmp] == '/') ? tmp : tmp + 1;
	if (ft_strcmp(way, "./") != 0)
	{
		while (idx < i)
			ft_putchar(way[idx++]);
		ft_putendl(":");
	}
}

void	ft_putinfo(struct stat buf, char *name, t_vec2 nb_max, t_vec2 str_max)
{
	struct passwd	*pwd;
	struct group	*grp;

	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	ft_putchar(device(buf));
	mode_type(buf);
	(device(buf) == 'c') ? nb_patern(nb_max.x, buf.st_blksize) : nb_patern(nb_max.x, buf.st_nlink);
	(pwd == NULL) ? id_patern(str_max.x, buf.st_uid) :
		str_patern(str_max.x, pwd->pw_name);
	(grp == NULL) ? id_patern(str_max.x, buf.st_gid) :
		str_patern(str_max.y, grp->gr_name);
	nb_patern(nb_max.y, buf.st_size);
	time_patern(buf);
	ft_putchar(' ');
	if (device(buf) == 'l')
	{
		ft_putstr(name);
		ft_putstr(" private -> ");
	}
	ft_putendl(name);
}

void	ls_simple(char *way, t_env *e)
{
	int	i;

	i = -1;
	print_way(way, e->recursive);
	while (e->current[++i][0] != 0)
		ft_putendl(e->current[i]);
	if (e->pile != NULL && e->pile->first != NULL)
		ft_putchar('\n');
}

void	ls_all(char *way, t_env *e)
{
	int		i;
	int		ln;
	t_vec2	nb_max;
	t_vec2	str_max;

	i = -1;
	ln = ln_tab(e->current);
	max_st_nb(e->buf, ln, &nb_max);
	max_st_str(e->buf, ln, &str_max);
	print_way(way, e->recursive);
	print_octet(e->buf, ln);
	while (e->current[++i][0] != 0)
		ft_putinfo(e->buf[i], e->current[i], nb_max, str_max);
	if (e->pile != NULL && e->pile->first != NULL)
		ft_putchar('\n');
}

void	print_lnk(struct stat buf, char *lnk, t_pile *pile)
{
	int		i;
	char 	*tmp;
	t_vec2	nb_max;
	t_vec2	str_max;

	i = -1;
	max_st_nb(&buf, 1, &nb_max);
	max_st_str(&buf, 1, &str_max);
	tmp = (lnk[0] != '/') ? ft_strdup(lnk) : ft_strsub(lnk, 1, ft_strlen(lnk));
	ft_putinfo(buf, tmp, nb_max, str_max);
	clean_ptr((void *)(&tmp));
	if (pile != NULL && pile->first != NULL)
		ft_putchar('\n');
}
