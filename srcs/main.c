/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:28:57 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/04 15:49:33 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int
	ft_save(t_scene *scene, char *filename)
{
	if (!ft_parse_file(scene, filename))
		return (0);
	if (!ft_draw_image(scene, 0))
		return (0);
	if (!ft_screenshot(scene, "screenshot.bmp"))
		return (0);
	ft_close(scene);
	return (1);
}

static int
	ft_run(t_scene *scene, char *filename)
{
	int	size_filename;

	size_filename = ft_strlen(filename);
	if (size_filename <= 3)
		return (0);
	if (filename[size_filename - 3] != '.'
	|| filename[size_filename - 2] != 'r'
	|| filename[size_filename - 1] != 't')
		return (0);
	if (!ft_parse_file(scene, filename))
		return (0);
	if (!ft_draw_all_images(scene))
		return (0);
	ft_key_hook(32, (void*)scene);
	mlx_key_hook(scene->screen.window, ft_key_hook, scene);
	mlx_hook(scene->screen.window, 17, 0, ft_close, scene);
	mlx_loop(scene->screen.mlx);
	return (1);
}

int
	main(int argc, char **argv)
{
	t_scene		scene;

	ft_mkscene(&scene);
	if (argc == 2)
	{
		if (!ft_run(&scene, argv[1]))
			ft_close(&scene);
	}
	else if (argc == 3 && !ft_strncmp(argv[2], "-save", ft_strlen(argv[2])))
		if (!ft_save(&scene, argv[1]))
			ft_close(&scene);
	return (0);
}
