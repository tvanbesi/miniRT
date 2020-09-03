/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 22:49:40 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/03 03:49:30 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void
	ft_swap_double(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int
	ft_getcolor(t_color *rgb)
{
	return (rgb->r * 65536 + rgb->g * 256 + rgb->b);
}

t_color
	ft_getrgb(int color)
{
	t_color	rgb;

	rgb.r = color / 65536;
	color -= rgb.r * 65536;
	rgb.g = color / 256;
	color -= rgb.g * 256;
	rgb.b = color;
	return (rgb);
}

t_camera
	ft_mkcamera(t_coords pos, t_coords ori)
{
	t_camera	r;

	r.pos = pos;
	r.ori = ori;
	return (r);
}

t_light
	ft_mklight(t_coords pos, int color, double lum)
{
	t_light r;

	r.pos = pos;
	r.color = color;
	r.lum = lum;
	return (r);
}
