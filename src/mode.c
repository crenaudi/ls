/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:07:46 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/02 13:53:18 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	mode_type(struct stat buf)
{
	char	mode[12] = {
		'-', '-', '-', '-', '-', '-',
		'-', '-', '-', ' ', ' ', '\0'
	};

	if ((buf.st_mode & S_IRUSR) == S_IRUSR)
		mode[0] = 'r';
	if ((buf.st_mode & S_IWUSR) == S_IWUSR)
		mode[1] = 'w';
	if ((buf.st_mode & S_IXUSR) == S_IXUSR)
		mode[2] = 'x';
	if ((buf.st_mode & S_IRGRP) == S_IRGRP)
		mode[3] = 'r';
	if ((buf.st_mode & S_IWGRP) == S_IWGRP)
		mode[4] = 'w';
	if ((buf.st_mode & S_IXGRP) == S_IXGRP)
		mode[5] = 'x';
	if ((buf.st_mode & S_IROTH) == S_IROTH)
		mode[6] = 'r';
	if ((buf.st_mode & S_IWOTH) == S_IWOTH)
		mode[7] = 'w';
	if ((buf.st_mode & S_IXOTH) == S_IXOTH)
		mode[8] = 'x';
	ft_putstr(mode);
}
