/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 20:19:18 by crenaudi          #+#    #+#             */
/*   Updated: 2019/12/17 23:02:21 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*copy;

	if (!s1)
		return ((s2 == NULL) ? NULL : ft_strdup(s2));
	if (!s2)
		return ((s1 == NULL) ? NULL : ft_strdup(s1));
	if (!(copy = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (0);
	ft_strcat(ft_strcpy(copy, s1), s2);
	return (copy);
}
