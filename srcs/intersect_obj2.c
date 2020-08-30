/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_obj2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 16:02:02 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/08/30 16:27:19 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_ray
	ft_ray_rotate(t_ray *ray, t_object *object)
{
	t_ray		raytrs;
	t_matrix	*srt;
	t_matrix	*sr;

	raytrs = *ray;
	sr = ft_mat_mlt(&object->cylinder.Si, &object->cylinder.Ri);
	srt = ft_mat_mlt(sr, &object->cylinder.Ti);
	ft_vec_mat_mlt(&raytrs.pos, srt);
	ft_vec_mat_mlt(&raytrs.dir, sr);
	return (raytrs);
}

int
	ft_intersect_cylinder(t_ray *ray, t_object *object, double *solution)
{
	double		coeffs[3];
	double		*solutions;
	double		z[2];
	t_ray		raytrs;

	raytrs = ft_ray_rotate(ray, object);
	coeffs[0] = pow(raytrs.dir.x, 2) + pow(raytrs.dir.y, 2);
	coeffs[1] = 2 * (raytrs.pos.x * raytrs.dir.x + raytrs.pos.y * raytrs.dir.y);
	coeffs[2] = pow(raytrs.pos.x, 2) + pow(raytrs.pos.y, 2) - 1;
	if (!(solutions = (double*)malloc(sizeof(double) * 2)))
		return (0);
	if (ft_quadratic_eq(coeffs, solutions))
	{
		z[0] = raytrs.pos.z + raytrs.dir.z * solutions[0];
		z[1] = raytrs.pos.z + raytrs.dir.z * solutions[1];
		if (solutions[0] > 0.0 && z[0] > 0.0 && z[0] < object->cylinder.height)
		{
			object->cylinder.lastfacehit = EXTERIOR;
			*solution = solutions[0];
			return (*solution > 0.0);
		}
		else if (solutions[1] > 0.0 && z[1] > 0.0
		&& z[1] < object->cylinder.height)
		{
			object->cylinder.lastfacehit = INTERIOR;
			*solution = solutions[1];
			return (*solution > 0.0);
		}
	}
	free(solutions);
	return (0);
}
