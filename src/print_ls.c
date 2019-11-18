/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:08:10 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/02 13:55:05 by crenaudi         ###   ########.fr       */
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
	if (ft_strcmp(way, "./"))
	{
		ft_putchar('\n');
		ft_putendl(ft_strjoin(way, " :\n"));
	}
}

static void		ft_putinfo(struct stat buf, char *name)
{
	struct passwd	*pwd;
	struct group	*grp;
	char			*tm;
	int				i;

	i = -1;
	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	ft_putchar(device_type(buf));
	mode_type(buf);
	ft_putnbr(buf.st_nlink);
	ft_putchar(' ');
	ft_putspace(pwd->pw_name);
	ft_putspace(grp->gr_name);
	ft_putnbr(buf.st_size);
	ft_putchar(' ');
	tm = ctime(&buf.st_ctime);
	while (tm[++i + 1] != '\0')
		ft_putchar(tm[i]);
	ft_putchar(' ');
	ft_putendl(name);
}

void			print_simple(struct stat *buf, char *way, t_env *e)
{
	int	i;

	(void)buf;
	print_way(way);
	i = -1;
	while (e->curr[++i][0] != 0)
		ft_putspace(e->curr[i]);
	ft_putchar('\n');
}

void			print_all(struct stat *buf, char *way, t_env *e)
{
	int		i;
	t_imp	*size;

	i = -1;
	size = init_size(e);
	print_way(way);
	while (e->curr[++i][0] != 0)
		ft_putinfo(buf[i], e->curr[i]);
	ft_putchar('\n');
	free(size);
}
