/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:16:31 by sabra             #+#    #+#             */
/*   Updated: 2021/02/04 14:24:00 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

void	intersect_pl(t_rt *rt, t_elem *pl, t_xyz start, t_xyz finish)
{
	t_xyz	co;
	float	k1;
	float	k2;


	co = v_new(pl->pos, start);
	pl->ori = normalize(pl->ori);
	k1 = ft_dot(&pl->ori, &co);
	k2 = ft_dot(&pl->ori, &finish);
	if (k2 == 0)
		rt->t1 = INT_MAX;
	else
		rt->t1 = (k1 / k2);
	rt->t2 = INT_MAX;
}

int	intersect_sq(t_rt *rt, t_elem *sq, t_xyz start, t_xyz finish)
{
	t_xyz	co;
	t_xyz	hit;
	float	k1;
	float	k2;

	co = v_new(sq->pos, start);
	sq->ori = normalize(sq->ori);
	k1 = ft_dot(&(sq->ori), &co);
	rt->t2 = INT_MAX;
	k2 = ft_dot(&finish, &sq->ori);
	if (k2 == 0)
	{
		rt->t1 = INT_MAX;
		return (0);
	}
	rt->t1 = (k1 / k2);
	hit = v_new(v_multi(finish, rt->t1), sq->pos);
	if (fabs(hit.x) <= (sq->len / 2) &&
			fabs(hit.y) <= (sq->len / 2) &&
			fabs(hit.z) <= (sq->len / 2))
		return (1);
	else
		rt->t1 = INT_MAX;
	return (0);
}

int		intersect_tr(t_rt *rt, t_elem *tr, t_xyz start, t_xyz finish)
{
	float a;
	float f;
	float u;
	float v;
	
	rt->t2 = INT_MAX;
	rt->t1 = INT_MAX;
	tr->edge1 = v_new(tr->vertex1, tr->vertex0);
	tr->edge2 = v_new(tr->vertex2, tr->vertex0);
	tr->hight = v_cross(finish, tr->edge2);
	a = ft_dot(&tr->edge1, &tr->hight);
	if (a > -0.00001 && a < 0.00001)
		return (0);
	tr->s = v_new(start, tr->vertex0);
	f = 1 / a;
	u = f * ft_dot(&tr->s, &tr->hight);
	if (u < 0 || u > 1)
		return (0);
	tr->q = v_cross(tr->s, tr->edge1);
	v = f * ft_dot(&finish, &tr->q);
	if (v < 0 || v + u > 1)
		return (0);
	rt->t1 = f * ft_dot(&tr->edge2, &tr->q);
	if (rt->t1 <= 0.00001)
		rt->t1 = INT_MAX;
	return (1);
}

void	intersect_init(t_rt *rt, t_elem *elem, t_xyz start, t_xyz finish)
{
	if (elem->id == SPHERE)
		intersect_sp(rt, elem, start, finish);
	else if(elem->id == PLANE)
		intersect_pl(rt, elem, start, finish);
	else if(elem->id == SQUARE)
		intersect_sq(rt, elem, start, finish);
	else if(elem->id == TRIANGLE)
		intersect_tr(rt, elem, start, finish);

}
