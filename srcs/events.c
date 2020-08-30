/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 17:19:10 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/08/30 16:16:09 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int
	ft_close(void)
{
	exit(0);
}

int
	ft_key_hook(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene*)param;
	if (keycode == 49)
	{
		mlx_clear_window(scene->screen.mlx, scene->screen.window);
		mlx_put_image_to_window(scene->screen.mlx, scene->screen.window,
		scene->images[scene->camselect].ptr, 0, 0);
		scene->camselect++;
		if (scene->camselect >= scene->cam_count)
			scene->camselect = 0;
	}
	if (keycode == 53)
	{
		ft_clear_images(scene);
		mlx_destroy_window(scene->screen.mlx, scene->screen.window);
		ft_close();
	}
	return (0);
}