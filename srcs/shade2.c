/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 22:47:31 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/01 22:47:48 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void
	ft_shade_color(t_surf_pt *p_hit, int surfcolor,
	t_light *light, double ratio)
{
	t_color	rgbsurf;
	t_color	rgblight;
	t_color	tmp;

	rgbsurf = ft_getrgb(surfcolor);
	rgblight = ft_getrgb(light->color);
	tmp = ft_getrgb(p_hit->color);
	tmp.r += rgbsurf.r * ratio *
	(double)((double)rgblight.r / 255.0) * light->lum;
	tmp.g += rgbsurf.g * ratio *
	(double)((double)rgblight.g / 255.0) * light->lum;
	tmp.b += rgbsurf.b * ratio *
	(double)((double)rgblight.b / 255.0) * light->lum;
	if (tmp.r > 255)
		tmp.r = 255;
	if (tmp.g > 255)
		tmp.g = 255;
	if (tmp.b > 255)
		tmp.b = 255;
	p_hit->color = ft_getcolor(&tmp);
}
