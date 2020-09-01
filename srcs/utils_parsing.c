/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 15:41:05 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/09/01 23:22:24 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int
	ft_parse_color(t_color *color, const char *s)
{
	char	**rgb;

	if (!(rgb = ft_split(s, ',')))
		return (0);
	*color = (t_color){ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2])};
	ft_splitf(rgb);
	return (ft_isvvalid_rgb(*color));
}

int
	ft_parse_coords(t_coords *c, const char *s, int ctype)
{
	char	**split;

	if (!(split = ft_split(s, ',')))
		return (0);
	*c = (t_coords){ft_atof(split[0]), ft_atof(split[1]), ft_atof(split[2])};
	ft_splitf(split);
	if (ctype == ORI)
		return (ft_isvvalid_ori(*c));
	return (1);
}
