/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:28:57 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/08/29 15:25:42 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int
	ft_close(void)
{
	exit(0);
}

int
	ft_key_hook(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene*)param;
	if (keycode == 49)
	{
		mlx_put_image_to_window(scene->screen.mlx, scene->screen.window, scene->images[scene->camselect].ptr, 0, 0);
		scene->camselect++;
		if (scene->camselect >= scene->cam_count)
			scene->camselect = 0;
	}
	if (keycode == 53)
	{
		ft_clear_images(scene);
		mlx_destroy_window(scene->screen.mlx, scene->screen.window);
		ft_close();
	}
	return (0);
}

static int
	ft_draw_all_images(t_scene *scene)
{
	int i;

	i = 0;
	while (i++ < scene->cam_count)
	{
		ft_selectcam(scene, i - 1);
		scene->images[scene->camselect] = ft_mkimage(&scene->screen);
		if (!ft_ray_tracer(&scene->screen, scene, scene->images[scene->camselect].data_addr))
			return (0);
	}
	return (1);
}

int
	main(int argc, char **argv)
{
	t_scene		scene;
	char		*line;
	int			fd;
	int			gnl;

	ft_mkscene(&scene);
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((gnl = get_next_line(fd, &line)) == 1)
		{
			if (!ft_parse_line(line, &scene) && ft_strncmp(line, "", 1))
				return (0);
			free(line);
		}
		if (gnl == -1)
			return (0);
		if (!ft_draw_all_images(&scene))
			return (0);
		mlx_key_hook(scene.screen.window, ft_key_hook, &scene);
		mlx_hook(scene.screen.window, 17, 0, ft_close, NULL);
		mlx_loop(scene.screen.mlx);
	}
	else if (argc == 3 && !ft_strncmp(argv[2], "-save", ft_strlen(argv[2])))
	{
		fd = open(argv[1], O_RDONLY);
		while ((gnl = get_next_line(fd, &line)) == 1)
		{
			if (!ft_parse_line(line, &scene) && ft_strncmp(line, "", 1))
				return (0);
			free(line);
		}
		if (gnl == -1)
			return (0);
		ft_selectcam(&scene, 0);
		scene.images[scene.camselect] = ft_mkimage(&scene.screen);
		if (!ft_ray_tracer(&scene.screen, &scene, scene.images[scene.camselect].data_addr))
			return (0);
		if (!ft_screenshot(&scene, "test.bmp"))
			return (0);
	}
	return (0);
}
