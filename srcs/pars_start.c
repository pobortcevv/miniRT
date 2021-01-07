/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:42:15 by sabra             #+#    #+#             */
/*   Updated: 2021/01/08 01:07:51 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		char_count(char *line, int c)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == c)
			count++;
		i++;
	}
	return (count);
}

int		dushnila_defence(char *line, int id)
{
	if (id == INT)
	{
		if (char_count(line, '-') > 1 || (char_count(line, '-') > 0 && line[0] != '-'))
			return (0);
		if (!(ft_inset(line, "-0123456789")))
			return (0);
	}
	if (id == FLOAT)
	{
		if (char_count(line, '-') > 1 || (char_count(line, '-') > 0 && line[0] != '-'))
			return (0);
		if (char_count(line, '.') > 1 || !(ft_isdigit(line[0])))
			return (0);
		if (!(ft_inset(line, "-0123456789.")))
			return (0);
	}
	if (id == STRING)
	{
		if (!ft_memcmp(line, "R", ft_strlen(line)) || !ft_memcmp(line, "A", ft_strlen(line))
		|| !ft_memcmp(line, "c", ft_strlen(line))
		|| !ft_memcmp(line, "l", ft_strlen(line))
		|| !ft_memcmp(line, "pl", ft_strlen(line))
		|| !ft_memcmp(line, "sp", ft_strlen(line))
		|| !ft_memcmp(line, "sq", ft_strlen(line))
		|| !ft_memcmp(line, "cy", ft_strlen(line))
		|| !ft_memcmp(line, "tr", ft_strlen(line)))
			return (0);
	}
	return (1);
}

int		parse_sphere(t_rt *rt)
{
	char	**place_split;

	if (char_count(rt->split[1], ',') != 2 && char_count(rt->split[3], ',') != 2)
		return (0);
	place_split = ft_split(rt->split[1], ',');
	rt->sp.pos.x = ft_atof(place_split[0]);
	rt->sp.pos.y = ft_atof(place_split[1]);
	rt->sp.pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	rt->sp.r = ft_atof(rt->split[2]);
	place_split = ft_split(rt->split[3], ',');
	rt->sp.color.r = ft_atof(place_split[0]);
	rt->sp.color.g = ft_atof(place_split[1]);
	rt->sp.color.b = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	return (1);
}

int		parse_camera(t_rt *rt)
{
	char	**place_split;

	if (char_count(rt->split[1], ',') != 2 && char_count(rt->split[2], ',') != 2)
		return (0);
	place_split = ft_split(rt->split[1], ',');
	rt->cam.pos.x = ft_atof(place_split[0]);
	rt->cam.pos.y = ft_atof(place_split[1]);
	rt->cam.pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
	rt->cam.or.x = ft_atof(place_split[0]);
	rt->cam.or.y = ft_atof(place_split[1]);
	rt->cam.or.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	rt->cam.fov = ft_atoi(rt->split[3]);
	return (1);
}

int		parse_res(t_rt *rt)
{
	if (!dushnila_defence(rt->split[1], INT) || !dushnila_defence(rt->split[2], INT))
		return (0);
	rt->res.x = ft_atoi(rt->split[1]);
	rt->res.y = ft_atoi(rt->split[2]);	
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
	
	result = 1;
	while ((result = get_next_line(rt->fd, &(rt->line))) == 1)
	{
		if ((line_check(rt->line) == EMPTY_LINE))
				continue;
		rt->split = ft_split(rt->line, ' ');
		if ((ft_memcmp(rt->split[0], "R", ft_strlen(rt->split[0]))) == 0)
			parse_res(rt);
		//else if (rt->split[0][0] == 'A')
			//parse_scene(rt, AMBIANT);
		else if ((ft_memcmp(rt->split[0], "c", ft_strlen(rt->split[0]))) == 0)
			parse_camera(rt);
		//else if (rt->split[0][0] == 'l')
			//parse_scene(rt, LIGHT);
		if ((ft_memcmp(rt->split[0], "sp", ft_strlen(rt->split[0]))) == 0)
			parse_sphere(rt);
		ft_free_mat(rt->split);
		ft_free_line(rt->line);
	}
	return (result);
}

