/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 22:47:31 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/03 16:48:04 by tvanbesi         ###   ########.fr       */
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

void
	ft_shade(t_surf_pt *p_hit, t_object *obj, t_light *light)
{
	if (obj->sphere.type == SPHERE)
		ft_shade_sphere(p_hit, obj, light);
	else if (obj->plane.type == PLANE)
		ft_shade_flatsurf(p_hit, obj, light);
	else if (obj->sphere.type == SQUARE)
		ft_shade_flatsurf(p_hit, obj, light);
	else if (obj->cylinder.type == CYLINDER)
		ft_shade_cylinder(p_hit, obj, light);
	else if (obj->triangle.type == TRIANGLE)
		ft_shade_flatsurf(p_hit, obj, light);
}

void
	ft_shade_amblight(t_surf_pt *p_hit, t_object *obj, t_light *amblight)
{
	if (obj->plane.type == PLANE)
		ft_shade_color(p_hit, obj->plane.color, amblight, 1.0);
	else if (obj->plane.type == CYLINDER)
		ft_shade_color(p_hit, obj->cylinder.color, amblight, 1.0);
	else if (obj->plane.type == TRIANGLE)
		ft_shade_color(p_hit, obj->triangle.color, amblight, 1.0);
	else if (obj->plane.type == SPHERE)
		ft_shade_color(p_hit, obj->sphere.color, amblight, 1.0);
	else if (obj->plane.type == SQUARE)
		ft_shade_color(p_hit, obj->square.color, amblight, 1.0);
}
