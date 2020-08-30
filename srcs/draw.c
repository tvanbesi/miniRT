/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 17:16:45 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/08/29 17:22:32 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int
	ft_draw_image(t_scene *scene, int camselect)
{
	ft_selectcam(scene, camselect);
	scene->images[scene->camselect] = ft_mkimage(&scene->screen);
	if (!ft_ray_tracer(scene, scene->images[scene->camselect].data_addr))
		return (0);
	return (1);
}

int
	ft_draw_all_images(t_scene *scene)
{
	int i;

	i = 0;
	while (i++ < scene->cam_count)
		if (!ft_draw_image(scene, i - 1))
			return (0);
	return (1);
}