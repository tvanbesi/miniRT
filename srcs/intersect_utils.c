/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 15:51:43 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/02 22:28:11 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int
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

int
	ft_oddeven_vertices_test(t_coords v[3])
{
	int	i;
	int	j;
	int	r;

	i = -1;
	r = 0;
	while (++i < 2)
	{
		j = i;
		while (++j < 3)
		{
			if ((v[i].y < 0.0 && v[j].y >= 0.0)
			|| (v[i].y >= 0.0 && v[j].y < 0.0))
			{
				if (v[i].x >= 0.0 && v[j].x >= 0.0)
					r++;
				else if ((v[i].x >= 0.0 && v[j].x < 0.0)
				|| (v[i].x < 0.0 && v[j].x >= 0.0))
					if (ft_isabscissa_inter_positive(&v[i], &v[j]))
						r++;
			}
		}
	}
	return (r);
}

int
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
