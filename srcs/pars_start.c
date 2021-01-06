/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:42:15 by sabra             #+#    #+#             */
/*   Updated: 2021/01/06 09:51:40 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		parse_scene(t_rt *rt, int id)
{
	if (id == RESOLUTION)
	{
		rt->res.x = ft_atoi(rt->split[1]);
		rt->res.y = ft_atoi(rt->split[2]);	
	}
	ft_printf("x = %d\ny = %d\n", rt->res.x, rt->res.y); 
	return (1);
}

int		ft_pars(t_rt *rt)
{
	int result;
	
	result = 0;
	while ((result = get_next_line(rt->fd, &(rt->line))) == 1)
	{
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
		ft_free_split(rt->split);
		free(rt->line);
	}
	return (result);
}
