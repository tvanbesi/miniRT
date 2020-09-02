/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_linesanity1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 11:25:02 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/09/02 22:28:51 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int
	ft_isvalid_res(char **a)
{
	if (a[1] && a[2] && !a[3])
		return (ft_isvalid_int(a[1]) && ft_isvalid_int(a[2]));
	return (0);
}

int
	ft_isvalid_alight(char **a)
{
	if (a[1] && a[2] && !a[3])
		return (ft_isvalid_db(a[1]) && ft_isvalid_rgb(a[2]));
	return (0);
}

int
	ft_isvalid_cam(char **a)
{
	if (a[1] && a[2] && a[3] && !a[4])
	{
		return (ft_isvalid_3db(a[1])
			&& ft_isvalid_3db(a[2])
			&& ft_isvalid_int(a[3]));
	}
	return (0);
}

int
	ft_isvalid_light(char **a)
{
	if (a[1] && a[2] && a[3] && !a[4])
	{
		return (ft_isvalid_3db(a[1])
				&& ft_isvalid_db(a[2])
				&& ft_isvalid_rgb(a[3]));
	}
	return (0);
}

int
	ft_isvalid_sphere(char **a)
{
	if (a[1] && a[2] && a[3] && !a[4])
	{
		return (ft_isvalid_3db(a[1])
				&& ft_isvalid_db(a[2])
				&& ft_isvalid_rgb(a[3]));
	}
	return (0);
}
