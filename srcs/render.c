/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 06:48:14 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 17:14:53 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	extra_light(t_rt *rt, t_elem *cl_elem, float light, t_color *result)
{
	int		i;
	t_lgt	*lgt;

	i = 0;
	while (i < ft_lstsize(rt->lgt_lst))
	{
		lgt = ft_lstlgt(rt->lgt_lst, i++);
		cl_elem->l = v_new(lgt->pos, cl_elem->p);
		if (shadow_intersect(rt, cl_elem) != INT_MAX)
			continue;
		if ((cl_elem->n_dot_l = ft_dot(&cl_elem->norm, &cl_elem->l)) > 0)
			light += lgt->bright * cl_elem->n_dot_l /
				(v_len(cl_elem->norm) * v_len(cl_elem->l));
		cl_elem->v_r = reflect_ray(cl_elem->l, cl_elem->norm);
		cl_elem->r_dot_v = ft_dot(&cl_elem->v_r, &rt->cam.d);
		if (cl_elem->r_dot_v > 0)
			light += lgt->bright * powf(cl_elem->r_dot_v /
					(v_len(cl_elem->v_r) * v_len(rt->cam.d)), BRIGHT_RATE);
		color_ambiant(result, lgt->color);
	}
	return (light);
}

t_color	comp_light(t_rt *rt, t_elem *cl_elem, float t)
{
	int		i;
	float	light;
	t_color	result;

	light = 0;
	i = 0;
	cl_elem->p = v_plus(rt->cam.pos, v_multi(rt->cam.d, t));
	if (cl_elem->id == SPHERE)
		cl_elem->norm = v_new(cl_elem->p, cl_elem->pos);
	else if (cl_elem->id == CYLINDER)
		cl_elem->norm = cy_normal(*cl_elem, v_new(cl_elem->p, cl_elem->pos));
	else
		cl_elem->norm = cl_elem->ori;
	normalize(&cl_elem->norm);
	light += rt->amb.ratio;
	result = c_one();
	color_ambiant(&result, rt->amb.color);
	light = extra_light(rt, cl_elem, light, &result);
	color_light(&result, light);
	return (result);
}

t_color	closest_intersect(t_rt *rt, t_xyz start, t_xyz finish, float t_min)
{
	int	i;

	rt->closest_t = INT_MAX;
	i = 0;
	rt->cl_el = rt->ob_lst->content;
	while (i < ft_lstsize(rt->ob_lst))
	{
		intersect_init(rt, ft_lstcnt(rt->ob_lst, i), start, finish);
		if (rt->t1 >= t_min && rt->t1 < rt->closest_t)
		{
			rt->closest_t = rt->t1;
			rt->cl_el = ft_lstcnt(rt->ob_lst, i);
		}
		if (rt->t2 >= t_min && rt->t2 < rt->closest_t)
		{
			rt->closest_t = rt->t2;
			rt->cl_el = ft_lstcnt(rt->ob_lst, i);
		}
		i++;
	}
	if (rt->closest_t == INT_MAX)
		return (c_null());
	return (rt->cl_el->color);
}

t_color	trace_ray(t_rt *rt, t_xyz start, t_xyz finish, int id)
{
	t_color	l_c;
	t_color	reflected_color;

	if (id == START_RAY)
		l_c = closest_intersect(rt, start, finish, CAMERA_START);
	else
		l_c = closest_intersect(rt, start, finish, EPSILON);
	if (c_isnull(l_c))
		return (l_c);
	l_c = cs_multi(rt->cl_el->color, comp_light(rt, rt->cl_el, rt->closest_t));
	if (rt->depth <= 0)
		return (l_c);
	rt->cl_el->v_r = reflect_ray(rt->cam.d, rt->cl_el->norm);
	rt->depth -= 1;
	reflected_color = trace_ray(rt, rt->cl_el->p, rt->cl_el->v_r, MIRROR);
	reflected_color = c_multi(reflected_color, 1 - REFLECTION_RATE);
	l_c = c_multi(l_c, REFLECTION_RATE);
	return (c_plus(l_c, reflected_color));
}

void	render(t_rt *rt)
{
	int			x;
	int			y;
	t_color		color;
	float		**rotation_m;
	int			res;

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
			res = ft_color(color.r, color.g, color.b);
			mlx_pixel_put(rt->mlx, rt->mlx_win, x, y, res);
			y++;
		}
		x++;
	}
	ft_free_float_mat(rotation_m);
}
