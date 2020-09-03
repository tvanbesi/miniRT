/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 22:50:46 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/03 03:15:41 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object
	ft_mksphere(t_coords pos, double diameter, int color)
{
	t_object	r;
	t_sphere	obj;

	obj.type = SPHERE;
	obj.pos = pos;
	obj.radius = diameter / 2.0;
	obj.color = color;
	r.sphere = obj;
	return (r);
}

t_object
	ft_mkcylinder(t_coords pos, t_coords ori,
	double hr[2], int color)
{
	t_object	r;
	t_cylinder	obj;
	t_coords	tmp;

	obj.type = CYLINDER;
	obj.height = hr[0];
	obj.color = color;
	obj.pos = pos;
	obj.ri = ft_mat_rot(&ori);
	tmp = (t_coords){0.0, 0.0, 1.0};
	ft_vec_mat_mlt(&tmp, obj.ri);
	obj.ori = tmp;
	ft_normalize(&obj.ori);
	obj.ri = ft_mat_inv(obj.ri);
	obj.ti = ft_mat_trans(&pos);
	obj.ti = ft_mat_inv(obj.ti);
	obj.si = ft_mat_scal(&(t_coords){hr[1], hr[1], 1.0});
	obj.si = ft_mat_inv(obj.si);
	r.cylinder = obj;
	return (r);
}
