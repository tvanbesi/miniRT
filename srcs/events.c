/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 17:19:10 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/09/04 13:02:27 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int
	ft_close(void *param)
{
	t_scene *scene;

	scene = (t_scene*)param;
	ft_clear_images(scene);
	ft_clear_objects(scene);
	if (scene->screen.mlx && scene->screen.window)
		mlx_destroy_window(scene->screen.mlx, scene->screen.window);
	exit(0);
}

int
	ft_key_hook(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene*)param;
	if (keycode == 32)
	{
		mlx_clear_window(scene->screen.mlx, scene->screen.window);
		mlx_put_image_to_window(scene->screen.mlx, scene->screen.window,
		scene->images[scene->camselect].ptr, 0, 0);
		scene->camselect++;
		if (scene->camselect >= scene->cam_count)
			scene->camselect = 0;
	}
	else if (keycode == 113 || keycode == 65307)
		ft_close((void*)scene);
	return (0);
}
