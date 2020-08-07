/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:26:04 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/08/06 15:31:32 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int
	ft_findobjtoparse(char *line)
{
	while (ft_isspace(*line))
		line++;
	if (!*line)
		return (-1);
	if (line[0] == 'R' && ft_isspace(line[1]))
		return(RESOLUTION);
	else if (line[0] == 'A' && ft_isspace(line[1]))
		return(AMBLIGHT);
	else if (line[0] == 'c' && ft_isspace(line[1]))
		return (CAMERA);
	else if (line[0] == 'l' && ft_isspace(line[1]))
		return (LIGHT);
	else if (line[0] == 'p' && line[1] == 'l')
		return (PLANE);
	else if (line[0] == 's' && line[1] == 'q')
		return (SQUARE);
	else if (line[0] == 'c' && line[1] == 'y')
		return (CYLINDER);
	else if (line[0] == 't' && line[1] == 'r')
		return (TRIANGLE);
	else if (line[0] == 's' && line[1] == 'p')
		return (SPHERE);
	return (-1);
}
