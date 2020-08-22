/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 02:27:24 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/08/04 18:37:38 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void
	ft_swap_double(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int
	ft_getcolor(t_color *rgb)
{
	return (rgb->r * 65536 + rgb->g * 256 + rgb->b);
}

t_color
	ft_getrgb(int color)
{
	t_color	rgb;

	rgb.r = color / 65536;
	color -= rgb.r * 65536;
	rgb.g = color / 256;
	color -= rgb.g * 256;
	rgb.b = color;
	return (rgb);
}

t_camera
	ft_mkcamera(t_coords pos, t_coords ori)
{
	t_camera	r;

	r.pos = pos;
	r.ori = ori;
	return (r);
}

t_light
	ft_mklight(t_coords pos, int color, double lum)
{
	t_light r;

	r.pos = pos;
	r.color = color;
	r.lum = lum;
	return (r);
}

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
	ft_mkcylinder(t_coords pos, t_coords ori, double height, double radius, int color)
{
	t_object	r;
	t_cylinder	obj;
	t_matrix	*m;
	t_coords	tmp;

	obj.type = CYLINDER;
	obj.height = height;
	obj.color = color;
	obj.pos = pos;
	obj.Ri = *ft_mat_rot(&ori);
	tmp = (t_coords){0.0, 0.0, 1.0};
	ft_vec_mat_mlt(&tmp, &obj.Ri);
	obj.ori = tmp;
	ft_normalize(&obj.ori);
	obj.Ri = *ft_mat_inv(&obj.Ri);
	obj.Ti = *ft_mat_trans(&pos);
	obj.Ti = *ft_mat_inv(&obj.Ti);
	obj.Si = *ft_mat_scal(&(t_coords){radius, radius, 1.0});
	obj.Si = *ft_mat_inv(&obj.Si);
	r.cylinder = obj;
	return (r);
}

t_object
	ft_mkplane(t_coords pos, t_coords ori, int color)
{
	t_object	r;
	t_plane		obj;
	t_matrix	*m;

	obj.type = PLANE;
	obj.pos = pos;
	obj.norm = (t_coords){0.0, 0.0, 1.0};
	m = ft_mat_rot(&ori);
	ft_vec_mat_mlt(&obj.norm, m);
	free(m);
	ft_normalize(&obj.norm);
	obj.color = color;
	r.plane = obj;
	return (r);
}

t_object
	ft_mksquare(t_coords pos, t_coords ori, double height, int color)
{
	t_object	r;
	t_square	obj;
	t_matrix	*m;

	obj.type = SQUARE;
	obj.pos = pos;
	obj.norm = (t_coords){0.0, 0.0, 1.0};
	obj.e1 = (t_coords){1.0, 0.0, 0.0};
	obj.e2 = (t_coords){0.0, 1.0, 0.0};
	m = ft_mat_rot(&ori);
	ft_vec_mat_mlt(&obj.norm, m);
	ft_vec_mat_mlt(&obj.e1, m);
	ft_vec_mat_mlt(&obj.e2, m);
	free(m);
	ft_normalize(&obj.norm);
	ft_normalize(&obj.e1);
	ft_normalize(&obj.e2);
	obj.height2 = height / 2.0;
	obj.e1 = ft_coo_mlt(&obj.e1, obj.height2);
	obj.e2 = ft_coo_mlt(&obj.e2, obj.height2);
	obj.color = color;
	r.square = obj;
	return (r);
}

t_object
	ft_mktriangle(t_coords *vertices, int color)
{
	t_object	r;
	t_triangle	obj;
	t_coords	v32;
	t_coords	v12;

	obj.type = TRIANGLE;
	obj.v1 = vertices[0];
	obj.v2 = vertices[1];
	obj.v3 = vertices[2];
	v32 = ft_coo_sub(&obj.v3, &obj.v2);
	v12 = ft_coo_sub(&obj.v1, &obj.v2);
	obj.norm = ft_cross(&v32, &v12);
	ft_normalize(&obj.norm);
	obj.color = color;
	r.triangle = obj;
	return (r);
}
