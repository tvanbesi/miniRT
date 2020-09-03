/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 21:32:48 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/03 16:47:08 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_ray
	*ft_mkray(t_screen *screen, t_scene *scene, int x, int y)
{
	t_ray	*r;
	double	px;
	double	py;

	if (!(r = (t_ray*)malloc(sizeof(*r))))
		return (NULL);
	px = (2.0 * (((double)x - 0.5) / (double)screen->width) - 1.0)
	* screen->tfov2;
	py = 1.0 - 2.0 * (((double)y - 0.5) / (double)screen->height)
	* screen->tfov2 * screen->aspect_ratio;
	r->dir = (t_coords){px, py, 1.0};
	ft_vec_mat_mlt(&r->dir, scene->ctw_matrix);
	ft_normalize(&r->dir);
	r->pos = scene->cameras[scene->camselect].pos;
	return (r);
}

static void
	ft_primray(t_ray *ray, t_scene *scene, t_surf_pt *p_hit)
{
	int			i;
	double		d;
	double		solution;
	t_coords	tmp;

	p_hit->d_to_ori = INFINITY;
	i = 0;
	while (i < scene->obj_count)
	{
		if (ft_intersect(ray, &scene->objects[i], &solution))
		{
			tmp.x = ray->pos.x + ray->dir.x * solution;
			tmp.y = ray->pos.y + ray->dir.y * solution;
			tmp.z = ray->pos.z + ray->dir.z * solution;
			if ((d = ft_dist(&tmp, &ray->pos)) < p_hit->d_to_ori)
			{
				p_hit->pos = tmp;
				p_hit->d_to_ori = d;
				p_hit->iobj = i;
			}
		}
		i++;
	}
}

static void
	ft_color_pixel(unsigned char **data_addr, int color)
{
	int	*p;

	p = (int*)*data_addr;
	*p = color;
	*data_addr += 4;
}

static void
	ft_ssc(t_scene *scene, t_surf_pt *p_hit,
	unsigned char **data_addr, t_ray *ray)
{
	ft_shade_amblight(p_hit, &scene->objects[p_hit->iobj], &scene->amblight);
	if (scene->objects[p_hit->iobj].cylinder.type == CYLINDER)
		scene->objects[p_hit->iobj].cylinder.setfacehit = 1;
	ft_shadray(ray, scene, p_hit);
	if (scene->objects[p_hit->iobj].cylinder.type == CYLINDER)
		scene->objects[p_hit->iobj].cylinder.setfacehit = 0;
	ft_color_pixel(data_addr, p_hit->color);
}

int
	ft_ray_tracer(t_scene *scene, unsigned char *data_addr)
{
	int			i;
	int			j;
	t_surf_pt	p_hit;
	t_ray		*ray;

	i = 0;
	j = 0;
	while (i++ < scene->screen.height)
	{
		while (j++ < scene->screen.width)
		{
			if (!(ray = ft_mkray(&scene->screen, scene, j, i)))
				return (0);
			p_hit.color = 0.0;
			ft_primray(ray, scene, &p_hit);
			if (p_hit.d_to_ori != INFINITY)
				ft_ssc(scene, &p_hit, &data_addr, ray);
			free(ray);
		}
		j = 0;
	}
	return (1);
}
