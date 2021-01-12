/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 06:42:11 by sabra             #+#    #+#             */
/*   Updated: 2021/01/12 13:58:14 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float ft_dot(t_xyz *vec1, t_xyz *vec2)
{
	float result;

	result = vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
	return (result);
}
