/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:00:17 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/01 23:19:48 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int
	ft_parse_plane(char **a, t_scene *scene)
{
	t_object	*obj;

	obj = &scene->objects[scene->obj_count];
	if (!ft_parse_coords(&obj->plane.pos, a[1], POS))
		return (0);
	if (!ft_parse_coords(&obj->plane.ori, a[2], ORI))
		return (0);
	if (!ft_parse_color(&obj->plane.rgb, a[3]))
		return (0);
	obj->plane.color = ft_getcolor(&obj->plane.rgb);
	*obj = ft_mkplane(obj->plane.pos, obj->plane.ori, obj->plane.color);
	scene->obj_count++;
	return (1);
}

int
	ft_parse_square(char **a, t_scene *scene)
{
	t_object	*obj;

	obj = &scene->objects[scene->obj_count];
	if (!ft_parse_coords(&obj->square.pos, a[1], POS))
		return (0);
	if (!ft_parse_coords(&obj->square.ori, a[2], ORI))
		return (0);
	obj->square.height = ft_atof(a[3]);
	if (obj->square.height <= 0.0)
		return (0);
	if (!ft_parse_color(&obj->square.rgb, a[4]))
		return (0);
	obj->square.color = ft_getcolor(&obj->square.rgb);
	*obj = ft_mksquare(obj->square.pos, obj->square.ori,
	obj->square.height, obj->square.color);
	scene->obj_count++;
	return (1);
}

int
	ft_parse_cylinder(char **a, t_scene *scene)
{
	t_object	*obj;
	double		hr[2];

	obj = &scene->objects[scene->obj_count];
	if (!ft_parse_coords(&obj->cylinder.pos, a[1], POS))
		return (0);
	if (!ft_parse_coords(&obj->cylinder.ori, a[2], ORI))
		return (0);
	hr[1] = ft_atof(a[3]) / 2.0;
	hr[0] = ft_atof(a[4]);
	if (hr[1] <= 0.0 || hr[0] <= 0.0)
		return (0);
	if (!ft_parse_color(&obj->cylinder.rgb, a[5]))
		return (0);
	obj->cylinder.color = ft_getcolor(&obj->cylinder.rgb);
	*obj = ft_mkcylinder(obj->cylinder.pos, obj->cylinder.ori,
	hr, obj->cylinder.color);
	scene->obj_count++;
	return (1);
}

int
	ft_parse_triangle(char **a, t_scene *scene)
{
	t_object	*obj;
	t_coords	v[3];

	obj = &scene->objects[scene->obj_count];
	if (!ft_parse_coords(&obj->triangle.v1, a[1], POS))
		return (0);
	if (!ft_parse_coords(&obj->triangle.v2, a[2], POS))
		return (0);
	if (!ft_parse_coords(&obj->triangle.v3, a[3], POS))
		return (0);
	if (!ft_parse_color(&obj->triangle.rgb, a[4]))
		return (0);
	obj->triangle.color = ft_getcolor(&obj->triangle.rgb);
	v[0] = obj->triangle.v1;
	v[1] = obj->triangle.v2;
	v[2] = obj->triangle.v3;
	*obj = ft_mktriangle(v, obj->triangle.color);
	scene->obj_count++;
	return (1);
}
