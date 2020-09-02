/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 01:15:58 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/02 22:27:39 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void
	ft_print_coords(t_coords c)
{
	printf("x:\t%f\ty:\t%f\tz:\t%f\n", c.x, c.y, c.z);
}

void
	ft_print_rgb(t_color *rgb)
{
	printf("%d,%d,%d\n", rgb->r, rgb->g, rgb->b);
}

void
	ft_print_matrix(t_matrix *matrix)
{
	for (int k = 0; k < 4; k++)
	{
		for (int l = 0; l < 4; l++)
		{
			printf("%.3f\t", matrix->v[k][l]);
		}
		printf("\n");
	}
	printf("\n");
}

void
	ft_print_matrix3(t_matrix3 *m)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			printf("%.3f\t", m->v[i][j]);
		printf("\n");
	}
	printf("\n");
}

void
	ft_print_coordscp(t_coords_cp c)
{
	printf("r:\t%f\tt:\t%f\tz:\t%f\n", c.r, c.t, c.z);
}

void
	ft_print_screen(t_screen *screen)
{
	printf("tfov2\t%f\nratio\t%f\nwidth\t%d\nheight\t%d\nmlx\t%p\nwindow\t%p\n",
	screen->tfov2, screen->aspect_ratio, screen->width, screen->height, screen->mlx, screen->window);
}

void
	ft_print_scene(t_scene *scene)
{
	printf("camselect\t%d\ncam_count\t%d\nlight_count\t%d\nobj_count\t%d\n",
	scene->camselect, scene->cam_count, scene->light_count, scene->obj_count);
}

void
	ft_print_camera(t_camera *cam)
{
	printf("POS\t");
	ft_print_coords(cam->pos);
	printf("ORI\t");
	ft_print_coords(cam->ori);
	printf("fov\t%d\n", cam->fov);
}

void
	ft_print_light(t_light *light)
{
	printf("POS\t");
	ft_print_coords(light->pos);
	printf("RGB\t");
	ft_print_rgb(&light->rgb);
	printf("lum\t%f\n", light->lum);
}
