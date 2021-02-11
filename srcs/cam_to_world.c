/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_to_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:34:32 by sabra             #+#    #+#             */
/*   Updated: 2021/02/11 17:47:45 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/* 
 * Реализовать смещение камеры
 * с pos на 0.0.0
 *
 */

void	cam_to_world(t_rt *rti, float **rotation_m)
{
	int		i;
	t_elem	curr_elem;
	t_lgt	curr_lgt;

	i = 0;
	while(i < ft_lstsize(rt->ob_lst))
	{
		curr_elem = ft_lstcnt(rt->ob_lst, i);
		if (curr_elem->id != TRIANGLE)
		{
			curr_elem->pos = rotate_scene(curr_elem->pos, rotation_m);
			curr_elem->ori = rotate_scene(curr_elem->ori, rotation_m);
		}
		else
		{
			curr_elem->vertex0 = rotate_scene(curr_elem->vertex0, rotation_m);
			curr_elem->vertex1 = rotate_scene(curr_elem->vertex1, rotation_m);
			curr_elem->vertex2 = rotate_scene(curr_elem->vertex2, rotation_m);
		}
		i++;
	}
	i = 0;
	while (i < ft_lstsize(rt->lgt_lst))
	{
		curr_lgt = ft_lstcnt(rt->lgt_lst, i);
		curr_lgt->pos = rotate_scene(curr_lgt->pos, rotation_m);
		i++;
	}
}
