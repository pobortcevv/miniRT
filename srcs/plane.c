/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:01:51 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 20:32:21 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	intersect_pl(t_rt *rt, t_elem *pl, t_xyz start, t_xyz finish)
{
	t_xyz	co;
	float	k1;
	float	k2;

	co = v_new(pl->pos, start);
	normalize(&pl->ori);
	k1 = ft_dot(&pl->ori, &co);
	k2 = ft_dot(&pl->ori, &finish);
	if (k2 == 0)
		rt->t1 = INT_MAX;
	else
		rt->t1 = k1 / k2;
	rt->t2 = INT_MAX;
}

void	parse_plane_p2(t_rt *rt, t_elem *pl, char **place_split)
{
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT))
		error_parse(rt, "PLANE INFO ERROR\n", pl, place_split);
	pl->pos.x = ft_atof(place_split[0]);
	pl->pos.y = ft_atof(place_split[1]);
	pl->pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT))
		error_parse(rt, "PLANE INFO ERROR\n", pl, place_split);
	pl->ori.x = ft_atof(place_split[0]);
	pl->ori.y = ft_atof(place_split[1]);
	pl->ori.z = ft_atof(place_split[2]);
	if (!normal_check(pl->ori))
		error_parse(rt, "PLANE INFO ERROR\n", pl, place_split);
}

int		parse_plane(t_rt *rt)
{
	char	**place_split;
	t_elem	*pl;

	if (ft_split_size(rt->split) != 4 || ft_charcnt(rt->split[1], ',') != 2
			|| ft_charcnt(rt->split[3], ',') != 2 ||
			ft_charcnt(rt->split[2], ',') != 2)
		return (0);
	pl = ft_calloc(1, sizeof(t_elem));
	pl->id = PLANE;
	place_split = ft_split(rt->split[1], ',');
	parse_plane_p2(rt, pl, place_split);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[3], ',');
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT))
		error_parse(rt, "PLANE INFO ERROR\n", pl, place_split);
	pl->color.b = ft_atof(place_split[0]);
	pl->color.g = ft_atof(place_split[1]);
	pl->color.r = ft_atof(place_split[2]);
	if (!check_color_parse(pl->color))
		error_parse(rt, "PLANE COLOR INFO ERROR\n", pl, place_split);
	ft_free_mat(place_split);
	ft_lstadd_back(&rt->ob_lst, ft_lstnew(pl));
	return (1);
}
