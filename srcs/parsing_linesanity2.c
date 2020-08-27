/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_linesanity2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 11:26:43 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/08/23 11:55:47 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int
	ft_isvalid_plane(char **a)
{
	if (a[1] && a[2] && a[3] && !a[4])
		return (ft_isvalid_3db(a[1])
				&& ft_isvalid_3db(a[2])
				&& ft_isvalid_rgb(a[3]));
	return (0);
}

int
	ft_isvalid_square(char **a)
{
	if (a[1] && a[2] && a[3] && a[4] && !a[5])
		return (ft_isvalid_3db(a[1])
				&& ft_isvalid_3db(a[2])
				&& ft_isvalid_db(a[3])
				&& ft_isvalid_rgb(a[4]));
	return (0);
}

int
	ft_isvalid_cyl(char **a)
{
	if (a[1] && a[2] && a[3] && a[4] && a[5] && !a[6])
		return (ft_isvalid_3db(a[1])
				&& ft_isvalid_3db(a[2])
				&& ft_isvalid_db(a[3])
				&& ft_isvalid_db(a[4])
				&& ft_isvalid_rgb(a[5]));
	return (0);
}

int
	ft_isvalid_triangle(char **a)
{
	if (a[1] && a[2] && a[3] && a[4] && !a[5])
		return (ft_isvalid_3db(a[1])
				&& ft_isvalid_3db(a[2])
				&& ft_isvalid_3db(a[3])
				&& ft_isvalid_rgb(a[4]));
	return (0);
}
