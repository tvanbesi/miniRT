/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:28:57 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/01 23:23:57 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int
	ft_save(t_scene *scene, char *filename)
{
	if (!ft_parse_file(scene, filename))
		return (0);
	if (!ft_draw_image(scene, 0))
		return (0);
	if (!ft_screenshot(scene, "screenshot.bmp"))
		return (0);
	return (1);
}

static int
	ft_run(t_scene *scene, char *filename)
{
	if (!ft_parse_file(scene, filename))
		return (0);
	if (!ft_draw_all_images(scene))
		return (0);
	mlx_key_hook(scene->screen.window, ft_key_hook, scene);
	mlx_hook(scene->screen.window, 17, 0, ft_close, NULL);
	mlx_loop(scene->screen.mlx);
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
		return (ft_run(&scene, argv[1]));
	else if (argc == 3 && !ft_strncmp(argv[2], "-save", ft_strlen(argv[2])))
		return (ft_save(&scene, argv[1]));
	return (0);
}
