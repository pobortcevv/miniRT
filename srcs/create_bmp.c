/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:52:05 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 15:34:03 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void		bmp_render(t_rt *rt, int fd)
{
	int				x;
	int				y;
	t_color			color;
	unsigned int	res;
	float			**rotation_m;

	y = rt->res.y;
	rt->cam = *ft_lstcam(rt->cmr_lst, 0);
	rotation_m = rotation_matrix(rt->cam.ori);
	cam_to_world(rt, rotation_m, &rt->cam);
	while (y >= 0)
	{
		x = 0;
		while (x < rt->res.x)
		{
			rt->depth = MIRRORING_DEPTH_VALUE;
			to_viewport(x, y, rt);
			color = trace_ray(rt, rt->cam.pos, rt->cam.d, START_RAY);
			res = ft_color(color.r, color.g, color.b);
			write(fd, &res, 3);
			x++;
		}
		y--;
	}
	ft_free_float_mat(rotation_m);
}

static void	make_header(t_rt *rt, unsigned char *header, size_t file_size)
{
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	header[2] = (unsigned char)file_size;
	header[3] = (unsigned char)(file_size >> 8);
	header[4] = (unsigned char)(file_size >> 16);
	header[5] = (unsigned char)(file_size >> 24);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
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

int			create_bmp(t_rt *rt)
{
	unsigned char	header[54];
	size_t			file_size;
	int				fd;

	ft_bzero(&header, 54);
	file_size = rt->res.x * rt->res.y + 54;
	if (!(fd = open("miniRT.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)))
		error_exit(rt, "OPEN FILE ERROR\n");
	make_header(rt, header, file_size);
	write(fd, header, 54);
	normalize(&rt->cam.ori);
	bmp_render(rt, fd);
	close(fd);
	exit(0);
	return (1);
}
