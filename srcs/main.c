/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:28:57 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/08/22 16:40:44 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int
	ft_close(void)
{
	exit(0);
}

int
	main(void)
{
	void		*mlx;
	void		*window;
	t_screen	screen;
	t_scene		scene;
	int			white = ft_getcolor(&(t_color){255, 255, 255});
	int			red = ft_getcolor(&(t_color){255, 0, 0});
	int			green = ft_getcolor(&(t_color){0, 255, 0});
	int			blue = ft_getcolor(&(t_color){0, 0, 255});
	int			magenta = ft_getcolor(&(t_color){255, 0, 255});

	char	*line;
	int		fd;
	int		gnl;
	char	**split;

	// INITIALISE SCREEN WIDTH AND HEIGHT TO 0 FOR ERROR HANDLING

	fd = open("scene1.rt", O_RDONLY);
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		printf("\n-----%s-----\n", line);
		split = ft_splits(line, "\t\n\v\f\r ");
		while(*split)
		{
			printf("|%s|", *split);
			split++;
		}
	}
	if (gnl == -1)
		printf("ERROR\n");

	screen.mlx = mlx_init();
	screen.window = mlx_new_window(screen.mlx, 1000, 1000, "miniRT");

	screen.width = 1000;
	screen.height = 1000;
	screen.aspect_ratio = (double)screen.width / (double)screen.height;
	screen.tfov2 = tan(90.0 / 2.0 * M_PI / 180);

	scene.objects[0] = ft_mkplane((t_coords){0.0, 0.0, 1000.0}, (t_coords){0.0, 0.0, 0.0}, white);
	scene.objects[1] = ft_mksphere((t_coords){200.0, 0.0, 400.0}, 100.0, blue);
	scene.objects[2] = ft_mksphere((t_coords){0.0, 0.0, 400.0}, 100.0, green);
	scene.objects[3] = ft_mksquare((t_coords){0.0, 200.0, 400.0}, (t_coords){0.0, 0.250, 0.0}, 200.0, red);
	t_coords	*v;
	v = malloc(sizeof(t_coords) * 3);
	v[0] = (t_coords){-400.0, 0.0, 500.0};
	v[1] = (t_coords){-200.0, 0.0, 500.0};
	v[2] = (t_coords){-300.0, 100.0, 500.0};
	scene.objects[4] = ft_mktriangle(v, green);
	scene.objects[5] = ft_mkcylinder((t_coords){-200.0, -100.0, 600.0}, (t_coords){0.4, 0.0, 0.0}, 200.0, 100.0, magenta);
	scene.obj_count = 6;

	scene.cameras[0] = ft_mkcamera((t_coords){0.0, 0.0, 0.0}, (t_coords){0.1, 0.0, 0.0});
	scene.camselect = 0;
	scene.cam_count = 1;

	scene.ctw_matrix = ft_mat_rot(&scene.cameras[scene.camselect].ori);

	scene.amblight = ft_mklight((t_coords){0.0, 0.0, 0.0}, white, 0.1); 
	scene.lights[0] = ft_mklight((t_coords){0.0, 200.0, 200.0}, white, 0.4);
	scene.lights[1] = ft_mklight((t_coords){-100.0, 200.0, 200.0}, white, 0.4);
	scene.light_count = 2;
	
	// if (!(ft_ray_tracer(&screen, &scene)))
	// 	printf("ERROR\n");
	// mlx_hook(screen.window, 17, 0, ft_close, NULL);
	// mlx_loop(screen.mlx);
	return (0);
}
