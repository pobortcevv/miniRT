/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:26:25 by sabra             #+#    #+#             */
/*   Updated: 2021/02/11 16:55:45 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
	rt->t1 = INT_MAX;
	rt->t2 = INT_MAX;
	while (i < ft_lstsize(rt->ob_lst))
	{
		intersect_init(rt, ft_lstcnt(rt->ob_lst, i), cl_elem->p, cl_elem->l);
		if (rt->t1 >= 0.0001 && rt->t1 < 1)
			closest_t = rt->t1;
		if (rt->t2 >= 0.0001 && rt->t2 < 1)
			closest_t = rt->t2;
		i++;
	}
	return (closest_t);
}

void	to_viewport(int x, int y, t_rt *rt)
{
	float	scale_w;
	float	scale_h;
	float	**rotation_m;

	normalize(&rt->cam.ori);
	scale_w = 2 * tan((rt->cam.fov / 2)) / rt->res.y;
	scale_h = 2 * tan(rt->cam.fov / 2) / rt->res.y;
	rt->cam.d.x = scale_w * (x - (rt->res.x / 2));
	rt->cam.d.y = scale_h * (rt->res.y / 2 - y);
	rt->cam.d.z = 1;
	//rt->cam.d.x = x - rt->res.x / 2;
	//rt->cam.d.y = rt->res.y / 2 - y;
	//rt->cam.d.z = -(rt->res.y / 2) / tan(rt->cam.fov / 2);
	//rt->cam.d = rotate_scene(rt->cam.d, rotation_matrix(rt->cam.ori));
	//rt->cam.d = v_new(rt->cam.d, rt->cam.pos);
	rt->cam.d.x -= rt->cam.pos.x;
	rt->cam.d.y -= rt->cam.pos.y;
	rotation_m = rotation_matrix(rt->cam.ori);
}
