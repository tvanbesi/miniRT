/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_linesanity2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 11:26:43 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/09/02 22:28:58 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int
	ft_isvalid_plane(char **a)
{
	if (a[1] && a[2] && a[3] && !a[4])
	{
		return (ft_isvalid_3db(a[1])
				&& ft_isvalid_3db(a[2])
				&& ft_isvalid_rgb(a[3]));
	}
	return (0);
}

int
	ft_isvalid_square(char **a)
{
	if (a[1] && a[2] && a[3] && a[4] && !a[5])
	{
		return (ft_isvalid_3db(a[1])
				&& ft_isvalid_3db(a[2])
				&& ft_isvalid_db(a[3])
				&& ft_isvalid_rgb(a[4]));
	}
	return (0);
}

int
	ft_isvalid_cyl(char **a)
{
	if (a[1] && a[2] && a[3] && a[4] && a[5] && !a[6])
	{
		return (ft_isvalid_3db(a[1])
				&& ft_isvalid_3db(a[2])
				&& ft_isvalid_db(a[3])
				&& ft_isvalid_db(a[4])
				&& ft_isvalid_rgb(a[5]));
	}
	return (0);
}

int
	ft_isvalid_triangle(char **a)
{
	if (a[1] && a[2] && a[3] && a[4] && !a[5])
	{
		return (ft_isvalid_3db(a[1])
				&& ft_isvalid_3db(a[2])
				&& ft_isvalid_3db(a[3])
				&& ft_isvalid_rgb(a[4]));
	}
	return (0);
}
