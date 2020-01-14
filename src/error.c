/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:09:07 by crenaudi          #+#    #+#             */
/*   Updated: 2019/12/17 23:19:21 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	init(int *er)
{
	er[0] = -1;
	er[1] = -2;
	er[2] = -3;
	er[3] = 1;
	er[4] = '\0';
}

void		error(char *av, int error, char c)
{
	int			er[5];
	int			i;
	const char	*s[6] = {
		": No such file or directory", ": Permission denied",
		"illegal option -- ", ": error in flags", ": usage flags", "\0"
	};

	init(er);
	ft_putstr("ls: ");
	if (error != -3)
		ft_putstr(av);
	i = -1;
	while (er[++i] != '\0')
		if (error == er[i])
		{
			ft_putstr(s[i]);
			if (error == -3)
				ft_putchar(c);
			ft_putchar('\n');
		}
	if (error == -3)
	{
		ft_putstr("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1]");
		ft_putendl(" [file ...]");
	}
}
