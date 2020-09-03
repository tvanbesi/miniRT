/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:09:30 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/03 16:50:14 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void
	ft_shade_sphere(t_surf_pt *p_hit, t_object *obj, t_light *light)
{
	t_coords	n;
	double		facing_ratio;
	t_ray		r;

	n = ft_coo_sub(&p_hit->pos, &obj->sphere.pos);
	ft_normalize(&n);
	r.dir = ft_coo_sub(&light->pos, &p_hit->pos);
	ft_normalize(&r.dir);
	facing_ratio = ft_dot(&n, &r.dir);
	if (facing_ratio < 0.0)
		facing_ratio = 0;
	ft_shade_color(p_hit, obj->sphere.color, light, facing_ratio);
}

void
	ft_shade_flatsurf(t_surf_pt *p_hit, t_object *obj, t_light *light)
{
	double	facing_ratio;
	t_ray	r;

	r.dir = ft_coo_sub(&light->pos, &p_hit->pos);
	ft_normalize(&r.dir);
	facing_ratio = 0.0;
	if (obj->plane.type == PLANE)
		facing_ratio = ft_dot(&obj->plane.norm, &r.dir);
	else if (obj->square.type == SQUARE)
		facing_ratio = ft_dot(&obj->square.norm, &r.dir);
	else if (obj->square.type == TRIANGLE)
		facing_ratio = ft_dot(&obj->triangle.norm, &r.dir);
	facing_ratio = fmax(facing_ratio, -facing_ratio);
	if (obj->plane.type == PLANE)
		ft_shade_color(p_hit, obj->plane.color, light, facing_ratio);
	else if (obj->square.type == SQUARE)
		ft_shade_color(p_hit, obj->square.color, light, facing_ratio);
	else if (obj->square.type == TRIANGLE)
		ft_shade_color(p_hit, obj->triangle.color, light, facing_ratio);
}

void
	ft_handle_light_inside(t_coords *n, t_object *o, t_ray *r, t_light *light, double *fr)
{
	
}

void
	ft_shade_cylinder(t_surf_pt *p_hit, t_object *obj, t_light *light)
{
	t_coords	n;
	t_coords	poshit;
	t_coords	oridposhit2;
	double		facing_ratio;
	t_ray		r;

	t_coords	tmpn;
	t_coords	tmptol;
	double p = ft_dot(&tmpn, &tmptol) / sqrt(ft_dot(&tmpn, &tmpn));

	poshit = ft_coo_sub(&p_hit->pos, &obj->cylinder.pos);
	oridposhit2 = ft_coo_mlt(&obj->cylinder.ori,
	ft_dot(&obj->cylinder.ori, &poshit));
	n = ft_coo_sub(&poshit, &oridposhit2);
	ft_normalize(&n);
	r.dir = ft_coo_sub(&light->pos, &p_hit->pos);
	ft_normalize(&r.dir);
	facing_ratio = ft_dot(&n, &r.dir);

	tmpn = (t_coords){-n.x * obj->cylinder.diameter, -n.y * obj->cylinder.diameter, -n.z * obj->cylinder.diameter};
	tmptol = ft_coo_sub(&light->pos, &p_hit->pos);
	if (obj->cylinder.facehit == INTERIOR && facing_ratio < 0.0 && p > 0.0 && p < obj->cylinder.diameter)
		facing_ratio = -facing_ratio;
	else if (obj->cylinder.facehit == EXTERIOR && facing_ratio < 0.0 && p > 0.0 && p < obj->cylinder.diameter)
		;
	else if (obj->cylinder.facehit == INTERIOR)
		facing_ratio = -facing_ratio;
	if (facing_ratio > 0.0)
		ft_shade_color(p_hit, obj->cylinder.color, light, facing_ratio);
}
