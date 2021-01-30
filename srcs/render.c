/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 06:48:14 by sabra             #+#    #+#             */
/*   Updated: 2021/01/29 13:00:59 by sabra            ###   ########.fr       */
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
	scale_w = vw / rt->res.y; 
	scale_h = vh / rt->res.y; 
	rt->cam.d.x = scale_w * (x - (rt->res.x / 2)) - rt->cam.pos.x;
	rt->cam.d.y = scale_h * (rt->res.y / 2 - y) - rt->cam.pos.y;
	rt->cam.d.z = 1;
	normalize(&rt->cam.d);
}

void	intersect_sp(t_rt *rt, t_elem *sp, t_xyz start, t_xyz finish)
{
	t_xyz	oc;
	float	k1;
	float	k2;
	float	k3;

	oc = v_new(start, sp->pos);
	k1 = ft_dot(&finish, &finish);
	k2 = 2 * ft_dot(&oc, &finish);
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
	normalize(&pl->ori);
	k1 = ft_dot(&(pl->ori), &co);
	if (!(k2 = ft_dot(&(pl->ori), &(rt->cam.d))))
		rt->t1 = INT_MAX;
	else
		rt->t1 = (k1 / k2);
	rt->t2 = INT_MAX;
}
//
//int	intersect_sq(t_rt *rt, t_elem *sq)
//{
	//t_xyz	co;
	//t_xyz	hit;
	//float	k1;
	//float	k2;
//
	//co = v_new(sq->pos, rt->cam.pos);
	//normalize(&sq->ori);
	//k1 = ft_dot(&(sq->ori), &co);
	//rt->t2 = INT_MAX;
	//if (!(k2 = ft_dot(&rt->cam.d, &sq->ori)))
	//{
		//rt->t1 = INT_MAX;
		//return (0);
	//}
	//rt->t1 = (k1 / k2);
	//hit = v_new(rt->cam.pos, v_multi(rt->cam.d, rt->t1));
	//if (fabs(hit.x - sq->pos.x) <= (sq->len / 2) &&
			//fabs(hit.y - sq->pos.y) <= (sq->len / 2) &&
			//fabs(hit.z - sq->pos.z) <= (sq->len / 2))
		//return (1);
	//else
		//rt->t1 = INT_MAX;
	//return (0);
//}
//
//int	check_tr(t_rt *rt, t_xyz hit, t_elem *tr)
//{
	//t_xyz	edge;
	//t_xyz	tr_hit;
	//t_xyz	h_cross;
//
	//tr_hit = v_new(hit, tr->a);
	//edge = v_new(tr->b, tr->a);
	//h_cross = cross(edge, tr_hit);
	//if (ft_dot(&tr->ori, &h_cross) < 0)
		//rt->t1 = INT_MAX;
	//tr_hit = v_new(hit, tr->b);
	//edge = v_new(tr->c, tr->b);
	//h_cross = cross(edge, tr_hit);
	//if (ft_dot(&tr->ori, &h_cross) < 0)
		//rt->t1 = INT_MAX;
	//tr_hit = v_new(hit, tr->c);
	//edge = v_new(tr->a, tr->c);
	//h_cross = cross(edge, tr_hit);
	//if (ft_dot(&tr->ori, &h_cross) < 0)
		//rt->t1 = INT_MAX;
	//return (1);
//}
//
//int	intersect_tr(t_rt *rt, t_elem *tr)
//{
	//float k1;
	//float k2;
	//t_xyz ac;
	//t_xyz hit;
//
	//tr->ori = cross(v_new(tr->b, tr->a), v_new(tr->c, tr->a));
	//normalize(&tr->ori);
	//rt->t2 = INT_MAX;
	//ac = v_new(rt->cam.pos, tr->a);
	//k1 = ft_dot(&tr->ori, &ac);
	//if (!(k2 = ft_dot(&tr->ori, &rt->cam.d)))
	//{
		//rt->t1 = INT_MAX;
		//return (0);
	//}
	//rt->t1 = k1 / k2;
	//hit = v_new(rt->cam.pos, v_multi(rt->cam.d, rt->t1));
	//return (check_tr(rt, hit, tr));
//}

int	ft_color(int r, int g, int b)
{
	int rgb;

	rgb = (b<<16) | (g<<8) | (r<<0);
	return (rgb);
}

