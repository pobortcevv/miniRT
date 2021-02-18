/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 18:01:12 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 18:14:37 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	parse_camera_p2(t_rt *rt, t_cam *cam, char **place_split)
{
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT)
			|| !find_err(rt->split[3], INT))
		error_parse(rt, "CAMERA INFO ERROR\n", cam, place_split);
	cam->pos.x = ft_atof(place_split[0]);
	cam->pos.y = ft_atof(place_split[1]);
	cam->pos.z = ft_atof(place_split[2]);
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT))
		error_parse(rt, "CAMERA INFO ERROR\n", cam, place_split);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
	cam->ori.x = ft_atof(place_split[0]);
	cam->ori.y = ft_atof(place_split[1]);
	cam->ori.z = ft_atof(place_split[2]);
	if ((cam->fov = ft_atof(rt->split[3]) * (3.14 / 180)) < 0)
		error_parse(rt, "CAMERA INFO ERROR\n", cam, place_split);
	ft_free_mat(place_split);
}

int			parse_camera(t_rt *rt)
{
	char	**place_split;
	t_cam	*cam;

	if (ft_split_size(rt->split) != 4 || ft_charcnt(rt->split[1], ',') != 2
			|| ft_charcnt(rt->split[2], ',') != 2)
		return (0);
	cam = ft_calloc(1, sizeof(t_cam));
	place_split = ft_split(rt->split[1], ',');
	parse_camera_p2(rt, cam, place_split);
	cam->id = rt->cam_count;
	rt->cam_count += 1;
	ft_lstadd_back(&rt->cmr_lst, ft_lstnew(cam));
	return (1);
}
