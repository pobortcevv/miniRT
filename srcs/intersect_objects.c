/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:16:31 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 19:22:37 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	intersect_init(t_rt *rt, t_elem *elem, t_xyz start, t_xyz finish)
{
	if (elem->id == SPHERE)
		intersect_sp(rt, elem, start, finish);
	else if (elem->id == PLANE)
		intersect_pl(rt, elem, start, finish);
	else if (elem->id == SQUARE)
		intersect_sq(rt, elem, start, finish);
	else if (elem->id == TRIANGLE)
		intersect_tr(rt, elem, start, finish);
	else if (elem->id == CYLINDER)
		intersect_cy(rt, elem, start, finish);
}
