/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:46:08 by sabra             #+#    #+#             */
/*   Updated: 2021/02/01 10:57:31 by sabra            ###   ########.fr       */
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

void	light_color(t_color *res, t_color lgt_color, float light)
{
	res->r += (lgt_color.r / 255) * light;
	//if (lgt_color.r == 0)
		//res->r += light;
	res->g += (lgt_color.g / 255) * light;
	//if (lgt_color.g == 0)
		//res->g += light;
	res->b += (lgt_color.b / 255) * light;
	//if (lgt_color.b == 0)
		//res->b += light;
}

int	ft_color(int r, int g, int b)
{
	int rgb;

	rgb = (b<<16) | (g<<8) | (r<<0);
	return (rgb);
}
