/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 01:56:57 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/01 23:24:25 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coords_cp
	ft_rectocp(t_coords rec)
{
	t_coords_cp	r;

	r.r = sqrt(pow(rec.x, 2.0) + pow(rec.y, 2.0));
	r.t = atan(rec.y / rec.x);
	r.z = rec.z;
	return (r);
}

int
	ft_quadratic_eq(double coeffs[3], double *solutions)
{
	double	d;
	double	q;

	d = pow(coeffs[1], 2) - 4 * coeffs[0] * coeffs[2];
	if (d < 0.0)
		return (0);
	if (d == 0.0)
	{
		solutions[0] = -0.5 * coeffs[1] / coeffs[0];
		solutions[1] = solutions[0];
		return (solutions[0] > 0.0);
	}
	else
	{
		q = coeffs[1] > 0.0 ? -0.5 *
		(coeffs[1] + sqrt(d)) : -0.5 * (coeffs[1] - sqrt(d));
		solutions[0] = q / coeffs[0];
		solutions[1] = coeffs[2] / q;
		if (solutions[0] > solutions[1] && solutions[1] > 0.0)
			ft_swap_double(&solutions[0], &solutions[1]);
		if (solutions[0] < 0.0 && solutions[1] < 0.0)
			return (0);
		return (1);
	}
}
