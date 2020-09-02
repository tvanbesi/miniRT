/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vector2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 18:23:31 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/02 22:28:31 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double
	ft_dist(t_coords *a, t_coords *b)
{
	t_coords	tmp;

	tmp = ft_coo_sub(a, b);
	return (sqrt(pow(tmp.x, 2) + pow(tmp.y, 2) + pow(tmp.z, 2)));
}

void
	ft_vec_mat_mlt(t_coords *v, t_matrix *m)
{
	t_coords tmp;

	tmp = *v;
	v->x = tmp.x * m->v[0][0] + tmp.y * m->v[0][1]
	+ tmp.z * m->v[0][2] + 1.0 * m->v[0][3];
	v->y = tmp.x * m->v[1][0] + tmp.y * m->v[1][1]
	+ tmp.z * m->v[1][2] + 1.0 * m->v[1][3];
	v->z = tmp.x * m->v[2][0] + tmp.y * m->v[2][1]
	+ tmp.z * m->v[2][2] + 1.0 * m->v[2][3];
}

void
	ft_normalize(t_coords *a)
{
	double	tmp;

	tmp = 1.0 / sqrt(pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2));
	a->x *= tmp;
	a->y *= tmp;
	a->z *= tmp;
}
