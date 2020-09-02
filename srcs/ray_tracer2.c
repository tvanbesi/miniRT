/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 22:12:46 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/02 22:29:22 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_coords
	ft_coords_from_ray(t_ray *ray, double solution)
{
	t_coords	r;

	r.x = ray->pos.x + ray->dir.x * solution;
	r.y = ray->pos.y + ray->dir.y * solution;
	r.z = ray->pos.z + ray->dir.z * solution;
	return (r);
}

void
	ft_shadray(t_ray *ray, t_scene *scene, t_surf_pt *p_hit)
{
	int			i;
	int			j;
	int			rayblocked;
	double		d;
	double		solution;

	i = -1;
	while (++i < scene->light_count)
	{
		rayblocked = 0;
		d = ft_dist(&scene->lights[i].pos, &p_hit->pos);
		ray->dir = ft_coo_sub(&scene->lights[i].pos, &p_hit->pos);
		ft_normalize(&ray->dir);
		ray->pos = ft_coo_add(&p_hit->pos, &ray->dir);
		j = -1;
		while (++j < scene->obj_count)
			if (ft_intersect(ray, &scene->objects[j], &solution))
			{
				ray->hit = ft_coords_from_ray(ray, solution);
				if ((rayblocked = (ft_dist(&ray->hit, &ray->pos) < d)))
					break ;
			}
		if (!rayblocked)
			ft_shade(p_hit, &scene->objects[p_hit->iobj], &scene->lights[i]);
	}
}
