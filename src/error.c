/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:09:07 by crenaudi          #+#    #+#             */
/*   Updated: 2019/11/28 18:37:21 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	error(char *av, int error, char *illegal)
{
	char *tmp;
	int			er[5];
	int			i;
	const char	*s[6] = {
		": No such file or directory", ": Premission denied",
		"illegal option -- ", ": error in flags", ": usage flags", "\0"
	};

	er[0] = -1;
	er[1] = -2;
	er[2] = -3;
	er[3] = 1;
	er[4] = '\0';
	ft_putstr("ls: ");
	if (error != -3)
		ft_putstr(av);
	i = -1;
	while (er[++i] != '\0')
		if (error == er[i])
		{
			tmp = ft_strjoin(s[i], illegal);
			(error == -3) ? ft_putendl(tmp) : ft_putendl(s[i]);
			free(tmp);
		}
	if (error == -3)
	{
		ft_putstr("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1]");
		ft_putendl(" [file ...]");
	}
}
