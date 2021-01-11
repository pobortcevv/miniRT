/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 06:48:14 by sabra             #+#    #+#             */
/*   Updated: 2021/01/11 22:34:17 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	to_viewport(int x, int y, t_rt *rt)
{
	float	scale_w;
	float	scale_h;
	float	vw;
	float	vh;

	vw = 2 * tan(rt->cam.fov / 2);
	vh = 2 * tan(rt->cam.fov / 2);
	scale_w = vw / rt->res.x; 
	scale_h = vh / rt->res.y; 
	rt->cam.d.x = (vw / scale_w * (x - (rt->res.x / 2))) - rt->cam.pos.x;
	rt->cam.d.y = (vh / scale_h * (y + (rt->res.y / 2))) - rt->cam.pos.y;
	rt->cam.d.z = 1;
}

void	intersect_sp(t_rt *rt)
{
	t_xyz oc;
	double k1;
	double k2;
	double k3;

	oc.x = rt->cam.pos.x - rt->sp.pos.x;
	oc.y = rt->cam.pos.y - rt->sp.pos.y;
	oc.z = rt->cam.pos.z - rt->sp.pos.z;
	k1 = ft_dot(&(rt->cam.d), &(rt->cam.d));
	k2 = 2 * ft_dot(&oc, &(rt->cam.d));
	k3 = ft_dot(&oc, &oc) - (rt->sp.r * rt->sp.r);
	rt->t1 = ft_queq(k1, k2, k3, 1);
	rt->t2 = ft_queq(k1, k2, k3, 2);
}

int	ft_color(int r, int g, int b)
{
	int rgb;

	rgb = (r<<0) | (g<<8) | (b<<16);
	return (rgb);
}

int	trace_ray(t_rt *rt, int min_t, int max_t)
{
	int	closest_t;
	int	color;
	t_sp	closest_sp;
	int	sp_id;

	closest_t = INT_MAX;
	sp_id = 0;
	ft_bzero(&closest_sp, sizeof(t_sp));
	/* * Здесь должен быть цикл для всех сфер/фигур
	 * * в сцене.
	 * */
	intersect_sp(rt);
	if (rt->t1 >= min_t && rt->t1 <= max_t && rt->t1 < closest_t)
	{
		closest_t = rt->t1;
		closest_sp = rt->sp;
		sp_id = 1;
	}
	if (rt->t2 >= min_t && rt->t2 <= max_t && rt->t2 < closest_t)
	{
		closest_t = rt->t2;
		closest_sp = rt->sp;
		sp_id = 1;
	}
	if (sp_id == 0)
		return ((0<<16) | (0<<8) | (0<<0));
	color = ft_color(closest_sp.color.r, closest_sp.color.g, closest_sp.color.b);
	return (color);
}

int	ft_iabs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	render(t_rt *rt)
{
	int x;
	int y;
	int color;

	x = 0;
	y = 0;
	while (x < rt->res.x)
	{
		while (y < rt->res.y)
		{
			to_viewport(x, y, rt);
			color = trace_ray(rt, 0, INT_MAX);
			mlx_pixel_put(rt->mlx, rt->mlx_win, x, y, color);
			y++;
		}
		x++;
	}
}



