/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 18:38:30 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/02 22:28:42 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix
	*ft_mat_adj(t_matrix *m)
{
	t_matrix	*r;
	t_matrix3	*m3;
	int			i;
	int			j;

	if (!(r = (t_matrix*)malloc(sizeof(*r))))
		return (NULL);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m3 = ft_mat4tomat3(m, j, i);
			r->v[i][j] = pow(-1, i + j + 2) * ft_mat3_det(m3);
			free(m3);
			j++;
		}
		i++;
	}
	return (r);
}

t_matrix
	*ft_mat_inv(t_matrix *m)
{
	t_matrix	*r;
	double		det;
	int			i;
	int			j;

	if (!(r = (t_matrix*)malloc(sizeof(*r))))
		return (NULL);
	det = 1.0 / ft_mat_det(m);
	r = ft_mat_adj(m);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			r->v[i][j] *= det;
			j++;
		}
		i++;
	}
	return (r);
}

static void
	*ft_mat_free(t_matrix *mx, t_matrix *my, t_matrix *mz, t_matrix *r)
{
	free(mx);
	free(my);
	free(mz);
	free(r);
	return (NULL);
}

t_matrix
	*ft_mat_rot(t_coords *c)
{
	t_matrix	*mx;
	t_matrix	*my;
	t_matrix	*mz;
	t_matrix	*r;

	my = NULL;
	mz = NULL;
	r = NULL;
	if (!(mx = ft_mat_rotx(c->x * M_PI)))
		return (NULL);
	if (!(my = ft_mat_roty(c->y * M_PI)))
		return (ft_mat_free(mx, my, mz, r));
	if (!(mz = ft_mat_rotz(c->z * M_PI)))
		return (ft_mat_free(mx, my, mz, r));
	if (!(r = ft_mat_mlt(ft_mat_mlt(mx, my), mz)))
		return (ft_mat_free(mx, my, mz, r));
	free(mx);
	free(my);
	free(mz);
	return (r);
}
