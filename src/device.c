/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:09:15 by crenaudi          #+#    #+#             */
/*   Updated: 2019/12/20 19:40:15 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	device(mode_t mode)
{
	if ((mode & S_IFIFO) == S_IFIFO)
		return ('p');
	if ((mode & S_IFLNK) == S_IFLNK)
		return ('l');
	if ((mode & S_IFCHR) == S_IFCHR)
		return ('c');
	if ((mode & S_IFDIR) == S_IFDIR)
		return ('d');
	if ((mode & S_IFBLK) == S_IFBLK)
		return ('b');
	if ((mode & S_IFREG) == S_IFREG)
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

void		mode_type(mode_t st_mode)
{
	char	mode[12];

	mode[0] = (st_mode & S_IRUSR) ? 'r' : '-';
	mode[1] = (st_mode & S_IWUSR) ? 'w' : '-';
	mode[2] = user_x(st_mode);
	mode[3] = (st_mode & S_IRGRP) ? 'r' : '-';
	mode[4] = (st_mode & S_IWGRP) ? 'w' : '-';
	mode[5] = grp_x(st_mode);
	mode[6] = (st_mode & S_IROTH) ? 'r' : '-';
	mode[7] = (st_mode & S_IWOTH) ? 'w' : '-';
	mode[8] = other_x(st_mode);
	mode[9] = ' ';
	mode[10] = ' ';
	mode[11] = '\0';
	ft_putstr(mode);
}
