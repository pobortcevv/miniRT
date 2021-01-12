/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 06:48:14 by sabra             #+#    #+#             */
/*   Updated: 2021/01/12 21:17:36 by sabra            ###   ########.fr       */
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
	rt->cam.d.x = scale_w * (x - (rt->res.x / 2)) - rt->cam.pos.x;
	rt->cam.d.y = scale_h * (rt->res.y / 2 - y) - rt->cam.pos.y;
	rt->cam.d.z = 1;
}

void	intersect_sp(t_rt *rt, t_elem *sp)
{
	t_xyz oc;
	double k1;
	double k2;
	double k3;

	oc.x = rt->cam.pos.x - sp->pos.x;
	oc.y = rt->cam.pos.y - sp->pos.y;
	oc.z = rt->cam.pos.z - sp->pos.z;
	k1 = ft_dot(&(rt->cam.d), &(rt->cam.d));
	k2 = 2 * ft_dot(&oc, &(rt->cam.d));
	k3 = ft_dot(&oc, &oc) - (sp->r * sp->r);
	rt->t1 = ft_queq(k1, k2, k3, 1);
	rt->t2 = ft_queq(k1, k2, k3, 2);
}

int	ft_color(int r, int g, int b)
{
	int rgb;

	rgb = (r<<0) | (g<<8) | (b<<16);
	return (rgb);
}

void	intersect_init(t_rt *rt, t_elem *elem)
{
	if (elem->id == SPHERE)
		intersect_sp(rt, elem);
}

t_elem	*ft_lstcnt(t_list *list, int index)
{
	int i;
	t_list *lst;
	t_elem *elem;

	lst = list;
	elem = lst->content;
	i = 0;
	while (i != index)
	{
		lst = lst->next;
		elem = lst->content;
		i++;
	}
	return (elem);
}

int	trace_ray(t_rt *rt, float min_t)
{
	float	closest_t;
	int	color;
	t_elem	*closest_elem;
	int	i;

	closest_t = INT_MAX;
	i = 0;
	closest_elem = rt->ob_lst->content;
	while (i < ft_lstsize(rt->ob_lst))
	{
		intersect_init(rt, ft_lstcnt(rt->ob_lst, i));
		if (rt->t1 >= min_t && rt->t1 < closest_t)
		{
			closest_t = rt->t1;
			closest_elem = ft_lstcnt(rt->ob_lst, i);
		}
		if (rt->t2 >= min_t && rt->t2 < closest_t)
		{
			closest_t = rt->t2;
			closest_elem = ft_lstcnt(rt->ob_lst, i);
		}
		i++;
	}
	if (closest_t == INT_MAX)
		return ((0<<16) | (0<<8) | (0<<0));
	color = ft_color(closest_elem->color.r, closest_elem->color.g, closest_elem->color.b);
	return (color);
}

void	render(t_rt *rt)
{
	int x;
	int y;
	int color;

	x = 0;
	while (x < rt->res.x)
	{
		y = 0;
		while (y < rt->res.y)
		{
			to_viewport(x, y, rt);
			color = trace_ray(rt, 0);
			mlx_pixel_put(rt->mlx, rt->mlx_win, x, y, color);
			y++;
		}
		x++;
	}
}



