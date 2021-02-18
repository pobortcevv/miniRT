/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:45:37 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 19:36:37 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		parse_ambiant(t_rt *rt)
{
	char	**place_split;

	if (ft_charcnt(rt->split[2], ',') != 2 || ft_split_size(rt->split) != 3)
		return (0);
	place_split = ft_split(rt->split[2], ',');
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT) ||
			!find_err(place_split[1], FLOAT) || !find_err(place_split[2], FLOAT)
			|| !find_err(rt->split[1], FLOAT))
		return (0);
	rt->amb.color.b = ft_atof(place_split[0]);
	rt->amb.color.g = ft_atof(place_split[1]);
	rt->amb.color.r = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	if (!check_color_parse(rt->amb.color))
		return (0);
	if ((rt->amb.ratio = ft_atof(rt->split[1])) < 0 || (rt->amb.ratio > 1))
		return (0);
	rt->amb.id = 1;
	return (1);
}

void	parse_light_p2(t_rt *rt, t_lgt *l, char **place_split)
{
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
		|| !find_err(place_split[1], FLOAT) || !find_err(place_split[2], FLOAT)
		|| !find_err(rt->split[2], FLOAT))
		error_parse(rt, "LIGHT INFO ERROR\n", l, place_split);
	l->pos.x = ft_atof(place_split[0]);
	l->pos.y = ft_atof(place_split[1]);
	l->pos.z = ft_atof(place_split[2]);
	if ((l->bright = ft_atof(rt->split[2])) < 0 || (l->bright > 1))
		error_parse(rt, "LIGHT INFO ERROR\n", l, place_split);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[3], ',');
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT))
		error_parse(rt, "LIGHT INFO ERROR\n", l, place_split);
	l->color.b = ft_atof(place_split[0]);
	l->color.g = ft_atof(place_split[1]);
	l->color.r = ft_atof(place_split[2]);
	if (!check_color_parse(l->color))
		error_parse(rt, "LIGHT COLOR INFO ERROR\n", l, place_split);
}

int		parse_light(t_rt *rt)
{
	char	**place_split;
	t_lgt	*l;

	if (ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[3], ',') != 2
			|| ft_split_size(rt->split) != 4)
		return (0);
	l = ft_calloc(1, sizeof(t_lgt));
	place_split = ft_split(rt->split[1], ',');
	parse_light_p2(rt, l, place_split);
	ft_free_mat(place_split);
	ft_lstadd_back(&rt->lgt_lst, ft_lstnew(l));
	return (1);
}

int		parse_res(t_rt *rt)
{
	if (!find_err(rt->split[1], INT) || !find_err(rt->split[2], INT)
			|| ft_split_size(rt->split) != 3 || rt->res.id == 1)
		return (0);
	rt->res.x = ft_atoi(rt->split[1]);
	rt->res.y = ft_atoi(rt->split[2]);
	if (rt->res.x > 2560)
		rt->res.x = 2560;
	if (rt->res.y > 1440)
		rt->res.y = 1440;
	if (rt->res.x < 0 || rt->res.y < 0)
		return (0);
	rt->res.id = 1;
	return (1);
}
