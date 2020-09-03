/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_obj2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 16:02:02 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/03 03:57:48 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_ray
	ft_ray_rotate(t_ray *ray, t_object *object)
{
	t_ray		raytrs;
	t_matrix	*srt;
	t_matrix	*sr;

	raytrs = *ray;
	sr = ft_mat_mlt(object->cylinder.si, object->cylinder.ri);
	srt = ft_mat_mlt(sr, object->cylinder.ti);
	ft_vec_mat_mlt(&raytrs.pos, srt);
	ft_vec_mat_mlt(&raytrs.dir, sr);
	free(sr);
	free(srt);
	return (raytrs);
}

static int
	ft_cylinder_solution(double *solutions, double *solution,
	t_object *object, int lastfacehit)
{
	object->cylinder.lastfacehit = lastfacehit;
	*solution = solutions[lastfacehit];
	free(solutions);
	return (*solution > 0.0);
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
			return (ft_cylinder_solution(solutions, solution, object, 0));
		else if (solutions[1] > 0.0 && z[1] > 0.0
		&& z[1] < object->cylinder.height)
			return (ft_cylinder_solution(solutions, solution, object, 1));
	}
	free(solutions);
	return (0);
}

static int
	ft_square_hittest(double p[2], double height)
{
	return ((p[0] >= -height
	&& p[0] <= height)
	&& (p[1] >= -height
	&& p[1] <= height));
}

int
	ft_intersect_square(t_ray *ray, t_object *object, double *solution)
{
	double		d;
	double		p[2];
	t_coords	l;
	t_coords	hit_to_center;
	t_coords	tmp;

	d = ft_dot(&object->square.norm, &ray->dir);
	if (fabs(d) > 1e-6)
	{
		l = ft_coo_sub(&object->square.pos, &ray->pos);
		*solution = ft_dot(&l, &object->square.norm) / d;
		if (*solution >= 0.0)
		{
			tmp.x = ray->pos.x + ray->dir.x * *solution;
			tmp.y = ray->pos.y + ray->dir.y * *solution;
			tmp.z = ray->pos.z + ray->dir.z * *solution;
			hit_to_center = ft_coo_sub(&tmp, &object->square.pos);
			p[0] = ft_dot(&hit_to_center, &object->square.e1)
			/ (object->square.height2);
			p[1] = ft_dot(&hit_to_center, &object->square.e2)
			/ (object->square.height2);
			return (ft_square_hittest(p, object->square.height2));
		}
	}
	return (0);
}
