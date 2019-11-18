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
	ft_putstr("ls: ");
	ft_putstr(av);
	if (error == -1)
		ft_putendl(": No such file or directory");
	else if (error == -2)
		ft_putendl(": Premission denied");
	else if (error == -3)
		ft_putendl("error in flags");
	else
		ft_putendl(": usage");
}
