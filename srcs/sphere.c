/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 18:51:22 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 19:01:15 by sabra            ###   ########.fr       */
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

void	parse_sphere_p2(t_rt *rt, t_elem *sp, char **place_split)
{
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT)
			|| !find_err(rt->split[2], FLOAT))
		error_parse(rt, "SPHERE INFO ERROR\n", sp, place_split);
	sp->pos.x = ft_atof(place_split[0]);
	sp->pos.y = ft_atof(place_split[1]);
	sp->pos.z = ft_atof(place_split[2]);
	if ((sp->r = ft_atof(rt->split[2]) / 2) < 0)
		error_parse(rt, "SPHERE INFO ERROR\n", sp, place_split);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[3], ',');
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT))
		error_parse(rt, "SPHERE INFO ERROR\n", sp, place_split);
	sp->color.b = ft_atof(place_split[0]);
	sp->color.g = ft_atof(place_split[1]);
	sp->color.r = ft_atof(place_split[2]);
	if (!check_color_parse(sp->color))
		error_parse(rt, "SPHERE COLOR INFO ERROR\n", sp, place_split);
}

int		parse_sphere(t_rt *rt)
{
	char	**place_split;
	t_elem	*sp;

	if (ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[3], ',') != 2
			|| ft_split_size(rt->split) != 4)
		return (0);
	sp = ft_calloc(1, sizeof(t_elem));
	sp->id = SPHERE;
	place_split = ft_split(rt->split[1], ',');
	parse_sphere_p2(rt, sp, place_split);
	ft_free_mat(place_split);
	ft_lstadd_back(&rt->ob_lst, ft_lstnew(sp));
	return (1);
}
