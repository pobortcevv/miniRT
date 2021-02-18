/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_to_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:34:32 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 15:23:26 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void		change_frame(t_rt *rt, t_cam *cam)
{
	int		i;
	t_elem	*curr_elem;
	t_lgt	*curr_lgt;

	i = 0;
	while (i < ft_lstsize(rt->ob_lst))
	{
		curr_elem = ft_lstcnt(rt->ob_lst, i);
		if (curr_elem->id != TRIANGLE)
			curr_elem->pos = v_new(curr_elem->pos, cam->pos);
		else
		{
			curr_elem->vertex0 = v_new(curr_elem->vertex0, cam->pos);
			curr_elem->vertex1 = v_new(curr_elem->vertex1, cam->pos);
			curr_elem->vertex2 = v_new(curr_elem->vertex2, cam->pos);
		}
		i++;
	}
	i = 0;
	while (i < ft_lstsize(rt->lgt_lst))
	{
		curr_lgt = ft_lstlgt(rt->lgt_lst, i++);
		curr_lgt->pos = v_new(curr_lgt->pos, cam->pos);
	}
	cam->pos = v_new(cam->pos, cam->pos);
}

void		rotate_tr(float **rotation_m, t_elem *curr_elem)
{
	curr_elem->vertex0 = rotate_scene(curr_elem->vertex0, rotation_m);
	curr_elem->vertex1 = rotate_scene(curr_elem->vertex1, rotation_m);
	curr_elem->vertex2 = rotate_scene(curr_elem->vertex2, rotation_m);
}

void		cam_to_world(t_rt *rt, float **rotation_m, t_cam *cam)
{
	int		i;
	t_elem	*curr_elem;
	t_lgt	*curr_lgt;

	i = 0;
	change_frame(rt, cam);
	while (i < ft_lstsize(rt->ob_lst))
	{
		curr_elem = ft_lstcnt(rt->ob_lst, i++);
		if (curr_elem->id != TRIANGLE)
		{
			curr_elem->pos = rotate_scene(curr_elem->pos, rotation_m);
			curr_elem->ori = rotate_scene(curr_elem->ori, rotation_m);
		}
		else
			rotate_tr(rotation_m, curr_elem);
	}
	i = 0;
	while (i < ft_lstsize(rt->lgt_lst))
	{
		curr_lgt = ft_lstlgt(rt->lgt_lst, i++);
		curr_lgt->pos = rotate_scene(curr_lgt->pos, rotation_m);
	}
}
