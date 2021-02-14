/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:42:15 by sabra             #+#    #+#             */
/*   Updated: 2021/02/08 17:55:26 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		ft_pars(t_rt *rt)
{
	int result;
	
	result = 1;
	while (get_next_line(rt->fd, &(rt->line)) == 1 && result)
	{
		if (*(rt->line) == '\0')
		{
				ft_free_line(&rt->line);
				continue;
		}
		rt->split = ft_split(rt->line, ' ');
		if (dushnila_defence(rt->split[0], STRING) == 0)
			result = 0;
		if ((ft_strncmp(rt->split[0], "R", ft_strlen(rt->split[0]))) == 0)
			 result = parse_res(rt);
		else if ((ft_strncmp(rt->split[0], "A", ft_strlen(rt->split[0]))) == 0)
			result = parse_ambiant(rt);
		if ((ft_strncmp(rt->split[0], "c", ft_strlen(rt->split[0]))) == 0)
			result = parse_camera(rt);
		if ((ft_strncmp(rt->split[0], "l", ft_strlen(rt->split[0]))) == 0)
			result = parse_light(rt);
		if ((ft_strncmp(rt->split[0], "sp", ft_strlen(rt->split[0]))) == 0)
			result = parse_sphere(rt);
		if ((ft_strncmp(rt->split[0], "pl", ft_strlen(rt->split[0]))) == 0)
			result = parse_plane(rt);
		if ((ft_strncmp(rt->split[0], "sq", ft_strlen(rt->split[0]))) == 0)
			result = parse_square(rt);
		if ((ft_strncmp(rt->split[0], "tr", ft_strlen(rt->split[0]))) == 0)
			result = parse_triangle(rt);
		if ((ft_strncmp(rt->split[0], "cy", ft_strlen(rt->split[0]))) == 0)
			result = parse_cylinder(rt);
		ft_free_mat(rt->split);
		ft_free_line(&rt->line);
	}
	if (rt->res.id == 0 || rt->amb.id == 0 || rt->cam_count == 0)
		result = 0;
	return (result);
}

