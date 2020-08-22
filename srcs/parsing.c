/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:26:04 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/08/22 19:51:02 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int
	ft_getobjval(char *line)
{
	if (line[0] && line[1])
	{
		if (line[0] == 'R' && ft_isspht(line[1]))
			return(RESOLUTION);
		else if (line[0] == 'A' && ft_isspht(line[1]))
			return(AMBLIGHT);
		else if (line[0] == 'c' && ft_isspht(line[1]))
			return (CAMERA);
		else if (line[0] == 'l' && ft_isspht(line[1]))
			return (LIGHT);
		if (line[3])
		{
			if (line[0] == 'p' && line[1] == 'l' && ft_isspht(line[3]))
				return (PLANE);
			else if (line[0] == 's' && line[1] == 'q' && ft_isspht(line[3]))
				return (SQUARE);
			else if (line[0] == 'c' && line[1] == 'y' && ft_isspht(line[3]))
				return (CYLINDER);
			else if (line[0] == 't' && line[1] == 'r' && ft_isspht(line[3]))
				return (TRIANGLE);
			else if (line[0] == 's' && line[1] == 'p' && ft_isspht(line[3]))
				return (SPHERE);
		}
	}
	return (-1);
}

char
	**ft_splitline(const char *line)
{
	char	**r;

	if (!(r = ft_splits(line, " \t")))
		return (NULL);
	return (r);
}

char
	**ft_splitrgb(const char *s)
{
	char	**r;

	if (!(r = ft_split(s, ',')))
		return (NULL);
	return (r);
}

int
	ft_isvalid_res(char **a)
{
	if (a[1] && a[2] && !a[3])
		return (ft_isvalid_int(a[1]) && ft_isvalid_int(a[2]));
	return (0);
}

int
	ft_isvalid_alight(char **a)
{
	if (a[1] && a[2] && !a[3])
		return (ft_isvalid_db(a[1]) && ft_isvalid_rgb(a[2]));
	return (0);
}