void	intersect_init(t_rt *rt, t_elem *elem, t_xyz start, t_xyz finish)
{
	if (elem->id == SPHERE)
		intersect_sp(rt, elem, start, finish);
	else if(elem->id == PLANE)
		intersect_pl(rt, elem);
	//else if(elem->id == SQUARE)
		//intersect_sq(rt, elem);
	//else if(elem->id == TRIANGLE)
		//intersect_tr(rt, elem);

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

t_lgt	*ft_lstlgt(t_list *list, int index)
{
	int 	i;
	t_list 	*lst;
	t_lgt 	*lgt;

	lst = list;
	lgt = lst->content;
	i = 0;
	while (i != index)
	{
		lst = lst->next;
		lgt = lst->content;
		i++;
	}
	return (lgt);
}

t_xyz	reflect_ray(t_xyz r, t_xyz norm)
{
	return (v_new(r, v_multi(norm, 2 * ft_dot(&norm, &r))));
}

float	shadow_intersect(t_rt *rt, t_elem *cl_elem)
{
	float	closest_t;
	int		i;

	closest_t = INT_MAX;
	i = 0;
	while (i < ft_lstsize(rt->ob_lst))
	{
		intersect_init(rt, ft_lstcnt(rt->ob_lst, i), cl_elem->p, cl_elem->l);
		if (rt->t1 >= 0.001 && rt->t1 <= 1)
			closest_t = rt->t1;
		if (rt->t2 >= 0.001 && rt->t2 <= 1)
			closest_t = rt->t2;
		i++;
	}
	return (closest_t);
}

float	comp_light(t_rt *rt, t_elem *cl_elem, float t)
{
	int	i;
	float	light;
	t_lgt	*lgt;
	
	light = 0;
	i = 0;
	cl_elem->p = v_plus(rt->cam.pos, v_multi(rt->cam.d, t));
	cl_elem->norm = v_new(cl_elem->p, cl_elem->pos);
	normalize(&cl_elem->norm);
	light += rt->amb.ratio;
	while (i < ft_lstsize(rt->lgt_lst))
	{
		lgt = ft_lstlgt(rt->lgt_lst, i++);
		cl_elem->l = v_new(lgt->pos, cl_elem->p);
		if (shadow_intersect(rt, cl_elem) != INT_MAX)
			continue;
		if((cl_elem->n_dot_l = ft_dot(&cl_elem->norm, &cl_elem->l)) > 0)
			light += lgt->bright * cl_elem->n_dot_l/(v_len(cl_elem->norm) * v_len(cl_elem->l));
		cl_elem->v_r = reflect_ray(cl_elem->l, cl_elem->norm);
		cl_elem->r_dot_v = ft_dot(&cl_elem->v_r, &rt->cam.d);
		if(cl_elem->r_dot_v > 0)
			light += lgt->bright * powf(cl_elem->r_dot_v/(v_len(cl_elem->v_r) * v_len(rt->cam.d)), 100);
	}
	return (light);
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

t_color	closest_intersect(t_rt *rt, t_xyz start, t_xyz finish, float t_min)
{
	int	i;

	rt->closest_t = INT_MAX;
	i = 0;
	rt->closest_elem = rt->ob_lst->content;
	while (i < ft_lstsize(rt->ob_lst))
	{
		intersect_init(rt, ft_lstcnt(rt->ob_lst, i), start, finish);
		if (rt->t1 >= t_min && rt->t1 < rt->closest_t)
		{
			rt->closest_t = rt->t1;
			rt->closest_elem = ft_lstcnt(rt->ob_lst, i);
		}
		if (rt->t2 >= t_min && rt->t2 < rt->closest_t)
		{
			rt->closest_t = rt->t2;
			rt->closest_elem = ft_lstcnt(rt->ob_lst, i);
		}
		i++;
	}
	if (rt->closest_t == INT_MAX)
		return (c_null());
	return (rt->closest_elem->color);
}

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

int	c_isnull(t_color c)
{
	return (c.r == 0 && c.g == 0 && c.b == 0);
}

t_color	trace_ray(t_rt *rt, t_xyz start, t_xyz finish, int id)
{
	t_color	local_color;
	t_color	reflected_color;
	
	if (id == START_RAY)
		local_color = closest_intersect(rt, start, finish, 0);
	else
		local_color = closest_intersect(rt, start, finish, 0.001);
	if (c_isnull(local_color))
		return (local_color);
	local_color = c_multi(rt->closest_elem->color, comp_light(rt, rt->closest_elem, rt->closest_t));
	if (rt->depth <= 0)
		return (local_color);
	rt->closest_elem->v_r = reflect_ray(rt->cam.d, rt->closest_elem->norm);
	rt->depth -= 1;
	reflected_color = trace_ray(rt, rt->closest_elem->p, rt->closest_elem->v_r, MIRROR);
	reflected_color = c_multi(reflected_color, 0.3);
	local_color = c_multi(local_color, 0.7);	
	return (c_plus(local_color, reflected_color));
}

void	render(t_rt *rt)
{
	int		x;
	int	 	y;
	t_color		color;

	x = 0;
	while (x < rt->res.x)
	{
		y = 0;
		while (y < rt->res.y)
		{
			rt->depth = 3;
			to_viewport(x, y, rt);
			color = trace_ray(rt, rt->cam.pos, rt->cam.d, START_RAY);
			mlx_pixel_put(rt->mlx, rt->mlx_win, x, y, ft_color(color.r, color.g, color.b));
			y++;
		}
		x++;

	}
}



