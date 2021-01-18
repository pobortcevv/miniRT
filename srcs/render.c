/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 06:48:14 by sabra             #+#    #+#             */
/*   Updated: 2021/01/18 12:56:21 by sabra            ###   ########.fr       */
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

t_xyz	v_new(t_xyz v1, t_xyz v2)
{
	t_xyz	v_res;

	v_res.x = v1.x - v2.x;
	v_res.y = v1.y - v2.y;
	v_res.z = v1.z - v2.z;
	return (v_res);
}

t_xyz	v_multi(t_xyz v, float n)
{
	t_xyz	v_res;

	v_res.x = v.x * n;
	v_res.y = v.y * n;
	v_res.z = v.z * n;
	return (v_res);
}

void	intersect_sp(t_rt *rt, t_elem *sp)
{
	t_xyz	oc;
	float	k1;
	float	k2;
	float	k3;

	oc = v_new(rt->cam.pos, sp->pos);
	k1 = ft_dot(&(rt->cam.d), &(rt->cam.d));
	k2 = 2 * ft_dot(&oc, &(rt->cam.d));
	k3 = ft_dot(&oc, &oc) - (sp->r * sp->r);
	rt->t1 = ft_queq(k1, k2, k3, 1);
	rt->t2 = ft_queq(k1, k2, k3, 2);
}

void	intersect_pl(t_rt *rt, t_elem *pl)
{
	t_xyz	co;
	float	k1;
	float	k2;

	co = v_new(pl->pos, rt->cam.pos);
	k1 = ft_dot(&(pl->ori), &co);
	if (!(k2 = ft_dot(&(pl->ori), &(rt->cam.d))))
		rt->t1 = INT_MAX;
	else
		rt->t1 = (k1 / k2);
	rt->t2 = INT_MAX;
}

int	intersect_sq(t_rt *rt, t_elem *sq)
{
	t_xyz	co;
	t_xyz	hit;
	float	k1;
	float	k2;

	co = v_new(sq->pos, rt->cam.pos);
	k1 = ft_dot(&(sq->ori), &co);
	rt->t2 = INT_MAX;
	if (!(k2 = ft_dot(&rt->cam.d, &sq->ori)))
	{
		rt->t1 = INT_MAX;
		return (0);
	}
	rt->t1 = (k1 / k2);
	hit = v_new(rt->cam.pos, v_multi(rt->cam.d, rt->t1));
	if (fabs(hit.x - sq->pos.x) <= (sq->len / 2) &&
			fabs(hit.y - sq->pos.y) <= (sq->len / 2) &&
			fabs(hit.z - sq->pos.z) <= (sq->len / 2))
		return (1);
	else
		rt->t1 = INT_MAX;
	return (0);
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
	else if(elem->id == PLANE)
		intersect_pl(rt, elem);
	else if(elem->id == SQUARE)
		intersect_sq(rt, elem);

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



