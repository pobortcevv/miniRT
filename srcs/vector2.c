/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:39:09 by sabra             #+#    #+#             */
/*   Updated: 2021/02/17 22:40:29 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_xyz	v_multi(t_xyz v, float n)
{
	t_xyz	v_res;

	v_res.x = v.x * n;
	v_res.y = v.y * n;
	v_res.z = v.z * n;
	return (v_res);
}

t_xyz	v_plus(t_xyz v1, t_xyz v2)
{
	t_xyz	v_res;

	v_res.x = v1.x + v2.x;
	v_res.y = v1.y + v2.y;
	v_res.z = v1.z + v2.z;
	return (v_res);
}
