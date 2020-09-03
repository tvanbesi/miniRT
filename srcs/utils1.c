/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 02:27:24 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/03 03:19:51 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void
	ft_mkscene(t_scene *scene)
{
	scene->cam_count = 0;
	scene->light_count = 0;
	scene->obj_count = 0;
	scene->res_set = 0;
	scene->amb_set = 0;
	scene->ctw_matrix = NULL;
}

void
	ft_selectcam(t_scene *scene, int camselect)
{
	scene->camselect = camselect;
	scene->screen.tfov2 = tan((double)scene->cameras[camselect].fov
	/ 2.0 * M_PI / 180);
	free(scene->ctw_matrix);
	scene->ctw_matrix = ft_mat_rot(&scene->cameras[camselect].ori);
}
