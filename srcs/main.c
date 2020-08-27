/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:28:57 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/08/27 17:58:20 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int
	main(int argc, char **argv)
{
	t_scene		scene;
	char		*line;
	int			fd;
	int			gnl;

	ft_mkscene(&scene);
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		if (!ft_parse_line(line, &scene) && ft_strncmp(line, "", ft_strlen(line)))
			return (0);
		free(line);
	}
	if (gnl == -1)
		return (0);
	ft_selectcam(&scene, 0);
	if (!(ft_ray_tracer(&scene.screen, &scene)))
		return (0);
	mlx_loop(scene.screen.mlx);
	return (0);
}
