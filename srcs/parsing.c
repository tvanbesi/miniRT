/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:26:04 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/01 18:56:22 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int
	ft_parse_file(t_scene *scene, char *filename)
{
	int		fd;
	int		gnl;
	char	*line;

	fd = open(filename, O_RDONLY);
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		if (!ft_parse_line(line, scene) && ft_strncmp(line, "", 1))
			return (0);
		free(line);
	}
	if (gnl == -1)
		return (0);
	return (1);
}

int
	ft_getobjtype(char *line)
{
	if (line[0] && line[1])
	{
		if (line[0] == 'R' && ft_isspht(line[1]))
			return (RESOLUTION);
		else if (line[0] == 'A' && ft_isspht(line[1]))
			return (AMBLIGHT);
		else if (line[0] == 'c' && ft_isspht(line[1]))
			return (CAMERA);
		else if (line[0] == 'l' && ft_isspht(line[1]))
			return (LIGHT);
		else if (line[2])
		{
			if (line[0] == 'p' && line[1] == 'l' && ft_isspht(line[2]))
				return (PLANE);
			else if (line[0] == 's' && line[1] == 'q' && ft_isspht(line[2]))
				return (SQUARE);
			else if (line[0] == 'c' && line[1] == 'y' && ft_isspht(line[2]))
				return (CYLINDER);
			else if (line[0] == 't' && line[1] == 'r' && ft_isspht(line[2]))
				return (TRIANGLE);
			else if (line[0] == 's' && line[1] == 'p' && ft_isspht(line[2]))
				return (SPHERE);
		}
	}
	return (-1);
}

int
	ft_isvalid_splitline(int objtype, char **a)
{
	if (objtype == RESOLUTION)
		return (ft_isvalid_res(a));
	else if (objtype == AMBLIGHT)
		return (ft_isvalid_alight(a));
	else if (objtype == CAMERA)
		return (ft_isvalid_cam(a));
	else if (objtype == LIGHT)
		return (ft_isvalid_light(a));
	else if (objtype == PLANE)
		return (ft_isvalid_plane(a));
	else if (objtype == SQUARE)
		return (ft_isvalid_square(a));
	else if (objtype == CYLINDER)
		return (ft_isvalid_cyl(a));
	else if (objtype == TRIANGLE)
		return (ft_isvalid_triangle(a));
	else if (objtype == SPHERE)
		return (ft_isvalid_sphere(a));
	return (0);
}

static void
	ft_parse_line_obj(int *r, int objtype, char **splitline, t_scene *scene)
{
	if (objtype == RESOLUTION)
		*r = ft_parse_res(splitline, scene);
	else if (objtype == AMBLIGHT)
		*r = ft_parse_amblight(splitline, scene);
	else if (objtype == CAMERA)
		*r = ft_parse_cam(splitline, scene);
	else if (objtype == LIGHT)
		*r = ft_parse_light(splitline, scene);
	else if (objtype == PLANE)
		*r = ft_parse_plane(splitline, scene);
	else if (objtype == SQUARE)
		*r = ft_parse_square(splitline, scene);
	else if (objtype == CYLINDER)
		*r = ft_parse_cylinder(splitline, scene);
	else if (objtype == TRIANGLE)
		*r = ft_parse_triangle(splitline, scene);
	else if (objtype == SPHERE)
		*r = ft_parse_sphere(splitline, scene);
}

int
	ft_parse_line(char *line, t_scene *scene)
{
	int		r;
	int		objtype;
	char	**splitline;

	if ((objtype = ft_getobjtype(line)) == -1)
		return (0);
	splitline = ft_splits(line, " \t");
	r = 0;
	if (ft_isvalid_splitline(objtype, splitline))
		ft_parse_line_obj(&r, objtype, splitline, scene);
	ft_splitf(splitline);
	return (r);
}
