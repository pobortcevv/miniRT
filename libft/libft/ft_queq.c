/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 15:28:56 by sabra             #+#    #+#             */
/*   Updated: 2021/01/11 07:29:31 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

double	ft_queq(double a, double b, double c, int id)
{
	double d;
	double x1;
	double x2;
	
	d = b*b - 4 * (a * c);
	if (d < 0)
		return (2147483647);
	x1 = (-b + sqrt(d)) / 2 * a;
	x2 = (-b - sqrt(d)) / 2 * a;
	if (id == 1)
		return (x1);
	return (x2);
}
