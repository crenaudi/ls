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

void		error(char *av, int error, char c)
{
	ft_putstr(LS);
	if (error != -3)
		ft_putstr(av);
	if (error == -1)
		ft_putendl(ERROR_01);
	if (error == -2)
		ft_putendl(ERROR_02);
	if (error == -3)
	{
		ft_putstr(ERROR_03);
		ft_putchar(c);
		ft_putchar('\n');
		ft_putstr(USAGE);
		ft_putendl(ERROR_06);
	}
	if (error == 1)
		ft_putendl(ERROR_04);
}
