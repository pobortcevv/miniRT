/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:22:24 by sabra             #+#    #+#             */
/*   Updated: 2021/01/18 18:21:20 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float 	ft_dot(t_xyz *vec1, t_xyz *vec2)
{
	float result;

	result = vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
	return (result);
}

float	v_len(t_xyz v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_xyz	normalize(t_xyz v)
{
	float len;
	t_xyz res;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	res.x = v.x / len;
	res.y = v.y / len;
	res.z = v.z / len;
	return (res);
}

t_xyz	cross(t_xyz v1, t_xyz v2)
{
	t_xyz	v_res;

	v_res.x = v1.y * v2.z - v1.z * v2.y;
	v_res.y = v1.z * v2.x - v1.x * v2.z;
	v_res.z = v1.x * v2.y - v1.y * v2.x;
	return (v_res);
}

t_xyz	v_new(t_xyz v1, t_xyz v2)
{
	t_xyz	v_res;

	v_res.x = v1.x - v2.x;
	v_res.y = v1.y - v2.y;
	v_res.z = v1.z - v2.z;
	return (v_res);
}

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
