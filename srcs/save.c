/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 17:05:58 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/08/29 15:42:42 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void
	ft_write_header(int fd, t_screen *screen)
{
	ft_putstr_fd("BM", fd);
	ft_putint_fd(54 + 3 * screen->width * screen->height + ((4 - (screen->width * 3) % 4) % 4) * screen->height, fd);
	ft_putint_fd(0, fd);
	ft_putchar_fd(54, fd);
	ft_putchar_fd(0, fd);
	ft_putchar_fd(0, fd);
	ft_putchar_fd(0, fd);
}

static void
	ft_write_info(int fd, t_screen *screen)
{
	ft_putchar_fd(40, fd);
	ft_putchar_fd(0, fd);
	ft_putchar_fd(0, fd);
	ft_putchar_fd(0, fd);
	ft_putint_fd(screen->width, fd);
	ft_putint_fd(screen->height, fd);
	ft_putchar_fd(1, fd);
	ft_putchar_fd(0, fd);
	ft_putchar_fd(24, fd);
	ft_putchar_fd(0, fd);
	ft_putint_fd(0, fd);
	ft_putint_fd(0, fd);
	ft_putint_fd(0, fd);
	ft_putint_fd(0, fd);
	ft_putint_fd(0, fd);
	ft_putint_fd(0, fd);
}

static void
	ft_write_pmap(int fd, t_screen *screen, t_image *img) 
{
	int				x;
	int				y;
	unsigned char	*p;

	y = screen->height;
	p = img->data_addr + (screen->height - 1) * img->size_line;
	while (y-- > 0)
	{
		x = screen->width;
		while (x-- > 0)
		{
			ft_putchar_fd((char)*p++, fd);
			ft_putchar_fd((char)*p++, fd);
			ft_putchar_fd((char)*p++, fd);
			p++;
		}
		p -= img->size_line * 2;
		x = (4 - (screen->width * 3) % 4) % 4;
		while (x-- > 0)
			ft_putchar_fd(0, fd);
	}
}

int
	ft_screenshot(t_scene *scene, char *filename)
{
	int	fd;

	if ((fd = open(filename, O_WRONLY | O_CREAT)) < 0)
		return (0);
	ft_write_header(fd, &scene->screen);
	ft_write_info(fd, &scene->screen);
	ft_write_pmap(fd, &scene->screen, &scene->images[scene->camselect]);
	close(fd);
	return (1);
}