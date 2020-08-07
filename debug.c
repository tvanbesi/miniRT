/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 01:15:58 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/08/03 21:11:57 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void
	ft_print_coords(t_coords c)
{
	printf("x:\t%f\ty:\t%f\tz:\t%f\n", c.x, c.y, c.z);
}

void
	ft_print_matrix(t_matrix *matrix)
{
	for (int k = 0; k < 4; k++)
	{
		for (int l = 0; l < 4; l++)
		{
			printf("%.3f\t", matrix->v[k][l]);
		}
		printf("\n");
	}
	printf("\n");
}

void
	ft_print_matrix3(t_matrix3 *m)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			printf("%.3f\t", m->v[i][j]);
		printf("\n");
	}
	printf("\n");
}

void
	ft_print_coordscp(t_coords_cp c)
{
	printf("r:\t%f\tt:\t%f\tz:\t%f\n", c.r, c.t, c.z);
}
