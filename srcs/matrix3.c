/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 18:38:30 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/03 03:15:26 by tvanbesi         ###   ########.fr       */
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

	det = 1.0 / ft_mat_det(m);
	r = ft_mat_adj(m);
	free(m);
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
	*ft_mat_free(t_matrix *m[5])
{
	int	i;

	i = 0;
	while (i++ < 5)
		free(m[i]);
	return (NULL);
}

t_matrix
	*ft_mat_rot(t_coords *c)
{
	t_matrix	*m[5];
	int			i;

	i = 0;
	while (i++ < 5)
		m[i - 1] = NULL;
	if (!(m[0] = ft_mat_rotx(c->x * M_PI)))
		return (ft_mat_free(m));
	if (!(m[1] = ft_mat_roty(c->y * M_PI)))
		return (ft_mat_free(m));
	if (!(m[2] = ft_mat_rotz(c->z * M_PI)))
		return (ft_mat_free(m));
	if (!(m[3] = ft_mat_mlt(m[0], m[1])))
		return (ft_mat_free(m));
	if (!(m[4] = ft_mat_mlt(m[3], m[2])))
		return (ft_mat_free(m));
	i = 0;
	while (i++ < 4)
		free(m[i - 1]);
	return (m[4]);
}
