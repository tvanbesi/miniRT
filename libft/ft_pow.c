/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:39:18 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/09/02 21:45:33 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double
	ft_pow(double x, int y)
{
	double	r;

	if (x == 0.0)
		return (x);
	r = 1.0;
	if (y > 0)
		while (y-- > 0)
			r *= x;
	else
		while (y++ < 0)
			r /= x;
	return (r);
}
