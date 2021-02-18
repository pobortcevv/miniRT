/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:43:46 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 17:43:50 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_xyz	cy_normal(t_elem cy, t_xyz cp)
{
	t_xyz tau;
	t_xyz norm;

	normalize(&cy.ori);
	tau = v_cross(cy.ori, cp);
	normalize(&tau);
	norm = v_cross(tau, cy.ori);
	return (norm);
}

void	intersect_cy(t_rt *rt, t_elem *cy, t_xyz start, t_xyz finish)
{
	t_xyz	oc;
	float	k1;
	float	k2;
	float	k3;

	oc = v_new(start, cy->pos);
	normalize(&cy->ori);
	k1 = ft_dot(&finish, &finish) - powf(ft_dot(&cy->ori, &finish), 2);
	k2 = 2 * (ft_dot(&finish, &oc) -
			ft_dot(&cy->ori, &oc) * ft_dot(&cy->ori, &finish));
	k3 = ft_dot(&oc, &oc) - powf(ft_dot(&cy->ori, &oc), 2) - powf(cy->r, 2);
	rt->t1 = ft_queq(k1, k2, k3, 1);
	rt->t2 = ft_queq(k1, k2, k3, 2);
	cy->p = v_plus(start, v_multi(finish, rt->t1));
	cy->p_2 = v_plus(start, v_multi(finish, rt->t2));
	if (ft_dot(&cy->ori, &cy->p) < cy->cy_hight / -2 ||
			ft_dot(&cy->ori, &cy->p) > cy->cy_hight / 2)
		rt->t1 = INT_MAX;
	if (ft_dot(&cy->ori, &cy->p_2) < cy->cy_hight / -2 ||
			ft_dot(&cy->ori, &cy->p_2) > cy->cy_hight / 2)
		rt->t2 = INT_MAX;
}

void	parse_cylinder_p2(t_rt *rt, t_elem *cy, char **place_split)
{
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT)
			|| !find_err(place_split[2], FLOAT) ||
			!find_err(rt->split[3], FLOAT))
		error_parse(rt, "CYLINDER INFO ERROR\n", cy, place_split);
	cy->pos.x = ft_atof(place_split[0]);
	cy->pos.y = ft_atof(place_split[1]);
	cy->pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT))
		error_parse(rt, "CYLINDER INFO ERROR\n", cy, place_split);
	cy->ori.x = ft_atof(place_split[0]);
	cy->ori.y = ft_atof(place_split[1]);
	cy->ori.z = ft_atof(place_split[2]);
	if ((cy->r = ft_atof(rt->split[3]) / 2) < 0 ||
			(cy->cy_hight = ft_atof(rt->split[4])) < 0)
		error_parse(rt, "CYLINDER INFO ERROR\n", cy, place_split);
	ft_free_mat(place_split);
}

int		parse_cylinder(t_rt *rt)
{
	char	**place_split;
	t_elem	*cy;

	if (ft_split_size(rt->split) != 6 || ft_charcnt(rt->split[1], ',') != 2
			|| ft_charcnt(rt->split[2], ',') != 2 ||
			ft_charcnt(rt->split[5], ',') != 2)
		return (0);
	cy = ft_calloc(1, sizeof(t_elem));
	cy->id = CYLINDER;
	place_split = ft_split(rt->split[1], ',');
	parse_cylinder_p2(rt, cy, place_split);
	place_split = ft_split(rt->split[5], ',');
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT))
		error_parse(rt, "CYLINDER INFO ERROR\n", cy, place_split);
	cy->color.b = ft_atof(place_split[0]);
	cy->color.g = ft_atof(place_split[1]);
	cy->color.r = ft_atof(place_split[2]);
	if (!check_color_parse(cy->color))
		error_parse(rt, "CYLINDER INFO ERROR\n", cy, place_split);
	ft_free_mat(place_split);
	ft_lstadd_back(&rt->ob_lst, ft_lstnew(cy));
	return (1);
}
