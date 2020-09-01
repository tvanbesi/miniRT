/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vector1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 02:19:18 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/01 18:24:16 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double
	ft_dot(t_coords *a, t_coords *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_coords
	ft_cross(t_coords *a, t_coords *b)
{
	return ((t_coords){a->y * b->z - a->z * b->y,
	a->z * b->x - a->x * b->z,
	a->x * b->y - a->y * b->x});
}

t_coords
	ft_coo_sub(t_coords *a, t_coords *b)
{
	return ((t_coords){a->x - b->x, a->y - b->y, a->z - b->z});
}

t_coords
	ft_coo_add(t_coords *a, t_coords *b)
{
	return ((t_coords){a->x + b->x, a->y + b->y, a->z + b->z});
}

t_coords
	ft_coo_mlt(t_coords *a, double b)
{
	return ((t_coords){a->x * b, a->y * b, a->z * b});
}
