/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 17:16:45 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/09/03 03:38:57 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
