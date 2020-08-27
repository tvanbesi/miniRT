/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sanity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 14:26:19 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/08/25 15:22:11 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int
    ft_isvvalid_rgb(t_color color)
{
    return (color.r >= 0 && color.r <= 255
            && color.g >= 0 && color.g <= 255
            && color.b >= 0 && color.b <= 255);
}

int
    ft_isvvalid_ori(t_coords ori)
{
    return (ori.x >= -1.0 && ori.x <= 1.0
            && ori.y >= -1.0 && ori.y <= 1.0
            && ori.z >= -1.0 && ori.z <= 1.0);
}

int
    ft_isvvalid_lum(double lum)
{
    return (lum >= 0.0 && lum <= 1.0);
}

int
	ft_isvalid_fov(int fov)
{
	return (fov > 0 && fov <= 180);
}