/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 23:33:56 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/03/11 01:05:37 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_matrix
	*ft_mat_mlt(t_matrix *m1, t_matrix *m2)
{
	t_matrix	*r;
	int			i;
	int			j;

	if (!(r = (t_matrix*)malloc(sizeof(*r))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			r->v[i][j] = m1->v[i][0] * m2->v[0][j]
			+ m1->v[i][1] * m2->v[1][j]
			+ m1->v[i][2] * m2->v[2][j]
			+ m1->v[i][3] * m2->v[3][j];
			j++;
		}
		i++;
		j = 0;
	}
	return (r);
}

t_matrix
	*ft_mat_trans(t_coords *c)
{
	t_matrix	*r;

	if (!(r = (t_matrix*)malloc(sizeof(*r))))
		return (NULL);
	r->v[0][0] = 1.0;
	r->v[0][1] = 0.0;
	r->v[0][2] = 0.0;
	r->v[0][3] = c->x;
	r->v[1][0] = 0.0;
	r->v[1][1] = 1.0;
	r->v[1][2] = 0.0;
	r->v[1][3] = c->y;
	r->v[2][0] = 0.0;
	r->v[2][1] = 0.0;
	r->v[2][2] = 1.0;
	r->v[2][3] = c->z;
	r->v[3][0] = 0.0;
	r->v[3][1] = 0.0;
	r->v[3][2] = 0.0;
	r->v[3][3] = 1.0;
	return (r);
}

t_matrix
	*ft_mat_scal(t_coords *c)
{
	t_matrix	*r;

	if (!(r = (t_matrix*)malloc(sizeof(*r))))
		return (NULL);
	r->v[0][0] = c->x;
	r->v[1][0] = 0.0;
	r->v[2][0] = 0.0;
	r->v[3][0] = 0.0;
	r->v[0][1] = 0.0;
	r->v[1][1] = c->y;
	r->v[2][1] = 0.0;
	r->v[3][1] = 0.0;
	r->v[0][2] = 0.0;
	r->v[1][2] = 0.0;
	r->v[2][2] = c->z;
	r->v[3][2] = 0.0;
	r->v[0][3] = 0.0;
	r->v[1][3] = 0.0;
	r->v[2][3] = 0.0;
	r->v[3][3] = 1.0;
	return (r);
}

t_matrix
	*ft_mat_rot(t_coords *c)
{
	t_matrix	*mx;
	t_matrix	*my;
	t_matrix	*mz;
	t_matrix	*r;

	if (!(mx = ft_mat_rotx(c->x * M_PI)))
		return (NULL);
	if (!(my = ft_mat_roty(c->y * M_PI)))
	{
		free(mx);
		return (NULL);
	}
	if (!(mz = ft_mat_rotz(c->z * M_PI)))
	{
		free(mx);
		free(my);
		return (NULL);
	}
	if (!(r = ft_mat_mlt(ft_mat_mlt(mx, my), mz)))
	{
		free(mx);
		free(my);
		free(mz);
		return (NULL);
	}
	free(mx);
	free(my);
	free(mz);
	return (r);
}

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
	ft_mat_det(t_matrix *m)
{
	double	r;

	r = m->v[0][0] * (m->v[1][1] * m->v[2][2] * m->v[3][3]
	+ m->v[1][2] * m->v[2][3] * m->v[3][1]
	+ m->v[1][3] * m->v[2][1] * m->v[3][2]
	- m->v[1][3] * m->v[2][2] * m->v[3][1]
	- m->v[1][2] * m->v[2][1] * m->v[3][3]
	- m->v[1][1] * m->v[2][3] * m->v[3][2])
	- m->v[1][0] * (m->v[0][1] * m->v[2][2] * m->v[3][3]
	+ m->v[0][2] * m->v[2][3] * m->v[3][1]
	+ m->v[0][3] * m->v[2][1] * m->v[3][2]
	- m->v[0][3] * m->v[2][2] * m->v[3][1]
	- m->v[0][2] * m->v[2][1] * m->v[3][3]
	- m->v[0][1] * m->v[2][3] * m->v[3][2])
	+ m->v[2][0] * (m->v[0][1] * m->v[1][2] * m->v[3][3]
	+ m->v[0][2] * m->v[1][3] * m->v[3][1]
	+ m->v[0][3] * m->v[1][1] * m->v[3][2]
	- m->v[0][3] * m->v[1][2] * m->v[3][1]
	- m->v[0][2] * m->v[1][1] * m->v[3][3]
	- m->v[0][1] * m->v[1][3] * m->v[3][2])
	- m->v[3][0] * (m->v[0][1] * m->v[1][2] * m->v[2][3]
	+ m->v[0][2] * m->v[1][3] * m->v[2][1]
	+ m->v[0][3] * m->v[1][1] * m->v[2][2]
	- m->v[0][3] * m->v[1][2] * m->v[2][1]
	- m->v[0][2] * m->v[1][1] * m->v[2][3]
	- m->v[0][1] * m->v[1][3] * m->v[2][2]);
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
