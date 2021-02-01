/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:47:54 by sabra             #+#    #+#             */
/*   Updated: 2021/02/01 10:50:05 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	c_multi_colors(t_color c1, t_color c2)
{
	t_color res;

	if ((res.r = c1.r * c2.r) > 255)
		res.r = 255;
	if ((res.g = c1.g * c2.g) > 255)
		res.g = 255;
	if ((res.b = c1.b * c2.b) > 255)
		res.b = 255;
	return (res);
}

int	c_isnull(t_color c)
{
	return (c.r == 0 && c.g == 0 && c.b == 0);
}

int	check_color_parse(t_color c)
{
	if (c.r < 0 || c.g < 0 || c.b < 0)
		return (0);
	return (1);
}
