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

char	device_type(struct stat buf)
{
	if ((buf.st_mode & S_IFIFO) == S_IFIFO)
		return ('p');
	if ((buf.st_mode & S_IFLNK) == S_IFLNK)
		return ('l');
	if ((buf.st_mode & S_IFCHR) == S_IFCHR)
		return ('c');
	if ((buf.st_mode & S_IFDIR) == S_IFDIR)
		return ('d');
	if ((buf.st_mode & S_IFBLK) == S_IFBLK)
		return ('b');
	if ((buf.st_mode & S_IFREG) == S_IFREG)
		return ('-');
	return ('f');
}
