/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 15:55:14 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/08/30 15:55:28 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
