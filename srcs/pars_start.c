/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:42:15 by sabra             #+#    #+#             */
/*   Updated: 2021/02/01 14:10:49 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		ft_split_size(char **split)
{
	int 	size;

	size = -1;
	while(split[++size]);
	return(size);
}

int		dushnila_defence(char *line, int id)
{
	if (id == INT)
	{
		if (ft_charcnt(line, '-') > 1 || (ft_charcnt(line, '-') > 0 && line[0] != '-'))
			return (0);
		if (!(ft_inset(line, "-0123456789")))
			return (0);
	}
	if (id == FLOAT)
	{
		if (ft_charcnt(line, '-') > 1 || (ft_charcnt(line, '-') > 0 && line[0] != '-'))
			return (0);
		if (ft_charcnt(line, '.') > 1 || (!(ft_isdigit(line[0])) && !(line[0] == '-')))
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

int		ft_pars(t_rt *rt)
{
	int result;
	
	result = 1;
	while (get_next_line(rt->fd, &(rt->line)) == 1 && result)
	{
		if (*(rt->line) == '\0')
				continue;
		rt->split = ft_split(rt->line, ' ');
		if ((ft_memcmp(rt->split[0], "R", ft_strlen(rt->split[0]))) == 0)
			 result = parse_res(rt);
		else if ((ft_memcmp(rt->split[0], "A", ft_strlen(rt->split[0]))) == 0)
			result = parse_ambiant(rt);
		if ((ft_memcmp(rt->split[0], "c", ft_strlen(rt->split[0]))) == 0)
			result = parse_camera(rt);
		if ((ft_memcmp(rt->split[0], "l", ft_strlen(rt->split[0]))) == 0)
			result = parse_light(rt);
		if ((ft_memcmp(rt->split[0], "sp", ft_strlen(rt->split[0]))) == 0)
			result = parse_sphere(rt);
		if ((ft_memcmp(rt->split[0], "pl", ft_strlen(rt->split[0]))) == 0)
			result = parse_plane(rt);
		if ((ft_memcmp(rt->split[0], "sq", ft_strlen(rt->split[0]))) == 0)
			result = parse_square(rt);
		if ((ft_memcmp(rt->split[0], "tr", ft_strlen(rt->split[0]))) == 0)
			result = parse_triangle(rt);
		ft_free_mat(rt->split);
		ft_free_line(rt->line);
	}
	return (result);
}

