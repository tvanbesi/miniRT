/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 22:37:13 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/09/01 23:22:08 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_image
	ft_mkimage(t_screen *screen)
{
	t_image	r;

	r.bits_per_pixel = BITS_PER_PIXEL;
	r.size_line = 4 * screen->width;
	r.endian = 0;
	r.ptr = mlx_new_image(screen->mlx, screen->width, screen->height);
	r.data_addr = mlx_get_data_addr(r.ptr,
	&r.bits_per_pixel, &r.size_line, &r.endian);
	return (r);
}

void
	ft_clear_images(t_scene *scene)
{
	while (scene->cam_count-- > 0)
		mlx_destroy_image(scene->screen.mlx,
		scene->images[scene->cam_count].ptr);
}
