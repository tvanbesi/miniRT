/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:09:30 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/01 22:47:51 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	ft_shade_cylinder(t_surf_pt *p_hit, t_object *obj, t_light *light)
{
	t_coords	n;
	t_coords	poshit;
	t_coords	oridposhit2;
	double		facing_ratio;
	t_ray		r;

	poshit = ft_coo_sub(&p_hit->pos, &obj->cylinder.pos);
	oridposhit2 = ft_coo_mlt(&obj->cylinder.ori,
	ft_dot(&obj->cylinder.ori, &poshit));
	n = ft_coo_sub(&poshit, &oridposhit2);
	ft_normalize(&n);
	r.dir = ft_coo_sub(&light->pos, &p_hit->pos);
	ft_normalize(&r.dir);
	facing_ratio = ft_dot(&n, &r.dir);
	if (obj->cylinder.lastfacehit == INTERIOR)
		facing_ratio = -facing_ratio;
	ft_shade_color(p_hit, obj->cylinder.color, light, facing_ratio);
}

void
	ft_shade(t_surf_pt *p_hit, t_object *obj, t_light *light)
{
	if (obj->sphere.type == SPHERE)
		ft_shade_sphere(p_hit, obj, light);
	else if (obj->plane.type == PLANE)
		ft_shade_flatsurf(p_hit, obj, light);
	else if (obj->sphere.type == SQUARE)
		ft_shade_flatsurf(p_hit, obj, light);
	else if (obj->cylinder.type == CYLINDER)
		ft_shade_cylinder(p_hit, obj, light);
	else if (obj->triangle.type == TRIANGLE)
		ft_shade_flatsurf(p_hit, obj, light);
}

void
	ft_shade_amblight(t_surf_pt *p_hit, t_object *obj, t_light *amblight)
{
	if (obj->plane.type == PLANE)
		ft_shade_color(p_hit, obj->plane.color, amblight, 1.0);
	else if (obj->plane.type == CYLINDER)
		ft_shade_color(p_hit, obj->cylinder.color, amblight, 1.0);
	else if (obj->plane.type == TRIANGLE)
		ft_shade_color(p_hit, obj->triangle.color, amblight, 1.0);
	else if (obj->plane.type == SPHERE)
		ft_shade_color(p_hit, obj->sphere.color, amblight, 1.0);
	else if (obj->plane.type == SQUARE)
		ft_shade_color(p_hit, obj->square.color, amblight, 1.0);
}
