/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 13:11:15 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/09/04 12:35:57 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int
	ft_parse_res(char **a, t_scene *scene)
{
	t_screen	*screen;
	int			max_resx;
	int			max_resy;

	if (scene->res_set)
		return (0);
	screen = &scene->screen;
	screen->width = ft_atoi(a[1]);
	screen->height = ft_atoi(a[2]);
	if (screen->width >= 0 && screen->height >= 0)
	{
		screen->mlx = mlx_init();
		mlx_get_screen_size(scene->screen.mlx, &max_resx, &max_resy);
		if (screen->width > max_resx)
			screen->width = max_resx;
		if (screen->height > max_resy)
			screen->height = max_resy;
		screen->aspect_ratio = (double)screen->width / (double)screen->height;
		screen->window = mlx_new_window(screen->mlx,
		screen->width, screen->height, "miniRT");
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

	if (scene->cam_count >= MAX_CAMERAS)
		return (0);
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

	if (scene->light_count > MAX_LIGHTS)
		return (0);
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

	if (scene->obj_count >= MAX_OBJECTS)
		return (0);
	obj = &scene->objects[scene->obj_count];
	if (!ft_parse_coords(&obj->sphere.pos, a[1], POS))
		return (0);
	obj->sphere.diameter = ft_atof(a[2]);
	if (obj->sphere.diameter <= 0.0)
		return (0);
	if (!ft_parse_color(&obj->sphere.rgb, a[3]))
		return (0);
	obj->sphere.color = ft_getcolor(&obj->sphere.rgb);
	*obj = ft_mksphere(obj->sphere.pos,
	obj->sphere.diameter, obj->sphere.color);
	scene->obj_count++;
	return (1);
}
