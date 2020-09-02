/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 23:33:56 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/02 22:28:35 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
