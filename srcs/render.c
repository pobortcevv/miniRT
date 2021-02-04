/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 06:48:14 by sabra             #+#    #+#             */
/*   Updated: 2021/02/04 14:26:00 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

t_color	comp_light(t_rt *rt, t_elem *cl_elem, float t)
{
	int	i;
	float	light;
	t_lgt	*lgt;
	t_color	result;
	
	light = 0;
	i = 0;
	cl_elem->p = v_plus(rt->cam.pos, v_multi(rt->cam.d, t));
	if (cl_elem->id == SPHERE)
		cl_elem->norm = v_new(cl_elem->p, cl_elem->pos);
	else
		cl_elem->norm = cl_elem->ori;
	cl_elem->norm = normalize(cl_elem->norm);
	light += rt->amb.ratio;
	result = c_one();
	color_ambiant(&result, rt->amb.color);
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
		color_ambiant(&result, lgt->color);	
	}
	color_light(&result, light);	
	return (result);
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
	local_color = c_multi_colors(rt->closest_elem->color, comp_light(rt, rt->closest_elem, rt->closest_t));
	if (rt->depth <= 0)
		return (local_color);
	rt->closest_elem->v_r = reflect_ray(rt->cam.d, rt->closest_elem->norm);
	rt->depth -= 1;
	reflected_color = trace_ray(rt, rt->closest_elem->p, rt->closest_elem->v_r, MIRROR);
	reflected_color = c_multi(reflected_color, 0.4);
	local_color = c_multi(local_color, 0.6);	
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
			rt->depth = 0;
			to_viewport(x, y, rt);
			color = trace_ray(rt, rt->cam.pos, rt->cam.d, START_RAY);
			mlx_pixel_put(rt->mlx, rt->mlx_win, x, y, ft_color(color.r, color.g, color.b));
			y++;
		}
		x++;
	}
}
