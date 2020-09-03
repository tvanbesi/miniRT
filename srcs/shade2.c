/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 22:47:31 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/03 16:43:15 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void
	ft_shade_color(t_surf_pt *p_hit, int surfcolor,
	t_light *light, double facing_ratio)
{
	t_color	rgbsurf;
	t_color	rgblight;
	t_color	tmp;

	rgbsurf = ft_getrgb(surfcolor);
	rgblight = ft_getrgb(light->color);
	tmp = ft_getrgb(p_hit->color);
	if (light->lum > 0.0)
	{
		tmp.r += (double)((double)rgblight.r / 255.0) * facing_ratio
		* rgbsurf.r * light->lum;
		tmp.g += (double)((double)rgblight.g / 255.0) * facing_ratio
		* rgbsurf.g * light->lum;
		tmp.b += (double)((double)rgblight.b / 255.0) * facing_ratio
		* rgbsurf.b * light->lum;
	}
	tmp.r = tmp.r > 255 ? 255 : tmp.r;
	tmp.g = tmp.g > 255 ? 255 : tmp.g;
	tmp.b = tmp.b > 255 ? 255 : tmp.b;
	p_hit->color = ft_getcolor(&tmp);
}
