/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:45:37 by sabra             #+#    #+#             */
/*   Updated: 2021/01/11 22:27:58 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		parse_sphere(t_rt *rt)
{
	char	**place_split;

	if (ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[3], ',') != 2)
		return (0);
	place_split = ft_split(rt->split[1], ',');
	if (!dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT)
			|| !dushnila_defence(rt->split[2], FLOAT))
		return (0);
	rt->sp.pos.x = ft_atof(place_split[0]);
	rt->sp.pos.y = ft_atof(place_split[1]);
	rt->sp.pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	rt->sp.r = ft_atof(rt->split[2]) / 2;
	place_split = ft_split(rt->split[3], ',');
	if (!dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		return (0);
	rt->sp.color.r = ft_atof(place_split[0]);
	rt->sp.color.g = ft_atof(place_split[1]);
	rt->sp.color.b = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	return (1);
}

int		parse_camera(t_rt *rt)
{
	char	**place_split;

	if (ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[2], ',') != 2)
		return (0);
	place_split = ft_split(rt->split[1], ',');
	if (!dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT)
			|| !dushnila_defence(rt->split[3], INT))
		return (0);
	rt->cam.pos.x = ft_atof(place_split[0]);
	rt->cam.pos.y = ft_atof(place_split[1]);
	rt->cam.pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
	if (!dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		return (0);
	rt->cam.or.x = ft_atof(place_split[0]);
	rt->cam.or.y = ft_atof(place_split[1]);
	rt->cam.or.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	rt->cam.fov = ft_atof(rt->split[3]) * (3.14/180);
	rt->cam.num += 1;
	return (1);
}

int		parse_res(t_rt *rt)
{
	if (!dushnila_defence(rt->split[1], INT) || !dushnila_defence(rt->split[2], INT))
		return (0);
	rt->res.x = ft_atoi(rt->split[1]);
	rt->res.y = ft_atoi(rt->split[2]);
	rt->res.id = 1;
	return (1);
}
