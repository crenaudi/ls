/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:07:46 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/25 18:40:27 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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

void		mode_type(struct stat buf)
{
	char	mode[12];

	mode[0] = (buf.st_mode & S_IRUSR) ? 'r' : '-';
	mode[1] = (buf.st_mode & S_IWUSR) ? 'w' : '-';
	mode[2] = user_x(buf.st_mode);
	mode[3] = (buf.st_mode & S_IRGRP) ? 'r' : '-';
	mode[4] = (buf.st_mode & S_IWGRP) ? 'w' : '-';
	mode[5] = grp_x(buf.st_mode);
	mode[6] = (buf.st_mode & S_IROTH) ? 'r' : '-';
	mode[7] = (buf.st_mode & S_IWOTH) ? 'w' : '-';
	mode[8] = other_x(buf.st_mode);
	mode[9] = ' ';
	mode[10] = ' ';
	mode[11] = '\0';
	ft_putstr(mode);
}
