/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:42:15 by sabra             #+#    #+#             */
/*   Updated: 2021/01/06 17:49:26 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		char_count(char *line, int c)
{
	int count;

	count = 0;
	while (*line++)
	{
		if (*line == c)
			count++;
	}
	return (count);
}

int		parse_scene(t_rt *rt, int id)
{
	char	**place_split;
	if (id == RESOLUTION)
	{
		rt->res.x = ft_atoi(rt->split[1]);
		rt->res.y = ft_atoi(rt->split[2]);	
	}
	if (id == CAMERA)
	{
		if (char_count(rt->split[1], ',') != 2 && char_count(rt->split[2], ',') != 2 && place_split = ft_split(rt->split[1]));
			return (0);
		rt->cam->pos.x = ft_atof(place_split[0]);
		rt->cam->pos.y = ft_atof(place_split[1]);
		rt->cam->pos.z = ft_atof(place_split[2]);
		ft_free_mat(place_split);
			
	}
	
	return (1);
}

int		line_check(char *line)
{
	if (*line == '\0')
		return(EMPTY_LINE);
	return (1);
}

int		ft_pars(t_rt *rt)
{
	int result;
	
	result = 0;
	while ((result = get_next_line(rt->fd, &(rt->line))) == 1)
	{
		if ((line_check(rt->line) == EMPTY_LINE))
				continue;
		rt->split = ft_split(rt->line, ' ');
		if (rt->split[0][0] == 'R')
			parse_scene(rt, RESOLUTION);
		else if (rt->split[0][0] == 'A')
			parse_scene(rt, AMBIANT);
		else if (rt->split[0][0] == 'c')
			parse_scene(rt, CAMERA);
		else if (rt->split[0][0] == 'l')
			parse_scene(rt, LIGHT);
		//if ((ft_strncmp(rt->split[0], "sp")) == 0)
			//parse_objects(rt, SPHERE);
		ft_free_mat(rt->split);
		ft_free_line(rt->line);
	}
	return (result);
}

