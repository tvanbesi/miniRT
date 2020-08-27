/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 15:46:18 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/08/25 14:49:22 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
    ft_splitf(char **a)
{
	char	**tmp;

	tmp = a;
	while (*a)
	{
		free(*a);
		a++;
	}
	free(tmp);
}