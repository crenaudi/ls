/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:09:07 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/02 13:37:11 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	error(char *av, int error)
{
	int er[5] = {-1, -2, -3, 1, '\0'};
	int i;
	const char *s[6] = {
		": No such file or directory",
		": Premission denied",
		"illegal option -- -",
		": error in flags",
		": usage flags",
		"\0"
	};

	ft_putstr("ls: ");
	if (error != -3)
		ft_putstr(av);
		i = -1;
	while (er[++i] != '\0')
		if (error == er[i])
			ft_putendl(s[i]);
	if (error == -3)
		ft_putendl("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]");
}
