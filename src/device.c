/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:09:15 by crenaudi          #+#    #+#             */
/*   Updated: 2020/01/28 18:41:41 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		device(mode_t st_mode)
{
	if ((st_mode & S_IFIFO) == S_IFIFO)
		return ('p');
	if ((st_mode & S_IFLNK) == S_IFLNK)
		return ('l');
	if ((st_mode & S_IFCHR) == S_IFCHR)
		return ('c');
	if ((st_mode & S_IFDIR) == S_IFDIR)
		return ('d');
	if ((st_mode & S_IFBLK) == S_IFBLK)
		return ('b');
	if ((st_mode & S_IFREG) == S_IFREG)
		return ('-');
	return ('f');
}

static char	user_x(mode_t st_mode)
{
	if ((S_IXUSR & st_mode) && (S_ISUID & st_mode))
		return ('s');
	else if (!(S_IXUSR & st_mode) && (S_ISUID & st_mode))
		return ('S');
	else if ((S_IXUSR & st_mode) && !(S_ISUID & st_mode))
		return ('x');
	else
		return ('-');
}

static char	grp_x(mode_t st_mode)
{
	if ((S_IXGRP & st_mode) && (S_ISGID & st_mode))
		return ('s');
	else if (!(S_IXGRP & st_mode) && (S_ISGID & st_mode))
		return ('S');
	else if ((S_IXGRP & st_mode) && !(S_ISGID & st_mode))
		return ('x');
	else
		return ('-');
}

static char	other_x(mode_t st_mode)
{
	if ((S_IXOTH & st_mode) && (S_ISVTX & st_mode))
		return ('t');
	else if (!(S_IXOTH & st_mode) && (S_ISVTX & st_mode))
		return ('T');
	else if ((S_IXOTH & st_mode) && !(S_ISVTX & st_mode))
		return ('x');
	else
		return ('-');
}

void		st_mode_type(mode_t st_mode)
{
	char	mod[12];

	mod[0] = (st_mode & S_IRUSR) ? 'r' : '-';
	mod[1] = (st_mode & S_IWUSR) ? 'w' : '-';
	mod[2] = user_x(st_mode);
	mod[3] = (st_mode & S_IRGRP) ? 'r' : '-';
	mod[4] = (st_mode & S_IWGRP) ? 'w' : '-';
	mod[5] = grp_x(st_mode);
	mod[6] = (st_mode & S_IROTH) ? 'r' : '-';
	mod[7] = (st_mode & S_IWOTH) ? 'w' : '-';
	mod[8] = other_x(st_mode);
	mod[9] = ' ';
	mod[10] = ' ';
	mod[11] = '\0';
	ft_putstr(mod);
}
