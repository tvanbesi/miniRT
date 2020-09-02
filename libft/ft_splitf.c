/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 15:46:18 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/09/02 21:42:59 by tvanbesi         ###   ########.fr       */
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
