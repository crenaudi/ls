/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:10 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/19 15:52:46 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		ft_putspace(char const *s)
{
	if (!s)
		return ;
	ft_putstr(s);
	ft_putchar(' ');
}

void			print_way(char *way)
{
	if (ft_strcmp(way, "./") != 0)
	{
		ft_putendl(ft_strjoin(ft_strsub(way, 0, ft_strlen(way) - 1), " :"));
	}
}

static void		ft_putinfo(struct stat buf, char *name, t_vec2 nb_max, t_vec2 str_max)
{
	struct passwd	*pwd;
	struct group	*grp;
	char			*tm;
	int				i;

	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	ft_putchar(device_type(buf));
	mode_type(buf);
	nb_patern(nb_max.x, buf.st_nlink);
	str_patern(str_max.x, pwd->pw_name);
	str_patern(str_max.y, grp->gr_name);
	nb_patern(nb_max.y, buf.st_size);
	tm = ctime(&buf.st_ctime);
	i = 3;
	while (++i < 11)
		ft_putchar(tm[i]);
	i += 8;
	while (tm[++i + 1] != '\0')
		ft_putchar(tm[i]);
	ft_putchar(' ');
	ft_putendl(name);
}

void			ls_simple(struct stat *buf, char *way, t_env *e)
{
	int	i;

	(void)buf;
	i = -1;
	print_way(way);
	while (e->curr[++i][0] != 0)
		ft_putspace(e->curr[i]);
	//Ne pas oublier de changer en ft_putendl
	ft_putchar('\n');
	if (e->pile != NULL && e->pile->first != NULL)
		ft_putchar('\n');
}

void			ls_all(struct stat *buf, char *way, t_env *e)
{
	int		i;
	int ln;
	t_vec2	nb_max;
	t_vec2	str_max;

	i = -1;
	ln = ln_tab(e->curr);
	nb_max.x = max_st_nlink(buf, ln);
	nb_max.y = max_st_size(buf, ln);
	str_max.x = max_st_nlink(buf, ln);
	str_max.y = max_st_size(buf, ln);
	print_way(way);
	while (e->curr[++i][0] != 0)
			ft_putinfo(buf[i], e->curr[i], nb_max, str_max);
	ft_putchar('\n');
	if (e->pile != NULL && e->pile->first != NULL)
		ft_putchar('\n');
}
