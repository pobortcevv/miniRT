/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:52:05 by sabra             #+#    #+#             */
/*   Updated: 2021/02/16 13:57:26 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void bmp_render(t_rt *rt, int fd)
{
	int		x;
	int	 	y;
	t_color		color;
	float	**rotation_m;

	x = 0;
	normalize(&rt->cam.ori);
	rotation_m = rotation_matrix(rt->cam.ori);
	cam_to_world(rt, rotation_m, &rt->cam);
	while (x < rt->res.x)
	{
		y = 0;
		while (y < rt->res.y)
		{
			rt->depth = MIRRORING_DEPTH_VALUE;
			to_viewport(x, y, rt);
			color = trace_ray(rt, rt->cam.pos, rt->cam.d, START_RAY);
			write(fd, &ft_color(color.r, color.g, color.b), 3);
			y++;
		}
		x++;
	}
	ft_free_float_mat(rotation_m);
}

static void make_header(t_rt *rt, unsigned char *header, int file_size)
{
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	header[2] = (unsigned char)file_size;
	header[3] = (unsigned char)(file_size >> 8);
	header[4] = (unsigned char)(file_size >> 16);
	header[5] = (unsigned char)(file_size >> 24);
	header[10] = (unsigned char)54; /* The number of bytes between start of the file (0) and the first byte of the pixel data.) */
	header[14] = (unsigned char)40; /* Size of the header in bytes. It should be '40' in decimal to represent BITMAPINFOHEADER header type.'') */
	header[18] = (unsigned char)rt->res.x;
	header[19] = (unsigned char)(rt->res.x >> 8);
	header[20] = (unsigned char)(rt->res.x >> 16);
	header[21] = (unsigned char)(rt->res.x >> 24);
	header[22] = (unsigned char)rt->res.y;
	header[23] = (unsigned char)(rt->res.y >> 8);
	header[24] = (unsigned char)(rt->res.y >> 16);
	header[25] = (unsigned char)(rt->res.y >> 24);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
}

int		create_bmp(t_rt *rt)
{
	unsigned char	header[54];
	int				file_size;
	int				fd;

	ft_bzero(&header, 54);
	if (rt->res.x % 4)
		rt->res.x -= rt->res.x % 4;
	file_size = rt->res.x * rt->res.y + 54;
	if (!(fd = open("miniRT.bmp", O_CREAT | O_WRONLY | O_TRUNC)))
		error_exit(rt, "OPEN FILE ERROR\n");
	make_header(rt, header, file_size);
	write(fd, header, 54);
	bmp_render(rt, fd);
	close(fd);
	normal_exit(rt);
	return (1);
}
