/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 21:32:48 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/08/29 17:22:11 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_ray
	*ft_mkray(t_screen *screen, t_scene *scene, int x, int y)
{
	t_ray	*r;
	double	px;
	double	py;
	double	t;
	
	if (!(r = (t_ray*)malloc(sizeof(*r))))
		return (NULL);
	px = (2.0 * (((double)x - 0.5) / (double)screen->width) - 1.0) * screen->tfov2;
	py = 1.0 - 2.0 * (((double)y - 0.5) / (double)screen->height) * screen->tfov2 * screen->aspect_ratio;
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
	ft_shadray(t_ray *ray, t_scene *scene, t_surf_pt *p_hit)
{
	int			i;
	int			j;
	int			rayblocked;
	double		d;
	double		solution;
	t_coords	tmp;

	i = 0;
	while (i < scene->light_count)
	{
		rayblocked = 0;
		d = ft_dist(&scene->lights[i].pos, &p_hit->pos);
		ray->dir = ft_coo_sub(&scene->lights[i].pos, &p_hit->pos);
		ft_normalize(&ray->dir);
		ray->pos = ft_coo_add(&p_hit->pos, &ray->dir);
		j = 0;
		while (j < scene->obj_count)
		{
			if (ft_intersect(ray, &scene->objects[j], &solution))
			{
				tmp.x = ray->pos.x + ray->dir.x * solution;
				tmp.y = ray->pos.y + ray->dir.y * solution;
				tmp.z = ray->pos.z + ray->dir.z * solution;
				if ((rayblocked = (ft_dist(&tmp, &ray->pos) < d)))
					break;
			}
			j++;
		}
		if (!rayblocked)
			ft_shade(p_hit, &scene->objects[p_hit->iobj], &scene->lights[i]);
		i++;
	}
}

int
	ft_ray_tracer(t_scene *scene, unsigned char *data_addr)
{
	int			i;
	int			j;
	t_surf_pt	p_hit;
	t_ray		*ray;
	int			*p;

	i = 0;
	j = 0;
	while (i++ < scene->screen.height)
	{
		while (j++ < scene->screen.width)
		{
			if (!(ray = ft_mkray(&scene->screen, scene, j, i)))
				return (0);
			p_hit.color = 0;
			ft_primray(ray, scene, &p_hit);
			if (p_hit.d_to_ori != INFINITY)
			{
				ft_shade_amblight(&p_hit, &scene->objects[p_hit.iobj], &scene->amblight);
				ft_shadray(ray, scene, &p_hit);
				p = (int*)data_addr;
				*p = p_hit.color;
				data_addr += 4;
			}
			free(ray);
		}
		j = 0;
	}
	return (1);
}
