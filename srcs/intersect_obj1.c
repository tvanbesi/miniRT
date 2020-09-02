/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_obj1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 01:37:00 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/02 22:28:00 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int
	ft_intersect_sphere(t_ray *ray, t_object *object, double *solution)
{
	t_coords	l;
	double		coeffs[3];
	double		*solutions;

	l = ft_coo_sub(&ray->pos, &object->sphere.pos);
	coeffs[0] = ft_dot(&ray->dir, &ray->dir);
	coeffs[1] = 2.0 * ft_dot(&ray->dir, &l);
	coeffs[2] = ft_dot(&l, &l) - pow(object->sphere.radius, 2);
	if (!(solutions = (double*)malloc(sizeof(double) * 2)))
		return (0);
	if (!ft_quadratic_eq(coeffs, solutions))
		return (0);
	*solution = (solutions[0] > 0.0) ? solutions[0] : solutions[1];
	free(solutions);
	return (*solution > 0.0);
}

int
	ft_intersect_plane(t_ray *ray, t_object *object, double *solution)
{
	double		d;
	t_coords	l;

	d = ft_dot(&object->plane.norm, &ray->dir);
	if (fabs(d) > 1e-6)
	{
		l = ft_coo_sub(&object->plane.pos, &ray->pos);
		*solution = ft_dot(&l, &object->plane.norm) / d;
		return (*solution >= 0.0);
	}
	return (0);
}

int
	ft_intersect_triangle(t_ray *ray, t_object *object, double *solution)
{
	t_object	tr_plane;
	t_coords	point;

	tr_plane = ft_mkplane(object->triangle.v1,
	object->triangle.norm, object->triangle.color);
	if (ft_intersect_plane(ray, &tr_plane, solution))
	{
		point = (t_coords){ray->dir.x, ray->dir.y, ray->dir.z};
		point = ft_coo_mlt(&point, *solution);
		point = ft_coo_add(&point, &ray->pos);
		if (ft_oddeven_test(point, *object))
			return (1);
	}
	return (0);
}
