/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 01:37:00 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/08/03 22:16:52 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int
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

static int
	ft_intersect_cylinder(t_ray *ray, t_object *object, double *solution)
{
	double		coeffs[3];
	double		*solutions;
	double		z[2];
	t_ray		raytrs;
	t_matrix	*srt;
	t_matrix	*sr;

	raytrs = *ray;
	sr = ft_mat_mlt(&object->cylinder.Si, &object->cylinder.Ri);
	srt = ft_mat_mlt(sr, &object->cylinder.Ti);
	ft_vec_mat_mlt(&raytrs.pos, srt);
	ft_vec_mat_mlt(&raytrs.dir, sr);
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
		else if (solutions[1] > 0.0 && z[1] > 0.0 && z[1] < object->cylinder.height)
		{
			object->cylinder.lastfacehit = INTERIOR;
			*solution = solutions[1];
			return (*solution > 0.0);
		}
	}
	free(solutions);
	return (0);
}

static int
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

static int
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
			p[0] = ft_dot(&hit_to_center, &object->square.e1) / (object->square.height2);
			p[1] = ft_dot(&hit_to_center, &object->square.e2) / (object->square.height2);
			return ((p[0] >= -object->square.height2 && p[0] <= object->square.height2)
			&& (p[1] >= -object->square.height2 && p[1] <= object->square.height2));
		}
	}
	return (0);
}

static int
	ft_isabscissa_inter_positive(t_coords *p1, t_coords *p2)
{
	double	m;
	double	b;

	if (p2->x == p1->x)
		return (0);
	m = (p2->y - p1->y) / (p2->x - p1->x);
	b = p1->y - m * p1->x;
	return ((m >= 0.0 && b < 0.0) || (m < 0.0 && b >= 0.0));
}

static int
	ft_oddeven_vertices_test(t_coords v[3])
{
	int	i;
	int	j;
	int	r;

	i = 0;
	r = 0;
	while (i < 2)
	{
		j = i + 1;
		while (j < 3)
		{
			if ((v[i].y < 0.0 && v[j].y >= 0.0)
			|| (v[i].y >= 0.0 && v[j].y < 0.0))
			{
				if (v[i].x >= 0.0 && v[j].x >= 0.0)
					r++;
				else if ((v[i].x >= 0.0 && v[j].x < 0.0)
				|| (v[i].x < 0.0 && v[j].x >= 0.0))
				{
					if (ft_isabscissa_inter_positive(&v[i], &v[j]))
						r++;
				}
			}
			j++;
		}
		i++;
	}
	return (r);
}

static int
	ft_oddeven_test(t_coords point, t_object tr)
{
	t_coords	v[3];
	t_coords	vcpy[3];
	t_coords	e1;
	t_coords	e2;

	e1 = ft_coo_sub(&tr.triangle.v1, &tr.triangle.v2);
	ft_normalize(&e1);
	e2 = ft_cross(&e1, &tr.triangle.norm);
	ft_normalize(&e2);
	v[0] = ft_coo_sub(&tr.triangle.v1, &point);
	v[1] = ft_coo_sub(&tr.triangle.v2, &point);
	v[2] = ft_coo_sub(&tr.triangle.v3, &point);
	vcpy[0] = v[0];
	vcpy[1] = v[1];
	vcpy[2] = v[2];
	v[0].x = ft_dot(&e1, &vcpy[0]);
	v[0].y = ft_dot(&e2, &vcpy[0]);
	v[1].x = ft_dot(&e1, &vcpy[1]);
	v[1].y = ft_dot(&e2, &vcpy[1]);
	v[2].x = ft_dot(&e1, &vcpy[2]);
	v[2].y = ft_dot(&e2, &vcpy[2]);
	return (ft_oddeven_vertices_test(v) % 2 == 1);
}

static int
	ft_intersect_triangle(t_ray *ray, t_object *object, double *solution)
{
	t_object	tr_plane;
	int			smallest_dim;
	t_coords	point;

	tr_plane = ft_mkplane(object->triangle.v1, object->triangle.norm, object->triangle.color);
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

int
	ft_intersect(t_ray *ray, t_object *object, double *solution)
{
	if (object->sphere.type == SPHERE)
		return (ft_intersect_sphere(ray, object, solution));
	else if (object->plane.type == PLANE)
		return (ft_intersect_plane(ray, object, solution));
	else if (object->square.type == SQUARE)
		return (ft_intersect_square(ray, object, solution));
	else if (object->cylinder.type == CYLINDER)
		return (ft_intersect_cylinder(ray, object, solution));
	else if (object->triangle.type == TRIANGLE)
		return (ft_intersect_triangle(ray, object, solution));
	else
		return (0);
}
