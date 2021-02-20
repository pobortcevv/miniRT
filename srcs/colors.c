/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:11:44 by sabra             #+#    #+#             */
/*   Updated: 2021/02/20 11:11:46 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	c_plus(t_color c1, t_color c2)
{
	t_color res;

	if ((res.r = c1.r + c2.r) > 255)
		res.r = 255;
	if ((res.g = c1.g + c2.g) > 255)
		res.g = 255;
	if ((res.b = c1.b + c2.b) > 255)
		res.b = 255;
	return (res);
}

t_color	c_multi(t_color c, float n)
{
	t_color res;

	if ((res.r = c.r * n) > 255)
		res.r = 255;
	if ((res.g = c.g * n) > 255)
		res.g = 255;
	if ((res.b = c.b * n) > 255)
		res.b = 255;
	return (res);
}

t_color	c_null(void)
{
	t_color	res;

	res.r = 0;
	res.g = 0;
	res.b = 0;
	return (res);
}

void	color_light(t_color *res, float light)
{
	res->r *= light;
	res->g *= light;
	res->b *= light;
}

int		ft_color(int r, int g, int b)
{
	int	rgb;

	rgb = (b << 16) | (g << 8) | (r << 0);
	return (rgb);
}
