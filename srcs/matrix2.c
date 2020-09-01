/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 18:39:03 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/01 18:48:22 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_matrix
	*ft_mat_rotx(double a)
{
	t_matrix	*r;

	if (!(r = (t_matrix*)malloc(sizeof(*r))))
		return (NULL);
	r->v[0][0] = 1.0;
	r->v[0][1] = 0.0;
	r->v[0][2] = 0.0;
	r->v[0][3] = 0.0;
	r->v[1][0] = 0.0;
	r->v[1][1] = cos(a);
	r->v[1][2] = -sin(a);
	r->v[1][3] = 0.0;
	r->v[2][0] = 0.0;
	r->v[2][1] = sin(a);
	r->v[2][2] = cos(a);
	r->v[2][3] = 0.0;
	r->v[3][0] = 0.0;
	r->v[3][1] = 0.0;
	r->v[3][2] = 0.0;
	r->v[3][3] = 1.0;
	return (r);
}

t_matrix
	*ft_mat_roty(double a)
{
	t_matrix	*r;

	if (!(r = (t_matrix*)malloc(sizeof(*r))))
		return (NULL);
	r->v[0][0] = cos(a);
	r->v[0][1] = 0.0;
	r->v[0][2] = sin(a);
	r->v[0][3] = 0.0;
	r->v[1][0] = 0.0;
	r->v[1][1] = 1.0;
	r->v[1][2] = 0.0;
	r->v[1][3] = 0.0;
	r->v[2][0] = -sin(a);
	r->v[2][1] = 0.0;
	r->v[2][2] = cos(a);
	r->v[2][3] = 0.0;
	r->v[3][0] = 0.0;
	r->v[3][1] = 0.0;
	r->v[3][2] = 0.0;
	r->v[3][3] = 1.0;
	return (r);
}

t_matrix
	*ft_mat_rotz(double a)
{
	t_matrix	*r;

	if (!(r = (t_matrix*)malloc(sizeof(*r))))
		return (NULL);
	r->v[0][0] = cos(a);
	r->v[0][1] = -sin(a);
	r->v[0][2] = 0.0;
	r->v[0][3] = 0.0;
	r->v[1][0] = sin(a);
	r->v[1][1] = cos(a);
	r->v[1][2] = 0.0;
	r->v[1][3] = 0.0;
	r->v[2][0] = 0.0;
	r->v[2][1] = 0.0;
	r->v[2][2] = 1.0;
	r->v[2][3] = 0.0;
	r->v[3][0] = 0.0;
	r->v[3][1] = 0.0;
	r->v[3][2] = 0.0;
	r->v[3][3] = 1.0;
	return (r);
}

double
	ft_mat3_det(t_matrix3 *m)
{
	double	r;

	r = m->v[0][0] * (m->v[1][1] * m->v[2][2]
	- m->v[1][2] * m->v[2][1])
	- m->v[0][1] * (m->v[1][0] * m->v[2][2]
	- m->v[1][2] * m->v[2][0])
	+ m->v[0][2] * (m->v[1][0] * m->v[2][1]
	- m->v[1][1] * m->v[2][0]);
	return (r);
}

t_matrix3
	*ft_mat4tomat3(t_matrix *m, int l, int c)
{
	t_matrix3	*r;
	int			i;
	int			j;

	if (!(r = (t_matrix3*)malloc(sizeof(*r))))
		return (NULL);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (i >= l && j >= c)
				r->v[i][j] = m->v[i + 1][j + 1];
			else if (i >= l)
				r->v[i][j] = m->v[i + 1][j];
			else if (j >= c)
				r->v[i][j] = m->v[i][j + 1];
			else
				r->v[i][j] = m->v[i][j];
			j++;
		}
		i++;
	}
	return (r);
}
