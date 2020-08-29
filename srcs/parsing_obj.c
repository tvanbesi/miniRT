/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 13:11:15 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/08/28 12:18:14 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int
    ft_parse_res(char **a, t_scene *scene)
{
	t_screen	*screen;

	if (scene->res_set)
		return (0);
	screen = &scene->screen;
    screen->width = ft_atoi(a[1]);
    screen->height = ft_atoi(a[2]);
    if (screen->width >= 0 && screen->height >= 0)
	{
		if (screen->width > MAX_RESX)
			screen->width = MAX_RESX;
		if (screen->height > MAX_RESY)
			screen->height = MAX_RESY;
		screen->mlx = mlx_init();
		screen->aspect_ratio = (double)screen->width / (double)screen->height;
		screen->window = mlx_new_window(screen->mlx, screen->width, screen->height, "miniRT");
		scene->res_set = 1;
        return (1);
	}
    return (0);
}

int
    ft_parse_amblight(char **a, t_scene *scene)
{
	t_light	*amblight;

	if (scene->amb_set)
		return (0);
	amblight = &scene->amblight;
	amblight->lum = ft_atof(a[1]);
	if (!ft_isvvalid_lum(amblight->lum))
		return (0);
	if (!ft_parse_color(&amblight->rgb, a[2]))
		return (0);
	amblight->color = ft_getcolor(&amblight->rgb);
	scene->amb_set = 1;
	return (1);
}

int
	ft_parse_cam(char **a, t_scene *scene)
{
	t_camera	*cam;

	cam = &scene->cameras[scene->cam_count];
	if (!ft_parse_coords(&cam->pos, a[1], POS))
		return (0);
	if (!ft_parse_coords(&cam->ori, a[2], ORI))
		return (0);
	cam->fov = ft_atoi(a[3]);
	if (!ft_isvalid_fov(cam->fov))
		return (0);
	scene->cam_count++;
	return (1);
}

int
	ft_parse_light(char **a, t_scene *scene)
{
	t_light	*light;

	light = &scene->lights[scene->light_count];
	if (!ft_parse_coords(&light->pos, a[1], POS))
		return (0);
	light->lum = ft_atof(a[2]);
	if (!ft_isvvalid_lum(light->lum))
		return (0);
	if (!ft_parse_color(&light->rgb, a[3]))
		return (0);
	light->color = ft_getcolor(&light->rgb);
	scene->light_count++;
	return (1);
}

int
	ft_parse_sphere(char **a, t_scene *scene)
{
	t_object	*obj;

	obj = &scene->objects[scene->obj_count];
	if (!ft_parse_coords(&obj->sphere.pos, a[1], POS))
		return (0);
	obj->sphere.diameter = ft_atof(a[2]);
	if (obj->sphere.diameter <= 0.0)
		return (0);
	if (!ft_parse_color(&obj->sphere.rgb, a[3]))
		return (0);
	obj->sphere.color = ft_getcolor(&obj->sphere.rgb);
	*obj = ft_mksphere(obj->sphere.pos, obj->sphere.diameter, obj->sphere.color);
	scene->obj_count++;
	return (1);
}

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
	*obj = ft_mksquare(obj->square.pos, obj->square.ori, obj->square.height, obj->square.color);
	scene->obj_count++;
	return (1);
}

int
	ft_parse_cylinder(char **a, t_scene *scene)
{
	t_object	*obj;

	obj = &scene->objects[scene->obj_count];
	if (!ft_parse_coords(&obj->cylinder.pos, a[1], POS))
		return (0);
	if (!ft_parse_coords(&obj->cylinder.ori, a[2], ORI))
		return (0);
	obj->cylinder.radius = ft_atof(a[3]) / 2.0;
	obj->cylinder.height = ft_atof(a[4]);
	if (obj->cylinder.radius <= 0.0 || obj->cylinder.height <= 0.0)
		return (0);
	if (!ft_parse_color(&obj->cylinder.rgb, a[5]))
		return (0);
	obj->cylinder.color = ft_getcolor(&obj->cylinder.rgb);
	*obj = ft_mkcylinder(obj->cylinder.pos, obj->cylinder.ori, obj->cylinder.height, obj->cylinder.radius, obj->cylinder.color);
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